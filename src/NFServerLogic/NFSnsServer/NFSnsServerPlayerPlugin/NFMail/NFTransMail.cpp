// -------------------------------------------------------------------------
//    @FileName         :    NFTransMail.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFTransMail.cpp
//
// -------------------------------------------------------------------------

#include "NFTransMail.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFUserMailMgr.h"
#include "NFTransMailCreate.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserMailModule.h"
#include "NFUserMailUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFTransMail, EOT_TRANS_USER_MAIL_ID, NFTransBase)

NFTransMail::NFTransMail() {
    if (NFShmMgr::Instance()->GetCreateMode() == EN_OBJ_MODE_INIT) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFTransMail::~NFTransMail() noexcept {

}

int NFTransMail::CreateInit() {
    m_mailID = 0;
    m_cmd = 0;
    m_roleID = 0;
    m_begin = 0;
    m_end = 0;
    m_transID = -1;
    m_type = EN_TRANS_MAIL_TYPE_NULL;

    return 0;
}

int NFTransMail::ResumeInit() {
    return 0;
}

int NFTransMail::Init(uint64_t roleID, uint64_t id, int transID, int cmd, int begin, int end) {
    m_mailID = id;
    m_roleID = roleID;
    m_cmd = cmd;
    m_begin = begin;
    m_end = end;
    m_transID = transID;
    m_type = EN_TRANS_MAIL_TYPE_NULL;
    return 0;
}

int NFTransMail::Init(uint64_t roleID, int cmd, vector<uint64_t> &vec) {
    m_mailID = 0;
    m_roleID = roleID;
    m_cmd = cmd;
    m_begin = 0;
    m_end = 0;
    m_transID = -1;
    m_type = EN_TRANS_MAIL_TYPE_NULL;

    for (size_t i = 0; i < vec.size(); ++i) {
        m_delMailID.Add(vec[i]);
    }
    return 0;
}

bool NFTransMail::IsTimeOut() {
    if (NFTime::Now().UnixSec() >= m_dwKeepAliveTime + 300) {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "This Trans TimeOut Type:{} Info:{}", GetClassType(), GetDebugInfo());
        OnTimeOut();
        return true;
    }

    return false;
}

int NFTransMail::OnTimeOut() {
    NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "trans mail timeout, mailId:{} roleId:{}, cmd:{}, type:{}, transid:{}",
               m_mailID, m_roleID, m_cmd, m_type, m_transID);
    return 0;
}

int NFTransMail::OnTransFinished(int iRunLogicRetCode) {
    if (iRunLogicRetCode && m_transID > 0) {
        NFTransBase *pTransBase = NFShmMgr::Instance()->GetTrans(m_transID);
        if (!pTransBase) {
            NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "create mail but trans timeout, cmd:{} userId:{} transID:{}", m_cmd, m_roleID, m_transID);
            return -1;
        }

        pTransBase->SetFinished(iRunLogicRetCode);
    }

    if (m_type == EN_TRANS_MAIL_TYPE_SAVE) {
        NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
        CHECK_NULL(pUserMailExt);
        pUserMailExt->SetSaving(false);
    }

    if (iRunLogicRetCode)
    {
        if (m_cmd == proto_ff::NF_LTS_MAIL_LIST_REQ)
        {
            proto_ff::Proto_STLMailListRsp rsp;
            rsp.set_user_id(m_roleID);
            rsp.mutable_cs_rsp()->set_result(iRunLogicRetCode);
            NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
            if (pOnline)
            {
                pOnline->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_LIST_RSP, rsp);
            }
        }
        else if (m_cmd == proto_ff::NF_LTS_MAIL_READ_REQ)
        {
            proto_ff::Proto_STLMailReadRsp rsp;
            rsp.set_user_id(m_roleID);
            proto_email::Proto_CSMailReadRsp* cs_rsp = rsp.mutable_cs_rsp();
            cs_rsp->set_result(iRunLogicRetCode);
            NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
            if (pOnline)
            {
                pOnline->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_RSP, rsp);
            }
        }
        else if (m_cmd == proto_ff::NF_LTS_MAIL_DEL_REQ)
        {
            proto_ff::Proto_STLMailDelRsp rspMsg;
            proto_email::Proto_CSMailDelRsp* pRsp = rspMsg.mutable_cs_rsp();
            rspMsg.set_user_id(m_roleID);
            pRsp->set_result(iRunLogicRetCode);
            NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
            if (pOnline)
            {
                pOnline->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_DEL_RSP, rspMsg);
            }
        }
        else if (m_cmd == proto_ff::NF_LTS_MAIL_GET_ITEM_REQ)
        {

        }
    }


    return 0;
}

