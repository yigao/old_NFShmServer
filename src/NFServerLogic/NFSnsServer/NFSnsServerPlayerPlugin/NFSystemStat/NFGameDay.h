// -------------------------------------------------------------------------
//    @FileName         :    NFGameDay.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGameDay.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFBaseDBObj.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"

class NFGameDay : public NFBaseDBObj
{
public:
    NFGameDay();
    virtual ~NFGameDay();

    //非继承函数, 不要加virtual
    int CreateInit();
    //非继承函数, 不要加virtual
    int ResumeInit();

    std::string GetDayStr();
public:
    int Init(NF_SERVER_TYPES serverType, uint32_t gameId, uint32_t roomId);
    int DayTick();
    int WeekTick();
    int MonthTick();
    int InitData();
    int OnGameRoomStatInfo(const proto_ff::GameRoomStat& req);
private:
    uint32_t m_gameId;
    uint32_t m_roomId;
    proto_ff_s::tbLogGameDay_s m_stData;
DECLARE_DB_OBJ_SETTING(proto_ff::E_TABLE_LOG_GAME_DAY, tbLogGameDay, SYSTEM_DAY_MAX_SAVE_TIME, EN_DW_RETRY_ANY_SHUTDOWN);
DECLARE_IDCREATE(NFGameDay)
};
