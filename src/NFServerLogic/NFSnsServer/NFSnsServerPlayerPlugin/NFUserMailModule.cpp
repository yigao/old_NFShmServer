// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailModule.cpp
//
// -------------------------------------------------------------------------

#include "NFUserMailModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMailCreate.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFCommon.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMail.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFActivityMail.h"
#include "NFComm/NFMessageDefine/proto_event.pb.h"

NFCUserMailModule::NFCUserMailModule(NFIPluginManager *p) : NFIUserMailModule(p) {
}

NFCUserMailModule::~NFCUserMailModule() noexcept {

}

bool NFCUserMailModule::Awake() {
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_MAIL_LIST_REQ, this,
                                                       &NFCUserMailModule::OnHandleMailListReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_MAIL_READ_REQ, this,
                                                       &NFCUserMailModule::OnHandleMailReadReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_MAIL_DEL_REQ, this,
                                                       &NFCUserMailModule::OnHandleMailDelReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_OtherTS_MAIL_CREATE_REQ, this,
                                                       &NFCUserMailModule::OnHandleMailCreateReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_MAIL_GET_ITEM_REQ, this,
                                                       &NFCUserMailModule::OnHandleMailGetItemReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_MAIL_READ_ITEM_RSP, this,
                                                       &NFCUserMailModule::OnHandleMailReadItemRsp);

    Subscribe(proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    return true;
}

void NFCUserMailModule::OnTimer(uint32_t nTimerID) {
}

bool NFCUserMailModule::Init() {

    return true;
}

bool NFCUserMailModule::Execute() {
    return true;
}

int NFCUserMailModule::OnHandleMailListReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                           uint32_t nLen) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    proto_ff::Proto_LTSMailListReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());

    pTransMail->Init(xMsg.user_id(), 0, 0, proto_ff::NF_LTS_MAIL_LIST_REQ);
    iRetCode = pTransMail->HandleCSMsgReq(&xMsg);
    if (iRetCode)
    {
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCUserMailModule::OnHandleMailCreateReq(uint64_t unLinkId, uint64_t destLinkId, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    proto_ff::Proto_OtherTSMailCreateReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    iRetCode = NFUserMailUtil::OnCreateMail(*xMsg.mutable_role_mail(), xMsg.user_id(), true, destLinkId);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFCUserMailModule::OnHandleMailReadReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                           uint32_t nLen) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    proto_ff::Proto_LTSMailReadReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
    pTransMail->Init(xMsg.user_id(), 0, 0, proto_ff::NF_LTS_MAIL_READ_REQ);
    iRetCode = pTransMail->HandleCSMsgReq(&xMsg);
    if (iRetCode) {
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFCUserMailModule::OnHandleMailDelReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                          uint32_t nLen) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");

    int iRetCode = 0;
    proto_ff::Proto_LTSMailDelReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
    pTransMail->Init(xMsg.user_id(), 0, 0, proto_ff::NF_LTS_MAIL_DEL_REQ);
    iRetCode = pTransMail->HandleCSMsgReq(&xMsg);
    if (iRetCode) {
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCUserMailModule::OnHandleMailGetItemReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                              uint32_t nLen) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");

    int iRetCode = 0;
    proto_ff::Proto_LTSMailGetItemReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
    pTransMail->Init(xMsg.user_id(), 0, 0, proto_ff::NF_LTS_MAIL_GET_ITEM_REQ);
    iRetCode = pTransMail->HandleCSMsgReq(&xMsg);
    if (iRetCode) {
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCUserMailModule::OnHandleMailReadItemRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_LTSMailReadItemRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff::Proto_STLMailGetItemRsp rspMsg;
    rspMsg.set_user_id(xMsg.user_id());

    NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(xMsg.user_id());
    CHECK_NULL(pOnline);

    NFUserMail* pUserMailExt = NFUserMailMgr::GetInstance()->Find(xMsg.user_id());
    CHECK_NULL(pUserMailExt);

    // 还原状态
    for(int i = 0; i < (int)xMsg.id_size(); i++)
    {
        proto_ff_s::SingleMailInfo_s *pUserMailInfo = pUserMailExt->GetSimpleMail(xMsg.id(i).id());
        if (pUserMailInfo)
        {
            pUserMailInfo->status = proto_ff::EN_SNS_MAIL_NO_READ;
        }
        else
        {
            NFLogError(NF_LOG_SYSTEMLOG, 0, "mail id:{} can't find", xMsg.id(i).id());
        }
        pUserMailExt->MarkDirty();
    }

    proto_email::Proto_CSMailGetItemRsp *cs_rsp = rspMsg.mutable_cs_rsp();
    cs_rsp->mutable_item_list()->CopyFrom(xMsg.get_id());
    cs_rsp->set_no_read_count(pUserMailExt->GetAllNoReadMailSize());

    NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pOnline->GetLogicId(), proto_ff::NF_STL_MAIL_GET_ITEM_RSP, rspMsg);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCUserMailModule::OnExecute(uint32_t nEventID, uint64_t nSrcID, uint32_t bySrcType, const google::protobuf::Message& message)
{
    if (bySrcType == proto_ff::NF_EVENT_SERVER_TYPE)
    {
        if (nEventID == proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED)
        {
            NFActivityMail::Instance()->Init();
            NFUserMailMgr::Instance()->Init();
        }
    }
    return 0;
}