int
NFTransMail::HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id, uint32_t seq,
                            uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    if (table_id == proto_ff::E_TABLE_USER_MAIL) {
        if (cmd == proto_ff::E_STORESVR_S2C_SELECTOBJ) {
            iRetCode = ProGetMailBaseInfoRes((const storesvr_sqldata::storesvr_selobj_res *) pSSMsgRes, cmd, table_id,
                                             err_code);
        } else if (cmd == proto_ff::E_STORESVR_S2C_INSERT) {
            iRetCode = ProMailBaseCreateRes((const storesvr_sqldata::storesvr_ins_res *) pSSMsgRes, cmd, table_id,
                                            err_code);
        } else if (cmd == proto_ff::E_STORESVR_S2C_MODIFYOBJ)
        {
            iRetCode = ProSaveRoleMailRes((const storesvr_sqldata::storesvr_modobj_res *) pSSMsgRes, cmd, table_id, seq, err_code);
        }
    }
    else if (table_id == proto_ff::E_TABLE_MAIL_DETAIL) {
        if (cmd == proto_ff::E_STORESVR_S2C_SELECT)
        {
            iRetCode = ProMailListRes((const storesvr_sqldata::storesvr_sel_res*)pSSMsgRes, cmd, table_id, err_code);
        }
        else if (cmd == proto_ff::E_STORESVR_S2C_DELETE) {
            iRetCode = ProMailDelRes((const storesvr_sqldata::storesvr_del_res*)pSSMsgRes, cmd, table_id, err_code);
        }
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::HandleCSMsgReq(const google::protobuf::Message *pCSMsgReq) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    CHECK_NULL(pCSMsgReq);
    NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
    CHECK_NULL(pOnline);

    int iRetCode = HandleGetMailBaseInfoMsgParam(pCSMsgReq);
    if (iRetCode) {
        return iRetCode;
    }

    NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
    if (pUserMailExt) {
        iRetCode = HandleGetBaseInfoRes(pUserMailExt);
        SetFinished(iRetCode);
    } else {
        iRetCode = ProGetMailBaseInfoReq();
        if (iRetCode) {
            return iRetCode;
        }
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::ProMailSaveReq(NFUserMail *roleMailExt) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    proto_ff::tbUserMailInfo tb_user_mail;
    m_type = EN_TRANS_MAIL_TYPE_SAVE;
    tb_user_mail.set_user_id(m_roleID);
    proto_ff_s::UserMailInfo_s::write_to_pbmsg(*roleMailExt->GetData(), *tb_user_mail.mutable_base_info());

    int iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_MODIFYOBJ,
                                                                          proto_ff::E_TABLE_USER_MAIL,
																		  NF_DEFAULT_MYSQL_DB_NAME,
                                                                          "tbUserMailInfo",
                                                                          tb_user_mail,
                                                                          GetGlobalID(), roleMailExt->GetCurSeq(), m_roleID);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end -- iRetCode:{}", iRetCode);
    return iRetCode;
}

