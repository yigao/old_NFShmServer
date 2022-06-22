// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCodeTrans
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCodeTrans.h
//
// -------------------------------------------------------------------------

#include "NFRedeemCodeTrans.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFRedeemCodeMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFRedeemCodeTrans, EOT_REDEEM_CODE_TRANS_ID, NFTransBase)

NFRedeemCodeTrans::NFRedeemCodeTrans()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFRedeemCodeTrans::~NFRedeemCodeTrans()
{

}

int NFRedeemCodeTrans::CreateInit() {
    m_userId = 0;
    m_cmd = 0;
    m_redeemCodeId.CreateInit();
    return 0;
}

int NFRedeemCodeTrans::ResumeInit() {
    return 0;
}

int NFRedeemCodeTrans::HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id, uint32_t seq,
               uint32_t err_code)
{
    int iRetCode = 0;
    if (table_id == proto_ff::E_TABLE_NONE) {
        if (cmd == proto_ff::E_STORESVR_S2C_SELECTOBJ)
        {
            iRetCode = ProRedeemCodeRes((const storesvr_sqldata::storesvr_selobj_res*)pSSMsgRes, cmd, table_id, err_code);
        }
    }
    return iRetCode;
}

int NFRedeemCodeTrans::InitThisTrans(uint64_t userId, uint32_t cmd, const std::string& id)
{
    m_userId = userId;
    m_cmd = cmd;
    m_redeemCodeId = id;
    return 0;
}

int NFRedeemCodeTrans::ProRedeemCodeRes(const storesvr_sqldata::storesvr_selobj_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code)
{
    if (err_code != 0) {
        if (err_code == proto_ff::E_STORESVR_ERRCODE_SELECT_EMPTY) {
            NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
            CHECK_EXPR(pUser, -1, "user_id:{} not online", m_userId);

            proto_ff::Proto_STLRedeemCodeRsp codeRsp;
            codeRsp.set_result(proto_ff::EOT_CODE_REDEEM_CODE_NOT_EXIST);
            codeRsp.set_id(m_redeemCodeId.GetString());
            codeRsp.set_user_id(m_userId);
            codeRsp.set_add_gold(0);
            NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);
            SetFinished(0);
            return 0;
        } else {
            NFLogTrace(NF_LOG_LOGIN_SERVER_PLUGIN, 0,
                       "Get tbRedeeomCode:{} Failed From Mysql, cmd:{} tableid:{} err_code:{}", m_redeemCodeId.GetString(), cmd, table_id,
                       err_code);

            NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
            CHECK_EXPR(pUser, -1, "user_id:{} not online", m_userId);

            proto_ff::Proto_STLRedeemCodeRsp codeRsp;
            codeRsp.set_result(-1);
            codeRsp.set_id(m_redeemCodeId.GetString());
            codeRsp.set_user_id(m_userId);
            codeRsp.set_add_gold(0);
            NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);
            SetFinished(0);
            return 0;
        }
    }

    proto_ff::tbRedeemCode codeInfo;
    codeInfo.ParseFromString(pSelRsp->sel_record());

    NFRedeemCode* pCode = NFRedeemCodeMgr::Instance()->Find(m_redeemCodeId.GetString());
    if (!pCode)
    {
        NFRedeemCodeMgr::Instance()->ClearFull();
        pCode = NFRedeemCodeMgr::Instance()->Insert(m_redeemCodeId.GetString(), codeInfo);
        if (!pCode)
        {
            NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
            CHECK_EXPR(pUser, -1, "user_id:{} not online", m_userId);

            proto_ff::Proto_STLRedeemCodeRsp codeRsp;
            codeRsp.set_result(-1);
            codeRsp.set_id(m_redeemCodeId.GetString());
            codeRsp.set_user_id(m_userId);
            codeRsp.set_add_gold(0);
            NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);
            SetFinished(0);
            return 0;
        }
    }

    CHECK_EXPR(pCode, -1, "");

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
    CHECK_EXPR(pUser, -1, "user_id:{} not online", m_userId);

    pCode->SetUsed(m_userId);
    pCode->Save();

    proto_ff::Proto_STLRedeemCodeRsp codeRsp;
    codeRsp.set_result(0);
    codeRsp.set_id(m_redeemCodeId.GetString());
    codeRsp.set_user_id(m_userId);
    codeRsp.set_add_gold(pCode->GetGold());
    NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);

    NFRedeemCodeMgr::Instance()->Delete(m_redeemCodeId.GetString());

    SetFinished(0);
    return 0;
}

int NFRedeemCodeTrans::HandleRedeemCodeReq()
{
    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
    CHECK_EXPR(pUser, -1, "user_id:{} not online", m_userId);

    NFRedeemCode* pCode = NFRedeemCodeMgr::Instance()->Find(m_redeemCodeId.GetString());
    if (pCode)
    {
        if (pCode->IsUsed())
        {
            proto_ff::Proto_STLRedeemCodeRsp codeRsp;
            codeRsp.set_result(proto_ff::EOT_CODE_REDEEM_CODE_USED);
            codeRsp.set_id(m_redeemCodeId.GetString());
            codeRsp.set_user_id(m_userId);
            codeRsp.set_add_gold(0);
            NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);
            SetFinished(0);
        }
        else
        {
            pCode->SetUsed(m_userId);
            pCode->Save();

            proto_ff::Proto_STLRedeemCodeRsp codeRsp;
            codeRsp.set_result(0);
            codeRsp.set_id(m_redeemCodeId.GetString());
            codeRsp.set_user_id(m_userId);
            codeRsp.set_add_gold(pCode->GetGold());
            NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), proto_ff::E_STL_RedeemCodeRsp, codeRsp, 0);

            NFRedeemCodeMgr::Instance()->Delete(m_redeemCodeId.GetString());
            SetFinished(0);
        }
    }
    else
    {
        ReqGetRedeemCodeData();
    }
    return 0;
}

int NFRedeemCodeTrans::ReqGetRedeemCodeData()
{
    proto_ff::tbRedeemCode code;
    code.set_id(m_redeemCodeId.GetString());

    return NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                                    proto_ff::E_STORESVR_C2S_SELECTOBJ,
                                                                    proto_ff::E_TABLE_NONE,
                                                                    NF_DEFAULT_MYSQL_DB_NAME, "tbRedeemCode", code,
                                                                    GetGlobalID(), 0, std::hash<std::string>()(m_redeemCodeId.GetString()));
}

