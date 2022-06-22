// -------------------------------------------------------------------------
//    @FileName         :    NFGameDay.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGameDay.cpp
//
// -------------------------------------------------------------------------

#include "NFGameDay.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFCommon.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFShmCore/NFDBObjMgr.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFGameDay, EOT_LOG_GAME_DAY_ID, NFBaseDBObj)

NFGameDay::NFGameDay()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode())
    {
        CreateInit();
    }
    else
    {
        ResumeInit();
    }
}

NFGameDay::~NFGameDay()
{

}

int NFGameDay::CreateInit() {
    m_gameId = 0;
    m_roomId = 0;
    memset(&m_stData, 0, sizeof(m_stData));
    return 0;
}

int NFGameDay::ResumeInit() {
    return 0;
}

int NFGameDay::MakeLoadData(google::protobuf::Message* data)
{
    CHECK_NULL(data);
    if (m_bDataInited) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "aleady inited !" );
        return -1;
    }

    proto_ff::tbLogGameDay* p = dynamic_cast<proto_ff::tbLogGameDay*>(data);
    CHECK_NULL(p);
    p->set_date_id(m_stData.date_id.GetString());

    return 0;
}

int NFGameDay::MakeSaveData(google::protobuf::Message* data)
{
    if ( !m_bDataInited ) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "not init!" );
        return -1;
    }
    CHECK_NULL(data);

    proto_ff::tbLogGameDay* p = dynamic_cast<proto_ff::tbLogGameDay*>(data);
    CHECK_NULL(p);
    proto_ff_s::tbLogGameDay_s::write_to_pbmsg(m_stData, *p);

    return 0;
}

int NFGameDay::InitWithDBData(const std::string* data)
{
    CHECK_NULL( data );
    proto_ff::tbLogGameDay pb;
    bool ok = pb.ParseFromString(*data);
    CHECK_EXPR( ok, -1, "parse failed!");
    proto_ff_s::tbLogGameDay_s::read_from_pbmsg(pb, m_stData);
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init with db data: {} ", m_stData.date_id.GetString());

    m_bDataInited = true;
    return 0;
}

int NFGameDay::InitWithoutDBData()
{
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init without db data: date_id:{} ", m_stData.date_id.GetString());
    m_bDataInited = true;
    MarkDirty();
    return 0;
}

int NFGameDay::Init(NF_SERVER_TYPES serverType, uint32_t gameId, uint32_t roomId)
{
    m_gameId = gameId;
    m_roomId = roomId;
    SetServerType(serverType);

    return InitData();
}

int NFGameDay::InitData()
{
    memset(&m_stData, 0, sizeof(m_stData));
    m_stData.game_id = m_gameId;
    m_stData.room_id = m_roomId;
    std::string strTime = NFTime::Now().GetFormatDate();
    std::string strGame = NF_FORMAT("-{}-{}", m_gameId, m_roomId);
    m_stData.date_id = strTime + strGame;
    m_stData.stat_time = strTime;
    m_bDataInited = false;
    MarkDirty();
    CHECK_EXPR( m_stData.date_id.Size() > 0, -1, "error: {}", m_stData.date_id.GetString());
    return 0;
}

std::string NFGameDay::GetDayStr() {
    return m_stData.date_id.GetString();
}

int NFGameDay::WeekTick()
{
    m_stData.pour_week = 0;
    m_stData.fee_week = 0;
    m_stData.win_week = 0;

    DayTick();
    return 0;
}

int NFGameDay::MonthTick()
{
    m_stData.pour_month = 0;
    m_stData.fee_month = 0;
    m_stData.win_month = 0;

    DayTick();
    return 0;
}

int NFGameDay::DayTick()
{
    uint64_t pour_week = m_stData.pour_week;
    uint64_t pour_month = m_stData.pour_month;
    uint64_t all_pour = m_stData.all_pour;

    uint64_t fee_week = m_stData.fee_week;
    uint64_t fee_month = m_stData.fee_month;
    uint64_t all_fee = m_stData.all_fee;

    uint64_t win_week = m_stData.win_week;
    uint64_t win_month = m_stData.win_month;
    uint64_t all_win = m_stData.all_win;

    int iRet = InitData();
    CHECK_RET(iRet, "InitData failed, date id:{} iRet:{}", GetDayStr(), iRet);

    m_stData.pour_week = pour_week;
    m_stData.pour_month = pour_month;
    m_stData.all_pour = all_pour;

    m_stData.fee_week = fee_week;
    m_stData.fee_month = fee_month ;
    m_stData.all_fee = all_fee;

    m_stData.win_week = win_week;
    m_stData.win_month = win_month;
    m_stData.all_win = all_win;

    MarkDirty();

    iRet = NFDBObjMgr::Instance()->LoadFromDB(this);
    CHECK_RET(iRet, "LoadFromDB failed, date id:{} iRet:{}", GetDayStr(), iRet);
    return 0;
}

int NFGameDay::OnGameRoomStatInfo(const proto_ff::GameRoomStat& req)
{
    m_stData.pour_day += req.cur_pour();
    m_stData.pour_week += req.cur_pour();
    m_stData.pour_month += req.cur_pour();
    m_stData.all_pour += req.cur_pour();

    m_stData.fee_day += req.cur_fee();
    m_stData.fee_week += req.cur_fee();
    m_stData.fee_month += req.cur_fee();
    m_stData.all_fee += req.cur_fee();

    m_stData.win_day += req.cur_win();
    m_stData.win_week += req.cur_win();
    m_stData.win_month += req.cur_win();
    m_stData.all_win += req.cur_win();

    MarkDirty();
    return 0;
}