int NFTransMail::ProSaveRoleMailRes(const storesvr_sqldata::storesvr_modobj_res *pSelectRsp, uint32_t cmd, uint32_t table_id,
                                    uint32_t seq, uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    if (err_code == proto_ff::E_STORESVR_ERRCODE_OK)
    {
        NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
        CHECK_EXPR(pUserMailExt, -1, "Find UserMail Faled, roleId:{}", m_roleID);

        pUserMailExt->SetRoleDetailSavedSeq(seq);
        NFLogInfo(NF_LOG_USER_MAIL_PLUGIN, m_roleID, "RoleID:{} Save Role Mail To DB Success, Seq:{}", m_roleID, seq);
        SetFinished(0);
    } else {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_roleID, "RoleID:{} Save Sns User Mail to DB Failed! iRetCode:{}", m_roleID, err_code);
        return -1;
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::ProGetMailBaseInfoReq() {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    proto_ff::tbUserMailInfo tb_user_mail;
    tb_user_mail.set_user_id(m_roleID);

    int iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_SELECTOBJ,
                                                                          proto_ff::E_TABLE_USER_MAIL, NF_DEFAULT_MYSQL_DB_NAME, "tbUserMailInfo",
                                                                          tb_user_mail, GetGlobalID(), 0, m_roleID);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::LoadMailList(const std::vector<uint64_t>& vecMailId)
{
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;

    std::vector<storesvr_sqldata::storesvr_vk> vk_list;
    for (int i = 0; i < (int)vecMailId.size(); i++) {
        storesvr_sqldata::storesvr_vk vk;

        vk.set_column_name("id");
        std::string szID = NFCommon::tostr(vecMailId[i]);
        vk.set_column_value(szID);
        vk.set_column_type(storesvr_sqldata::E_COLUMNTYPE_NUM);
        vk.set_cmp_operator(storesvr_sqldata::E_CMPOP_EQUAL); //storesvr_sqldata::storesvr_cmp_operator
        vk.set_logic_operator(storesvr_sqldata::E_LOGICOP_OR);
        vk_list.push_back(vk);
    }

    if (vk_list.size() > 0) {
        std::string where_conds = "ORDER BY send_time asc";

        vk_list[vk_list.size() - 1].set_logic_operator(storesvr_sqldata::E_LOGICOP_NONE);

        iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_SELECT,
                                                                          proto_ff::E_TABLE_MAIL_DETAIL,
                                                                          NF_DEFAULT_MYSQL_DB_NAME,
                                                                          "tbUserMailDetail", vk_list, where_conds,
                                                                          GetGlobalID(),
                                                                          0, m_roleID);
    } else {
        return -1;
    }

    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::ProMailListReq(NFUserMail *roleMailExt, int simpleCount) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    CHECK_NULL(roleMailExt);

    int iRetCode = 0;
    if (simpleCount > ROLE_MAIL_GET_MAIL_MAX) {
        simpleCount = ROLE_MAIL_GET_MAIL_MAX;
    }

    if (simpleCount > roleMailExt->GetData()->simple_mail.GetSize()) {
        simpleCount = roleMailExt->GetData()->simple_mail.GetSize();
    }

    int needCount = roleMailExt->GetData()->simple_mail.GetSize() < ROLE_MAIL_GET_MAIL_MAX ? (
            roleMailExt->GetData()->simple_mail.GetSize() - simpleCount) : (ROLE_MAIL_GET_MAIL_MAX - simpleCount);

    int tmpCount = roleMailExt->GetData()->simple_mail.GetSize();

    std::vector<uint64_t> vecId;
    for (int i = tmpCount - simpleCount - needCount; i < tmpCount - simpleCount; ++i) {
        vecId.push_back(roleMailExt->GetData()->simple_mail[i].id);
    }

    if (vecId.size() > 0) {
        iRetCode = LoadMailList(vecId);
    } else {
        return -1;
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::ProMailDelReq(NFUserMail *roleMailExt) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    std::vector<storesvr_sqldata::storesvr_vk> vk_list;
    int iRetCode = 0;

    for(int i = 0; i< roleMailExt->GetData()->del_role_mail.GetSize(); ++i)
    {
        storesvr_sqldata::storesvr_vk vk;

        vk.set_column_name("id");
        vk.set_column_value(NFCommon::tostr(roleMailExt->GetData()->del_role_mail[i]));
        vk.set_column_type(storesvr_sqldata::E_COLUMNTYPE_NUM);
        vk.set_cmp_operator(storesvr_sqldata::E_CMPOP_EQUAL); //storesvr_sqldata::storesvr_cmp_operator
        vk.set_logic_operator(storesvr_sqldata::E_LOGICOP_OR);
        vk_list.push_back(vk);

        m_delMailID.Add(roleMailExt->GetData()->del_role_mail[i]);
    }

    if(vk_list.size() > 0)
    {
        std::string where_conds;
        vk_list[vk_list.size() - 1].set_logic_operator(storesvr_sqldata::E_LOGICOP_NONE);
        iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_DELETE,
                                                                          proto_ff::E_TABLE_MAIL_DETAIL,
                                                                          NF_DEFAULT_MYSQL_DB_NAME,
                                                                          "tbUserMailDetail", vk_list, where_conds,
                                                                          GetGlobalID(),
                                                                          0, m_roleID);;
    }
    else
        return -1;
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::ProMailDelReq() {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;

    std::vector<storesvr_sqldata::storesvr_vk> vk_list;
    storesvr_sqldata::storesvr_vk vk;

    vk.set_column_name("user_id");
    vk.set_column_value(NFCommon::tostr(m_roleID));
    vk.set_column_type(storesvr_sqldata::E_COLUMNTYPE_NUM);
    vk.set_cmp_operator(storesvr_sqldata::E_CMPOP_EQUAL); //storesvr_sqldata::storesvr_cmp_operator
    vk.set_logic_operator(storesvr_sqldata::E_LOGICOP_NONE);
    vk_list.push_back(vk);

    if (vk_list.size() > 0) {
        std::string where_conds = "";

        vk_list[vk_list.size() - 1].set_logic_operator(storesvr_sqldata::E_LOGICOP_NONE);

        iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_DELETE,
                                                                          proto_ff::E_TABLE_MAIL_DETAIL,
                                                                          NF_DEFAULT_MYSQL_DB_NAME,
                                                                          "tbUserMailDetail", vk_list, where_conds,
                                                                          GetGlobalID(),
                                                                          0, m_roleID);;
    }

    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::ProMailBaseCreateRes(const storesvr_sqldata::storesvr_ins_res *pSelRsp, uint32_t cmd, uint32_t table_id,
                                      uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    if (err_code == proto_ff::E_STORESVR_ERRCODE_OK) {
        proto_ff::tbUserMailInfo tb_user_mail;

        NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Insert(m_roleID);
        CHECK_NULL(pUserMailExt);

        pUserMailExt->Init(tb_user_mail.mutable_base_info());

        iRetCode = HandleGetBaseInfoRes(pUserMailExt);
        if (iRetCode) {
            return iRetCode;
        }
    }
    else
    {
        NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
        if (pUserMailExt)
        {
            iRetCode = HandleGetBaseInfoRes(pUserMailExt);
            if (iRetCode) {
                return iRetCode;
            }
            else
            {
                NFLogError(NF_LOG_SYSTEMLOG, m_roleID, "insert user mail error");
                return -1;
            }
        }
    }

    SetFinished(0);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::ProGetMailBaseInfoRes(const storesvr_sqldata::storesvr_selobj_res *pSelRsp, uint32_t cmd, uint32_t table_id,
                                       uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    if (err_code != proto_ff::E_STORESVR_ERRCODE_SELECT_EMPTY && err_code != proto_ff::E_STORESVR_ERRCODE_OK) {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "get mail base error:{} roleid:{} cmd:{}", err_code, m_roleID, m_cmd);
        return -1;
    }

    if (err_code == proto_ff::E_STORESVR_ERRCODE_SELECT_EMPTY) {
        proto_ff::tbUserMailInfo tb_user_mail;
        tb_user_mail.set_user_id(m_roleID);

        return NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                      proto_ff::E_STORESVR_C2S_INSERT,
                                                                      proto_ff::E_TABLE_USER_MAIL,
                                                                      NF_DEFAULT_MYSQL_DB_NAME, "tbUserMailInfo", tb_user_mail,
                                                                      GetGlobalID(),
                                                                      0, m_roleID);
    }

    NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
    if (err_code == proto_ff::E_STORESVR_ERRCODE_OK && pUserMailExt == NULL) {
        proto_ff::tbUserMailInfo tb_user_mail;
        bool ok = tb_user_mail.ParseFromString(pSelRsp->sel_record());
        CHECK_EXPR(ok, -1, "ParseFromString Failed!");

        pUserMailExt = NFUserMailMgr::GetInstance()->Insert(m_roleID);
        CHECK_NULL(pUserMailExt);
        pUserMailExt->Init(tb_user_mail.mutable_base_info());
    }

    iRetCode = HandleGetBaseInfoRes(pUserMailExt);
    if (iRetCode) {
        return iRetCode;
    }

    SetFinished(0);

    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::ProMailDelRes(const storesvr_sqldata::storesvr_del_res *pSelRsp, uint32_t cmd, uint32_t table_id,
                               uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
    CHECK_NULL(pUserMailExt);

    if(err_code == proto_ff::E_STORESVR_ERRCODE_OK || err_code == proto_ff::E_STORESVR_ERRCODE_DELETERECORDISNOTEXIST)
    {
        pUserMailExt->ClearDeletedMail(m_delMailID.ToVector());
    }

    SetFinished(0);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::HandleGetMailCacheRes(NFUserMailCacheInfo* mailCacheInfo)
{
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    switch(m_cmd)
    {
        case proto_ff::NF_OtherTS_MAIL_CREATE_REQ:
        {
            NFTransMailCreate *pTrans = dynamic_cast<NFTransMailCreate *>(NFShmMgr::Instance()->GetTrans(m_transID));
            if (pTrans == NULL) {
                NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_roleID, "create mail but trans timeout:{}", m_roleID);
                return -1;
            }

            iRetCode = pTrans->TransGetMailBaseRes();
            if (iRetCode) {
                pTrans->SetFinished(iRetCode);
            }

            m_transID = -1;
            break;
        }
        case proto_ff::NF_LTS_MAIL_LIST_REQ:
        {
            NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
            CHECK_NULL(pUserMailExt);
            iRetCode = NFUserMailUtil::SendMailListToClient(pUserMailExt, m_roleID, mailCacheInfo, m_begin, m_end);
            break;
        }
        case proto_ff::NF_LTS_MAIL_GET_ITEM_REQ:
        {
            NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
            CHECK_NULL(pUserMailExt);
            iRetCode = NFUserMailUtil::SendGetMailItemToClient(pUserMailExt, m_roleID, mailCacheInfo, m_mailID);

            break;
        }
        case proto_ff::NF_LTS_MAIL_DEL_REQ:
        {
            if(m_delMailID.GetSize() > 0) {
                NFUserMailUtil::ProDeleteOpGetCacheRes(m_roleID, m_delMailID.ToVector());
            }
            else
            {
                NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
                CHECK_NULL(pUserMailExt);
                NFUserMailUtil::DeleteAllCacheMail(pUserMailExt, mailCacheInfo, m_roleID);
            }

            break;
        }
        case proto_ff::NF_LTS_MAIL_READ_REQ:
        {
            NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
            CHECK_NULL(pUserMailExt);
            if (!mailCacheInfo)
            {
                proto_ff::Proto_STLMailReadRsp rsp;
                rsp.set_user_id(m_roleID);
                proto_email::Proto_CSMailReadRsp* cs_rsp = rsp.mutable_cs_rsp();
                cs_rsp->set_result(proto_ff::ERR_CODE_READ_MAIL_FAIL);
                NFOnlineUser *pUser = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
                CHECK_NULL(pUser);
                pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_RSP, rsp);
            }
            iRetCode = NFUserMailUtil::ProReadMailRes(pUserMailExt, m_roleID, m_mailID);
            break;
        }
        default:
            break;
    }

    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::ProMailListRes(const storesvr_sqldata::storesvr_sel_res *pSelRsp, uint32_t cmd, uint32_t table_id,
                                uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    CHECK_EXPR(err_code == 0 || err_code == proto_ff::E_STORESVR_ERRCODE_SELECT_EMPTY, -1, "load mail error, err={}", err_code);

    NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
    CHECK_NULL(pUserMailExt);

    if (err_code == proto_ff::E_STORESVR_ERRCODE_SELECT_EMPTY)
    {
        HandleGetMailCacheRes(NULL);
        SetFinished(0);
        return 0;
    }

    NFUserMailCacheInfo* pCacheInfo = NFUserMailUtil::GetInstance()->GetMailCache(m_roleID);

    for(int i = 0; i < pSelRsp->sel_records_size(); i++)
    {
        proto_ff::tbUserMailDetail mail;
        bool ok = mail.ParseFromString(pSelRsp->sel_records(i));
        CHECK_EXPR(ok, -1, "ParseFromString Failed!");

        if (pCacheInfo == NULL)
        {
            pCacheInfo = NFUserMailUtil::GetInstance()->AddMailCache(m_roleID);
            if (pCacheInfo == NULL)
            {
                NFLogError(NF_LOG_SYSTEMLOG, m_roleID, "add mail cache error:{}", m_roleID);
                return -1;
            }
        }

        if (!pUserMailExt->IsDeletedMail(mail.id()))
        {
            NFUserMailUtil::AddMailCache(pCacheInfo, mail);
        }
    }

    if (pSelRsp->is_lastbatch())
    {
        if (pCacheInfo)
        {
            pCacheInfo->isInit = true;
        }
        HandleGetMailCacheRes(pCacheInfo);
        SetFinished(0);
    }

    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

int NFTransMail::HandleGetBaseInfoRes(NFUserMail *roleMailExt) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    switch (m_cmd) {
        case proto_ff::NF_OtherTS_MAIL_CREATE_REQ: {
            NFTransMailCreate *pTrans = dynamic_cast<NFTransMailCreate *>(NFShmMgr::Instance()->GetTrans(m_transID));
            if (pTrans == NULL) {
                NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_roleID, "create mail but trans timeout:{}", m_roleID);
                return -1;
            }

            iRetCode = pTrans->TransGetMailBaseRes();
            if (iRetCode) {
                pTrans->SetFinished(iRetCode);
            }

            m_transID = -1;
            break;
        }
        case proto_ff::NF_LTS_MAIL_LIST_REQ: {
            iRetCode = NFUserMailUtil::ProGetMailListRes(roleMailExt, m_roleID, m_begin, m_end);
            break;
        }
        case proto_ff::NF_LTS_MAIL_READ_REQ: {
            iRetCode = NFUserMailUtil::ProReadMailRes(roleMailExt, m_roleID, m_mailID);
            break;
        }
        case proto_ff::NF_LTS_MAIL_DEL_REQ: {
            std::vector<uint64_t> vec;
            for (int i = 0; i < (int) m_delMailID.GetSize(); i++) {
                vec.push_back(m_delMailID[i]);
            }

            iRetCode = NFUserMailUtil::ProDeleteMailRes(roleMailExt, m_roleID, vec);
            break;
        }
        case proto_ff::NF_LTS_MAIL_GET_ITEM_REQ: {
            iRetCode = NFUserMailUtil::ProGetMailItemRes(roleMailExt, m_roleID, m_mailID);
            break;
        }
        case proto_ff::NF_LTS_PLAYER_LOGIN_REQ: {
            if (roleMailExt)
            {
                NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(m_roleID);
                CHECK_NULL(pOnline);

                proto_ff::Proto_STLMailAutoPushRsp ntf;
                ntf.set_all_count(roleMailExt->GetAllMailSize());
                ntf.set_no_read_count(roleMailExt->GetAllNoReadMailSize());
                NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pOnline->GetLogicId(), proto_ff::NF_STL_MAIL_MAIL_AUTO_PUSH_RSP, ntf);

#ifdef NF_DEBUG_MODE
                if (roleMailExt->GetSimpleMailSize() < 40)
                {
                    NFUserMailUtil::OnSendTemplateMail(m_roleID, 2);
                }
#endif
            }
            iRetCode = 0;
            break;
        }
        default: {
            break;
        }
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMail::HandleGetMailBaseInfoMsgParam(const google::protobuf::Message *pMsgRes) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    CHECK_NULL(pMsgRes);

    switch(m_cmd)
    {
        case proto_ff::NF_LTS_MAIL_LIST_REQ:
        {
            const proto_ff::Proto_LTSMailListReq* pReq = dynamic_cast<const proto_ff::Proto_LTSMailListReq*>(pMsgRes);
            CHECK_NULL(pReq);
            CHECK_EXPR(pReq->cs_req().begin() > 0 && pReq->cs_req().end() > 0 && pReq->cs_req().end() - pReq->cs_req().begin() + 1 >= 10, proto_ff::ERR_CODE_MSG_PARAM_ERROR, "begin:{} end:{} error", pReq->cs_req().begin(), pReq->cs_req().end());

            m_begin = pReq->cs_req().begin();
            m_end = pReq->cs_req().end();
            break;
        }
        case proto_ff::NF_LTS_MAIL_READ_REQ:
        {
            const proto_ff::Proto_LTSMailReadReq* pReq = dynamic_cast<const proto_ff::Proto_LTSMailReadReq*>(pMsgRes);
            CHECK_NULL(pReq);
            m_mailID = pReq->mail_id();
            break;
        }
        case proto_ff::NF_LTS_MAIL_DEL_REQ:
        {
            const proto_ff::Proto_LTSMailDelReq* pReq = dynamic_cast<const proto_ff::Proto_LTSMailDelReq*>(pMsgRes);
            CHECK_NULL(pReq);
            for(int i = 0; i < (int)pReq->cs_req().mail_id_size(); i++)
            {
                m_delMailID.Add(pReq->cs_req().mail_id(i));
            }
            break;
        }
        case proto_ff::NF_LTS_MAIL_GET_ITEM_REQ:
        {
            const proto_ff::Proto_LTSMailGetItemReq* pReq = dynamic_cast<const proto_ff::Proto_LTSMailGetItemReq*>(pMsgRes);
            CHECK_NULL(pReq);
            m_mailID = pReq->mail_id();
            break;
        }
        default:
        {
            break;
        }
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}

