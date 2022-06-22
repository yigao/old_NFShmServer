// -------------------------------------------------------------------------
//    @FileName         :    NFCOnlineModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCOnlineModule
//
// -------------------------------------------------------------------------

#include "NFSnsSystemStatModule.h"

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
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFGameDay.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemStat.h"

NFSnsSystemStatModule::NFSnsSystemStatModule(NFIPluginManager* p) : NFIDynamicModule(p)
{
}

NFSnsSystemStatModule::~NFSnsSystemStatModule()
{
}

bool NFSnsSystemStatModule::Awake()
{
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_WorldTSns_GAME_ROOM_REG_NOTIFY, this,
                                                 &NFSnsSystemStatModule::OnHandleGameRegReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_STSNS_PlayerJettonChangeStatReq, this,
                                                 &NFSnsSystemStatModule::OnHandlePlayerJettonChangeStatReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_GameTSns_GAME_ROOM_STAT_INFO_SEND, this,
                                                 &NFSnsSystemStatModule::OnHandleGameRoomStatInfoReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_GameTSns_GAME_PLAYER_ACH_INFO_SEND, this,
                                                 &NFSnsSystemStatModule::OnHandleGamePlayerAchInfoReq);

    Subscribe(proto_ff::NF_EVENT_SERVER_LOAD_DESC_STORE, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    Subscribe(proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    return true;
}

bool NFSnsSystemStatModule::Init()
{
    return true;
}

bool NFSnsSystemStatModule::Execute()
{
    return true;
}

bool NFSnsSystemStatModule::OnDynamicPlugin()
{
    return true;
}

int NFSnsSystemStatModule::OnExecute(uint32_t nEventID, uint64_t nSrcID, uint32_t bySrcType, const google::protobuf::Message& message)
{
    if (bySrcType == proto_ff::NF_EVENT_SERVER_TYPE)
    {
        if (nEventID == proto_ff::NF_EVENT_SERVER_LOAD_DESC_STORE)
        {
            NFSystemStatMgr::Instance()->Init();
        }
        else if (nEventID == proto_ff::NF_EVENT_SERVER_APP_FINISH_INITED)
        {
        }
    }
    return 0;
}

int NFSnsSystemStatModule::OnHandleGameRegReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::GameRoomRegReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSystemStatMgr::Instance()->InitGameReg(xMsg.room_info().game_id(), xMsg.room_info().room_id());

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsSystemStatModule::OnHandlePlayerJettonChangeStatReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_PlayerJettonChangeStatReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSystemDay::Instance()->OnPlayerJettonChangeStat(xMsg);
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsSystemStatModule::OnHandleGameRoomStatInfoReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_GameTSns_GameRoomStatInfoReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFGameDay* pGameDay = NFSystemStatMgr::Instance()->GetGameDay(xMsg.game_id(), xMsg.room_id());
    if (pGameDay)
    {
        pGameDay->OnGameRoomStatInfo(xMsg.stat_info());
    }

    if (!xMsg.is_exe_scene())
    {
        NFSystemDay::Instance()->OnGameRoomStatInfo(xMsg);
        pGameDay = NFSystemStatMgr::Instance()->GetGameDay(xMsg.game_id(), 0);
        if (pGameDay)
        {
            pGameDay->OnGameRoomStatInfo(xMsg.stat_info());
        }

        pGameDay = NFSystemStatMgr::Instance()->GetGameDay(0, 0);
        if (pGameDay)
        {
            pGameDay->OnGameRoomStatInfo(xMsg.stat_info());
        }
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsSystemStatModule::OnHandleGamePlayerAchInfoReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_GameTSns_GamePlayerAchInfoReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSnsUserSimple* pUser = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(xMsg.user_id(), false);
    CHECK_NULL(pUser);

    pUser->GetSimpleData()->ach_day += xMsg.ach_data().cur_ach();
    pUser->GetSimpleData()->ach_week += xMsg.ach_data().cur_ach();
    pUser->GetSimpleData()->ach_month += xMsg.ach_data().cur_ach();
    pUser->GetSimpleData()->ach_all += xMsg.ach_data().cur_ach();

    pUser->GetSimpleData()->all_fee += xMsg.ach_data().cur_fee();

    pUser->MarkDirty();

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}