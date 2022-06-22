// -------------------------------------------------------------------------
//    @FileName         :    NFRankMgr.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRankMgr.cpp
//
// -------------------------------------------------------------------------

#include "NFSystemStatMgr.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFShmCore/NFShmMgr.h"
#include "NFComm/NFShmCore/NFDBObjMgr.h"
#include "NFSystemDay.h"
#include "NFGameDay.h"
#include "NFSystemStat.h"
#include "NFComm/NFCore/NFMagicTimeUtil.h"
#include "NFComm/NFCore/NFTime.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFSystemStatMgr, EOT_SYSTEM_STAT_MGR_ID, NFShmObj)

NFSystemStatMgr::NFSystemStatMgr() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFSystemStatMgr::~NFSystemStatMgr() {
    if (m_checkTimer != INVALID_ID)
    {
        DeleteTimer(m_checkTimer);
        m_checkTimer = INVALID_ID;
    }

    if (m_dayTimer != INVALID_ID)
    {
        DeleteTimer(m_dayTimer);
        m_dayTimer = INVALID_ID;
    }

}

int NFSystemStatMgr::CreateInit() {
    m_bInited = false;
    m_checkTimer = INVALID_ID;
    m_dayTimer = INVALID_ID;
    return 0;
}

int NFSystemStatMgr::ResumeInit() {
    return 0;
}

void NFSystemStatMgr::OnTimer(int timeId, int callcount)
{
    if (m_checkTimer == timeId)
    {
        bool flag = true;

       if (!NFSystemDay::Instance()->IsDataInited())
       {
           flag = false;
       }

        if (flag)
        {
            DeleteTimer(m_checkTimer);
            m_checkTimer = INVALID_ID;
            NFIPluginManager::Instance()->FinishAppTask(NF_ST_SNS_SERVER, APP_INIT_LOAD_SYSTEM_STAT_DB, APP_INIT_STATUS_SERVER_LOAD_OBJ_FROM_DB);
        }
    }

    if (m_dayTimer == timeId)
    {
        DayTick();
    }
}

int NFSystemStatMgr::Init()
{
    if (m_bInited)
    {
        return 0;
    }

    m_checkTimer = SetTimer(1000, 0, 0, 0, 0, 0);
    m_dayTimer = SetDayCalender(0, 0, 0, 0);
    NFIPluginManager::Instance()->RegisterAppTask(NF_ST_SNS_SERVER, APP_INIT_LOAD_SYSTEM_STAT_DB, "Load System Stat From DB", APP_INIT_STATUS_SERVER_LOAD_OBJ_FROM_DB);

    int iRet = 0;
    iRet = InitSystemDay();
    CHECK_RET(iRet, "init system day faled, iRet:{}", iRet);

    iRet = InitGameDay(0, 0);
    CHECK_RET(iRet, "init game:{} day faled, iRet:{}", 2001, iRet);
    return 0;
}

int NFSystemStatMgr::InitSystemDay()
{
    NFSystemDay* pDay= NFSystemDay::Instance();
    CHECK_EXPR(pDay, -1, "Create NFSystemDay Failed, use count:{}", NFSystemDay::GetUsedCount());
    CHECK_EXPR(pDay->IsDataInited() == false, -1, "data_id:{} already inited!", pDay->GetDayStr());

    pDay->Init(NF_ST_SNS_SERVER);
    int iRet = NFDBObjMgr::Instance()->LoadFromDB(pDay);
    CHECK_RET(iRet, "inti failed, systtem day:{} iRet:{}", pDay->GetDayStr(), iRet);

    NFSystemStat* pStat= NFSystemStat::Instance();
    CHECK_EXPR(pStat, -1, "Create NFSystemDay Failed, use count:{}", NFSystemStat::GetUsedCount());
    CHECK_EXPR(pStat->IsDataInited() == false, -1, "data_id:{} already inited!", pStat->GetDayStr());

    pStat->Init(NF_ST_SNS_SERVER);
    iRet = NFDBObjMgr::Instance()->LoadFromDB(pStat);
    CHECK_RET(iRet, "inti failed, systtem day:{} iRet:{}", pStat->GetDayStr(), iRet);
    return 0;
}

