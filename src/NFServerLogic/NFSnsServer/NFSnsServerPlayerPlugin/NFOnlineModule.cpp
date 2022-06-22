// -------------------------------------------------------------------------
//    @FileName         :    NFCOnlineModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCOnlineModule
//
// -------------------------------------------------------------------------

#include "NFOnlineModule.h"

#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFServer/NFCommHead/NFICommLogicModule.h"
#include "NFComm/NFPluginModule/NFIMonitorModule.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFTransSnsUserOnline.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleMgr.h"

#include "NFUserMailModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMailCreate.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailUtil.h"
#include "NFComm/NFMessageDefine/proto_event.pb.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFRankMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFRankCommon.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFGetRankTrans.h"
#include "NFWhiteBlackListDesc.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemStatMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemDay.h"

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRedeemCode/NFRedeemCodeTrans.h"

NFCOnlineModule::NFCOnlineModule(NFIPluginManager* p) :NFIDynamicModule(p)
{
}

NFCOnlineModule::~NFCOnlineModule()
{
}

bool NFCOnlineModule::Awake()
{
	NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_PLAYER_LOGIN_REQ, this, &NFCOnlineModule::OnHandlePlayerLogin);
	NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_PLAYER_LOGOUT_REQ, this, &NFCOnlineModule::OnHandlePlayerLogout);
	NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_PLAYER_DISCONNECT_MSG, this, &NFCOnlineModule::OnHandlePlayerDisConnect);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_PLAYER_RECONNECT_MSG, this, &NFCOnlineModule::OnHandlePlayerReconnect);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_QUERY_USER_REQ, this, &NFCOnlineModule::OnHandleQueryUser);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_SNS_ROUTER_CMD_TO_SUIT_LOGIC, this, &NFCOnlineModule::OnHandleRouteToSuitLogicServer);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_STSns_UPDATE_RANK_REQ, this, &NFCOnlineModule::OnHandleUpdateRankStore);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_GET_COMMON_RANK_REQ, this, &NFCOnlineModule::OnHandleGetCommonRankReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTSns_CHANGE_FACE_NOTIFY, this, &NFCOnlineModule::OnHandleChangeFace);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTSns_CHANGE_NICKNAME_NOTIFY, this, &NFCOnlineModule::OnHandleChangeNickName);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTS_PLAYER_VIPLVEL_CHANGE_NOTIFY, this, &NFCOnlineModule::OnHandleChangeVipLevel);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_LTSns_NOTIFY_PLAYER_ENTER_GAME, this,
                                                 &NFCOnlineModule::OnHandlePlayerEnterGame);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_LTSns_NOTIFY_PLAYER_EXIT_GAME, this,
                                                 &NFCOnlineModule::OnHandlePlayerExitGame);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_LTS_RedeemCodeReq, this,
                                                 &NFCOnlineModule::OnHandleRedeemCodeReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_LTSns_CHANGE_USERID_NOTIFY, this,
                                                 &NFCOnlineModule::OnHandleChangeUserId);


    Subscribe(proto_ff::NF_EVENT_SERVER_LOAD_DESC_STORE, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    Subscribe(proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
	return true;
}

bool NFCOnlineModule::Init()
{
	return true;
}

bool NFCOnlineModule::Execute()
{
	return true;
}

bool NFCOnlineModule::OnDynamicPlugin()
{
	return true;
}

int NFCOnlineModule::OnHandlePlayerDisConnect(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::NotifyPlayerDisconnect xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandlePlayerReconnect(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::LTSNotifyPlayerReconnectReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransSnsUserOnline* pTrans = (NFTransSnsUserOnline*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_USER_ONLINE);
    CHECK_NULL(pTrans);
    pTrans->UserReconnect(xMsg);
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandlePlayerLogin(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
	NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
	proto_ff::Proto_LogicToSnsLoginReq xMsg;
	CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFTransSnsUserOnline* pTrans = (NFTransSnsUserOnline*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_USER_ONLINE);
    CHECK_NULL(pTrans);
    pTrans->UserLogin(xMsg);

	NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
	return 0;
}

int NFCOnlineModule::OnPlayerLogin(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    NFUserMailUtil::OnPlayerLogin(pSimple);
    NFSystemDay::Instance()->OnPlayerLogin(pSimple, pUser);
    return 0;
}

int NFCOnlineModule::OnNewPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    NFSystemDay::Instance()->OnNewPlayer(pSimple, pUser);
    return 0;
}

int NFCOnlineModule::OnPlayerLogout(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    NFUserMailUtil::OnPlayerLogout(pSimple);
    NFSystemDay::Instance()->OnPlayerLogout(pSimple, pUser);
    return 0;
}

int NFCOnlineModule::OnHandlePlayerLogout(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
	NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
	proto_ff::Proto_LogicToSnsLogoutReq xMsg;
	CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

	proto_ff::Proto_SnsToLogicLogoutRsp rspMsg;
	rspMsg.set_result(0);
	rspMsg.set_player_id(xMsg.player_id());
	NFSnsUserSimple* pUser = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(xMsg.player_id(), false);
	CHECK_NULL(pUser);

	pUser->UserLogout();
	pUser->SaveToDB(false);

	NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(xMsg.player_id());
	if (pOnline)
	{
        OnPlayerLogout(pUser, pOnline);

        NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pOnline->GetLogicId(), proto_ff::NF_STL_PLAYER_LOGOUT_RSP, rspMsg);

		NFOnlineUserMgr::GetInstance()->Delete(xMsg.player_id());
	}
	NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
	return 0;
}

int NFCOnlineModule::OnHandleChangeFace(uint64_t unLinkId, uint64_t destLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::LTSnsChangeFaceNotify xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(xMsg.user_id());
    CHECK_NULL(pOnline);

    NFSnsUserSimple* pUser = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(xMsg.user_id(), false);
    CHECK_NULL(pUser);

    pUser->GetSimpleData()->face = xMsg.face_id();
    pUser->MarkDirty();

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleChangeVipLevel(uint64_t unLinkId, uint64_t destLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::LTSnsChangeVipLevelNotify xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    NFTransSnsUserOnline* pTrans = (NFTransSnsUserOnline*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_USER_ONLINE);
    CHECK_NULL(pTrans);
    pTrans->UserModifyVipLevel(xMsg);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleChangeNickName(uint64_t unLinkId, uint64_t destLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::LTSnsChangeNickNameNotify xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    NFTransSnsUserOnline* pTrans = (NFTransSnsUserOnline*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_USER_ONLINE);
    CHECK_NULL(pTrans);
    pTrans->UserModifyName(xMsg);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleChangeUserId(uint64_t unLinkId, uint64_t destLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::LTSnsChangeUserIdNotify xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    NFTransSnsUserOnline* pTrans = (NFTransSnsUserOnline*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_USER_ONLINE);
    CHECK_NULL(pTrans);
    pTrans->UserModifyUserId(xMsg);

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleQueryUser(uint64_t unLinkId, uint64_t destLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_LTSQueryUserReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, destLinkId, msg, nLen, xMsg);

    tagQueryRole query;
    query.Reset();
    for(int i = 0; i < (int)xMsg.query_user_id_size(); i++)
    {
        query.Add(xMsg.query_user_id(i));
    }
    query.userId = xMsg.user_id();

    NFTransSnsBase* pTrans = (NFTransSnsBase*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_BASE);
    CHECK_EXPR(pTrans, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransSnsBase::GetUsedCount());
    pTrans->Init(req_trans_id);
    pTrans->SetNotify();
    int iRetCode = pTrans->QueryRole(query);
    if (iRetCode)
    {
        pTrans->SetFinished(iRetCode);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFCOnlineModule::OnExecute(uint32_t nEventID, uint64_t nSrcID, uint32_t bySrcType, const google::protobuf::Message& message)
{
    if (bySrcType == proto_ff::NF_EVENT_SERVER_TYPE)
    {
        if (nEventID == proto_ff::NF_EVENT_SERVER_LOAD_DESC_STORE)
        {
            NFRankMgr::Instance()->Init();
        }
        else if (nEventID == proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED)
        {
            NFSnsUserSimpleMgr::Instance()->Init();
        }
    }
    return 0;
}

int NFCOnlineModule::OnHandleRouteToSuitLogicServer(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_SvrPkg xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(xMsg.mutable_disp_info()->user_id());
    if (pUser)
    {
        NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, pUser->GetLogicId(), xMsg.msg_id(), xMsg.msg_data().data(), xMsg.msg_data().length());
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleUpdateRankStore(uint64_t unLinkId, uint64_t sendLinkId, uint64_t req_trans_id, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_STSnsUpdateRankReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, sendLinkId, msg, nLen, xMsg);
    int iRetCode = 0;
    uint32_t fromBusId = GetServerIndexFromUnlinkId(sendLinkId);

    int oldRank = 0;
    int newRank = 0;
    int iRet = NFRankMgr::Instance()->UpdateRank(xMsg.rank_type(), xMsg.mutable_score(), oldRank, newRank);
    CHECK_RET(iRet, "Update Rank Failed:{}", xMsg.DebugString());

    proto_ff::Proto_SnsTSUpdateRankRsp rsp;
    rsp.set_rank_type(xMsg.rank_type());
    rsp.set_id(xMsg.score().id());
    rsp.set_rank_old(oldRank);
    rsp.set_rank_new(newRank);

    if (req_trans_id <= 0)
    {
        NFMessageMgr::Instance()->SendMsgToLogicServer(NF_ST_SNS_SERVER, fromBusId, proto_ff::NF_SnsTS_UPDATE_RANK_RSP, rsp);
    }
    else
    {
        NFMessageMgr::Instance()->SendTransToLogicServer(NF_ST_SNS_SERVER, fromBusId, proto_ff::NF_SnsTS_UPDATE_RANK_RSP, rsp, 0, req_trans_id);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFCOnlineModule::OnHandleGetCommonRankReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_LTSGetCommonRankReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);
    int iRetCode = 0;

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(xMsg.user_id());
    CHECK_NULL(pUser);

    NFRankCommon* pRank = NFRankMgr::Instance()->GetRank(xMsg.rank_type());
    CHECK_NULL(pRank);

    NFGetRankTrans* pTrans = dynamic_cast<NFGetRankTrans*>(NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_GET_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "Create NFGetRankTrans Failed! Use Count:{}", NFGetRankTrans::GetUsedCount());

    pTrans->InitThisTrans(xMsg.user_id(), xMsg.rank_type());

    uint32_t from = xMsg.rank_from();
    uint32_t to = xMsg.rank_to();
    if (to >= (uint32_t)pRank->GetMaxRank())
    {
        to = pRank->GetMaxRank();
    }

    for(uint32_t i = from;  i <= to; i++)
    {
        const proto_ff_s::RankCommonScore_s *pScore = pRank->GetRankScore(i);
        if (pScore)
        {
            int rank = pRank->GetRank(pScore->id);
            proto_ff_s::RankCommonInfo_s info;
            info.rank = rank;
            info.id = pScore->id;
            pTrans->AddScore(info, *pScore);
        }
    }

    pTrans->DoQuery();

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFCOnlineModule::OnHandlePlayerEnterGame(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::NotifySnsPlayerEnterGame xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(xMsg.player_id());
    if (pUser)
    {
        pUser->SetGameId(xMsg.game_id());
        pUser->SetRoomId(xMsg.room_id());
        pUser->SetGameBusId(xMsg.game_bus_id());

        proto_ff_s::tbGameUserManagerData_s* pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), pUser->GetRoomId());
        if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
        {
            proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
            gameMsg.set_player_id(pUser->GetUserID());
            proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
            return 0;
        }

        pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), 0);
        if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
        {
            proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
            gameMsg.set_player_id(pUser->GetUserID());
            proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
            return 0;
        }

        pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), 0, 0);
        if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
        {
            proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
            gameMsg.set_player_id(pUser->GetUserID());
            proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
            return 0;
        }
    }
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandlePlayerExitGame(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::NotifySnsPlayerExitGame xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(xMsg.player_id());
    if (pUser)
    {
        pUser->SetGameId(0);
        pUser->SetRoomId(0);
        pUser->SetGameBusId(0);
    }
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCOnlineModule::OnHandleRedeemCodeReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_LTSRedeemCodeReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(xMsg.user_id());
    CHECK_EXPR(pUser, -1, "user_id:{} not online", xMsg.user_id());

    NFRedeemCodeTrans* pTrans = dynamic_cast<NFRedeemCodeTrans*>(NFShmMgr::Instance()->CreateTrans(EOT_REDEEM_CODE_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "Create NFRedeemCodeTrans Failed! Use Count:{}", NFGetRankTrans::GetUsedCount());

    pTrans->InitThisTrans(xMsg.user_id(), nMsgId, xMsg.id());
    int iRetCode = pTrans->HandleRedeemCodeReq();
    if (iRetCode)
    {
        pTrans->SetFinished(-1);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}