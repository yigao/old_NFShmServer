// -------------------------------------------------------------------------
//    @FileName         :    NFSystemDay.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSystemDay.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFBaseDBObj.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"

class NFSnsUserSimple;
class NFOnlineUser;

class NFSystemDay : public NFBaseDBObj
{
public:
    NFSystemDay();
    virtual ~NFSystemDay();

    //非继承函数, 不要加virtual
    int CreateInit();
    //非继承函数, 不要加virtual
    int ResumeInit();

    std::string GetDayStr();
public:
    int Init(NF_SERVER_TYPES serverType);
    int InitData();
    int DayTick();
    int CountValidPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser);
    int GetSystemDataFromSystemStat();
    int GetTodayFromSystemStat();
public:
    int OnPlayerLogin(NFSnsUserSimple* pSimple, NFOnlineUser* pUser);
    int OnPlayerLogout(NFSnsUserSimple* pSimple, NFOnlineUser* pUser);
    int OnNewPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser);
    int OnPlayerJettonChangeStat(const proto_ff::Proto_PlayerJettonChangeStatReq& req);
    int OnGameRoomStatInfo(const proto_ff::Proto_GameTSns_GameRoomStatInfoReq& req);
private:
    proto_ff_s::tbLogSystemDay_s m_stData;
DECLARE_DB_OBJ_SETTING(proto_ff::E_TABLE_LOG_SYSTEM_DAY, tbLogSystemDay, SYSTEM_DAY_MAX_SAVE_TIME, EN_DW_RETRY_ANY_SHUTDOWN);
DECLARE_IDCREATE(NFSystemDay)
};