int NFSystemStatMgr::InitGameDay(uint32_t gameId, uint32_t roomId)
{
    NFGameDay* pDay = GetGameDay(gameId, roomId);
    CHECK_EXPR(pDay == NULL, -1, "gameId:{} roomId:{} exist", gameId, roomId);

    uint64_t index = MAKE_UINT64(gameId, roomId);
    pDay = dynamic_cast<NFGameDay *>(NFShmMgr::Instance()->CreateObj(index, EOT_LOG_GAME_DAY_ID));
    CHECK_EXPR(pDay, -1, "Create Game Day Failed, gameId:{} roomId", gameId, roomId);
    CHECK_EXPR(pDay->IsDataInited() == false, -1, "data_id:{} already inited!", pDay->GetDayStr());

    pDay->Init(NF_ST_SNS_SERVER, gameId, roomId);
    int iRet = NFDBObjMgr::Instance()->LoadFromDB(pDay);
    CHECK_RET(iRet, "inti failed, systtem day:{} iRet:{}", pDay->GetDayStr(), iRet);

    return 0;
}

NFGameDay* NFSystemStatMgr::GetGameDay(uint32_t gameId, uint32_t roomId)
{
    uint64_t index = MAKE_UINT64(gameId, roomId);
    return dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetObjFromHashKey(index, EOT_LOG_GAME_DAY_ID));
}

int NFSystemStatMgr::DayTick()
{
    if (NFMagicTimeUtil::GetWeekDay127(NFTime::Now().UnixSec()) == 1)
    {
        NFSystemStat::Instance()->WeekTick();
        NFSystemDay::Instance()->DayTick();

        NFGameDay *pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetHeadObj(EOT_LOG_GAME_DAY_ID));
        while(pGameDay)
        {
            pGameDay->WeekTick();
            pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetNextObj(EOT_LOG_GAME_DAY_ID, pGameDay));
        }
    }
    else if (NFMagicTimeUtil::GetMonthDay(NFTime::Now().UnixSec()) == 1)
    {
        NFSystemStat::Instance()->MonthTick();
        NFSystemDay::Instance()->DayTick();

        NFGameDay *pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetHeadObj(EOT_LOG_GAME_DAY_ID));
        while(pGameDay)
        {
            pGameDay->MonthTick();
            pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetNextObj(EOT_LOG_GAME_DAY_ID, pGameDay));
        }
    }
    else
    {
        NFSystemStat::Instance()->DayTick();
        NFSystemDay::Instance()->DayTick();

        NFGameDay *pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetHeadObj(EOT_LOG_GAME_DAY_ID));
        while(pGameDay)
        {
            pGameDay->DayTick();
            pGameDay = dynamic_cast<NFGameDay*>(NFShmMgr::Instance()->GetNextObj(EOT_LOG_GAME_DAY_ID, pGameDay));
        }
    }

    return 0;
}

int NFSystemStatMgr::InitGameReg(uint32_t gameId, uint32_t roomId)
{
    CHECK_EXPR(gameId > 0 && roomId > 0, -1, "gameId:{} roomId:{} param error", gameId, roomId);

    NFGameDay* pGameDay = GetGameDay(gameId, roomId);
    if (pGameDay)
    {
        NFGameDay* pGame = GetGameDay(gameId, 0);
        if (!pGame)
        {
            int iRet = InitGameDay(gameId, 0);
            CHECK_EXPR(iRet == 0, -1, "InitGameDay gameId:{} roomId:{} failed!", gameId, 0);
        }
    }
    else
    {
        NFGameDay* pGame = GetGameDay(gameId, 0);
        if (!pGame)
        {
            int iRet = InitGameDay(gameId, 0);
            CHECK_EXPR(iRet == 0, -1, "InitGameDay gameId:{} roomId:{} failed!", gameId, 0);
        }

        int iRetCode = InitGameDay(gameId, roomId);
        CHECK_EXPR(iRetCode == 0, -1, "InitGameDay gameId:{} roomId:{} failed!", gameId, roomId);
    }
    return 0;
}
