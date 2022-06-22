// -------------------------------------------------------------------------
//    @FileName         :    NFTransMailCreate.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFTransMailCreate.cpp
//
// -------------------------------------------------------------------------

#include "NFTransMailCreate.h"
#include "NFTransMail.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFUserMailMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserMailModule.h"
#include "NFUserMailUtil.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFTransMailCreate, EOT_TRANS_USER_MAIL_CREATE_ID, NFTransBase)

NFTransMailCreate::NFTransMailCreate() {
    if (NFShmMgr::Instance()->GetCreateMode() == EN_OBJ_MODE_INIT) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFTransMailCreate::~NFTransMailCreate() noexcept {

}

int NFTransMailCreate::CreateInit() {
    memset(&m_tmp, 0, sizeof(m_tmp));
    m_roleID = 0;
    m_isGM = false;
    m_iSrcSvrID = -1;
    return 0;
}

int NFTransMailCreate::ResumeInit() {
    return 0;
}

int NFTransMailCreate::Init(uint64_t roleID, bool isGM, uint64_t iSrcSvrID) {
    m_roleID = roleID;
    m_isGM = isGM;
    m_iSrcSvrID = iSrcSvrID;
    return 0;
}

bool NFTransMailCreate::IsTimeOut() {
    if (NFTime::Now().UnixSec() >= m_dwKeepAliveTime + 3500) {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "This Trans TimeOut Type:{} Info:{}", GetClassType(), GetDebugInfo());
        OnTimeOut();
        return true;
    }

    return false;
}

int NFTransMailCreate::OnTimeOut() {
    proto_ff::tbUserMailDetail tmpDebug;

    proto_ff_s::tbUserMailDetail_s::write_to_pbmsg(m_tmp, tmpDebug);
    NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "trans mailCreate timeout: roleid:{} isgm:{} mail:{}", m_roleID, m_isGM,
               tmpDebug.DebugString());
    return 0;
}

int NFTransMailCreate::OnTransFinished(int iRunLogicRetCode) {
    return 0;
}

int NFTransMailCreate::HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id,
                                      uint32_t seq,
                                      uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin -- cmd:{} table_id:{} err_code:{}", cmd, table_id, err_code);

    int iRetCode = 0;
    if (table_id == proto_ff::E_TABLE_MAIL_DETAIL) {
        if (cmd == proto_ff::E_STORESVR_S2C_INSERT) {
            iRetCode = ProMailCreateRes((const storesvr_sqldata::storesvr_ins_res *) pSSMsgRes, cmd, table_id,
                                        err_code);
        }
    } else {
        iRetCode = -2;
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "Unknown TableID:{} cmd:{} TransInfo:{}", table_id, cmd, GetDebugInfo());
    }
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFTransMailCreate::TransGetMailBaseRes() {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;

    proto_ff::tbUserMailDetail tb_mail_detail;
    proto_ff_s::tbUserMailDetail_s::write_to_pbmsg(m_tmp, tb_mail_detail);
    iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                      proto_ff::E_STORESVR_C2S_INSERT,
                                                                      proto_ff::E_TABLE_MAIL_DETAIL,
                                                                      NF_DEFAULT_MYSQL_DB_NAME, "tbUserMailDetail", tb_mail_detail,
                                                                      GetGlobalID(),
                                                                      0, m_roleID);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end -- iRetCode:{}", iRetCode);
    return iRetCode;
}

int NFTransMailCreate::ProMailCreateReq(proto_ff::tbUserMailDetail &tb_role_mail) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");
    if (m_roleID == 0) {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "role null:{}", m_roleID);
        return 0;
    }

    int iRetCode = 0;
    uint64_t mailId = FindModule<NFIKernelModule>()->Get64UUID();
    tb_role_mail.set_id(mailId);
    tb_role_mail.set_send_time(NFTime::Now().UnixSec());
    tb_role_mail.set_user_id(m_roleID);

    proto_ff_s::tbUserMailDetail_s::read_from_pbmsg(tb_role_mail, m_tmp);

    NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
    if (pUserMailExt) {
        iRetCode = NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                          proto_ff::E_STORESVR_C2S_INSERT,
                                                                          proto_ff::E_TABLE_MAIL_DETAIL,
                                                                          NF_DEFAULT_MYSQL_DB_NAME, "tbUserMailDetail", tb_role_mail,
                                                                          GetGlobalID(),
                                                                          0, m_roleID);
    } else {
        NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
        CHECK_EXPR(pTransMail, ERR_TRANS_RUNED_TOO_MUCH, "Create msg Trans Failed! Used Item:{}",
                   NFTransMail::GetUsedCount());

        pTransMail->Init(m_roleID, 0, GetGlobalID(), (int) proto_ff::NF_OtherTS_MAIL_CREATE_REQ);
        iRetCode = pTransMail->ProGetMailBaseInfoReq();
        if (iRetCode) {
            pTransMail->SetFinished(iRetCode);
            return iRetCode;
        }
    }


    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int
NFTransMailCreate::ProMailCreateRes(const storesvr_sqldata::storesvr_ins_res *pSelRsp, uint32_t cmd, uint32_t table_id,
                                    uint32_t err_code) {
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- begin --");

    if (m_isGM)
    {
        proto_ff::Proto_STOtherMailCreateRsp rspMsg;
        rspMsg.set_result(err_code);
        rspMsg.set_user_id(m_roleID);
        proto_ff_s::tbUserMailDetail_s::write_to_pbmsg(m_tmp, *rspMsg.mutable_role_mail());
        uint32_t serverType = GetServerTypeFromUnlinkId(m_iSrcSvrID);
        uint32_t busId = GetServerIndexFromUnlinkId(m_iSrcSvrID);

        if (serverType == NF_ST_LOGIC_SERVER)
        {
           NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, busId, (uint32_t)proto_ff::NF_STOther_MAIL_CREATE_RSP, rspMsg);
        }
        else if (serverType == NF_ST_WORLD_SERVER)
        {
            NFMessageMgr::Instance()->SendMsgToWorldServer(NF_ST_SNS_SERVER, (uint32_t)proto_ff::NF_STOther_MAIL_CREATE_RSP, rspMsg);
        }
        else if (serverType == NF_ST_GAME_SERVER)
        {
            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, busId, (uint32_t)proto_ff::NF_STOther_MAIL_CREATE_RSP, rspMsg);
        }
    }

    if (err_code == proto_ff::E_STORESVR_ERRCODE_OK) {
        NFUserMail *pUserMailExt = NFUserMailMgr::GetInstance()->Find(m_roleID);
        CHECK_EXPR(pUserMailExt, -1, "pHashTable->Find(m_userId) Failed, roleID:{}", m_roleID);

        int iRet = NFUserMailUtil::AddMailRes(pUserMailExt, m_roleID, m_tmp);
        if (iRet)
        {
           NFLogError(NF_LOG_SYSTEMLOG, m_roleID, "add mail error, mailId:{}", m_tmp.id);
        }
        else
        {
            //NFLogBehavior(m_roleID, "", m_tmp);
        }

    } else {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "Insert mail error, roleid:{} mailid:{}", m_roleID, m_tmp.id);
        return -1;
    }

    SetFinished(0);
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "-- end --");
    return 0;
}
