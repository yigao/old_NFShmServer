// -------------------------------------------------------------------------
//    @FileName         :    NFSystemDay.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSystemDay.cpp
//
// -------------------------------------------------------------------------

#include "NFSystemDay.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFCommon.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFShmCore/NFDBObjMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFComm/NFCore/NFMagicTimeUtil.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"

#include "NFSystemStat.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFSystemDay, EOT_LOG_SYSTEM_DAY_ID, NFBaseDBObj)

NFSystemDay::NFSystemDay()
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

NFSystemDay::~NFSystemDay()
{

}

int NFSystemDay::CreateInit() {
    memset(&m_stData, 0, sizeof(m_stData));
    return 0;
}

int NFSystemDay::ResumeInit() {
    return 0;
}

int NFSystemDay::MakeLoadData(google::protobuf::Message* data)
{
    CHECK_NULL(data);
    if (m_bDataInited) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "aleady inited !" );
        return -1;
    }

    proto_ff::tbLogSystemDay* p = dynamic_cast<proto_ff::tbLogSystemDay*>(data);
    CHECK_NULL(p);
    p->set_date_id(m_stData.date_id.GetString());

    return 0;
}

int NFSystemDay::MakeSaveData(google::protobuf::Message* data)
{
    if ( !m_bDataInited ) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "not init!" );
        return -1;
    }
    CHECK_NULL(data);

    proto_ff::tbLogSystemDay* p = dynamic_cast<proto_ff::tbLogSystemDay*>(data);
    CHECK_NULL(p);
    proto_ff_s::tbLogSystemDay_s::write_to_pbmsg(m_stData, *p);

    return 0;
}

int NFSystemDay::InitWithDBData(const std::string* data)
{
    CHECK_NULL( data );
    proto_ff::tbLogSystemDay pb;
    bool ok = pb.ParseFromString(*data);
    CHECK_EXPR( ok, -1, "parse failed!");
    proto_ff_s::tbLogSystemDay_s::read_from_pbmsg(pb, m_stData);
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init with db data: {} ", m_stData.date_id.GetString());

    m_bDataInited = true;
    return 0;
}

int NFSystemDay::InitWithoutDBData()
{
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init without db data: date_id:{} ", m_stData.date_id.GetString());
    m_bDataInited = true;
    MarkDirty();
    return 0;
}

int NFSystemDay::Init(NF_SERVER_TYPES serverType)
{
    SetServerType(serverType);
    return InitData();
}

int NFSystemDay::InitData()
{
    memset(&m_stData, 0, sizeof(m_stData));
    m_stData.date_id = NFTime::Now().GetFormatDate();
    m_bDataInited = false;
    MarkDirty();
    CHECK_EXPR( m_stData.date_id.Size() > 0, -1, "error: {}", m_stData.date_id.GetString());
    return 0;
}

std::string NFSystemDay::GetDayStr() {
    return m_stData.date_id.GetString();
}

int NFSystemDay::OnPlayerLogin(NFSnsUserSimple *pSimple, NFOnlineUser *pUser) {
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    m_stData.login_count++;

    uint32_t maxOnline = NFOnlineUser::GetUsedCount();
    if (maxOnline > m_stData.max_online)
    {
        m_stData.max_online = maxOnline;
    }

    MarkDirty();

    NFSystemStat::Instance()->OnPlayerLogin(pSimple, pUser);
    return 0;
}

int NFSystemDay::OnPlayerLogout(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    CountValidPlayer(pSimple, pUser);

    NFSystemStat::Instance()->OnPlayerLogout(pSimple, pUser);
    return 0;
}

int NFSystemDay::CountValidPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    if (NFTime::Now().UnixSec() - pUser->GetLastLoginTime() >= MAX_VALID_PLAYER_STAT_TIME)
    {
        if (!NFMagicTimeUtil::IsSameDayStd(pSimple->m_userData.misc_data.last_valid_player_time, NFTime::Now().UnixSec()))
        {
            pSimple->m_userData.misc_data.last_valid_player_time = NFTime::Now().UnixSec();
            m_stData.valid_player++;
            MarkDirty();

            NFSystemStat::Instance()->CountValidPlayer();
        }
    }

    return 0;
}

int NFSystemDay::OnNewPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    m_stData.active_player++;
    m_stData.new_player++;
    MarkDirty();

    NFSystemStat::Instance()->OnNewPlayer(pSimple, pUser);
    return 0;
}

int NFSystemDay::DayTick()
{
    GetSystemDataFromSystemStat();
    MarkDirty();

    NFDBObjMgr::Instance()->SaveToDB(this);

    int iRet = InitData();
    CHECK_RET(iRet, "InitData Fail, system day:{} iRet:{}", GetDayStr(), iRet);

    m_stData.jetton_init = NFSystemStat::Instance()->GetAllJetton();
    GetTodayFromSystemStat();
    GetSystemDataFromSystemStat();

    MarkDirty();

    iRet = NFDBObjMgr::Instance()->LoadFromDB(this);
    CHECK_RET(iRet, "LoadFromDB failed, system day:{} iRet:{}", GetDayStr(), iRet);
    return 0;
}

int NFSystemDay::GetSystemDataFromSystemStat()
{
    m_stData.all_jetton = NFSystemStat::Instance()->GetAllJetton();
    m_stData.all_bank_jetton = NFSystemStat::Instance()->GetData().all_bank_jetton;
    m_stData.player_jetton = NFSystemStat::Instance()->GetData().player_jetton;

    m_stData.pour_week_all = NFSystemStat::Instance()->GetData().pour_week_all;
    m_stData.pour_month_all = NFSystemStat::Instance()->GetData().pour_month_all;

    m_stData.sys_win_week = NFSystemStat::Instance()->GetData().sys_win_week;
    m_stData.sys_win_month = NFSystemStat::Instance()->GetData().sys_win_month;

    m_stData.fee_week = NFSystemStat::Instance()->GetData().fee_week;
    m_stData.fee_month = NFSystemStat::Instance()->GetData().fee_month;

    m_stData.pay_week = NFSystemStat::Instance()->GetData().pay_week;
    m_stData.pay_month = NFSystemStat::Instance()->GetData().pay_month;;

    m_stData.commision_week = NFSystemStat::Instance()->GetData().commision_week;
    m_stData.commision_month = NFSystemStat::Instance()->GetData().commision_month;

    m_stData.zhuangzhang_week = NFSystemStat::Instance()->GetData().zhuangzhang_week;
    m_stData.zhuangzhang_month = NFSystemStat::Instance()->GetData().zhuangzhang_month;

    m_stData.vip_pay_week = NFSystemStat::Instance()->GetData().vip_pay_week;
    m_stData.vip_pay_month = NFSystemStat::Instance()->GetData().vip_pay_month;

    m_stData.trd_pay_week = NFSystemStat::Instance()->GetData().trd_pay_week;
    m_stData.trd_pay_month = NFSystemStat::Instance()->GetData().trd_pay_month;

    m_stData.draw_week = NFSystemStat::Instance()->GetData().draw_week;
    m_stData.draw_month = NFSystemStat::Instance()->GetData().draw_month;

    m_stData.give_week = NFSystemStat::Instance()->GetData().give_week;
    m_stData.give_month = NFSystemStat::Instance()->GetData().give_month;

    m_stData.week_vip_zhuanru = NFSystemStat::Instance()->GetData().week_vip_zhuanru;
    m_stData.month_vip_zhuanru = NFSystemStat::Instance()->GetData().month_vip_zhuanru;

    m_stData.week_vip_zhuanchu = NFSystemStat::Instance()->GetData().week_vip_zhuanchu;
    m_stData.month_vip_zhuanchu = NFSystemStat::Instance()->GetData().month_vip_zhuanchu;

    m_stData.commision_all = NFSystemStat::Instance()->GetData().commision_all;
    m_stData.all_fee = NFSystemStat::Instance()->GetData().all_fee;
    m_stData.all_pour = NFSystemStat::Instance()->GetData().all_pour;
    m_stData.all_win = NFSystemStat::Instance()->GetData().all_win;
    m_stData.pay_all = NFSystemStat::Instance()->GetData().pay_all;
    m_stData.zhuangzhang_all = NFSystemStat::Instance()->GetData().zhuangzhang_all;
    m_stData.vip_pay_all = NFSystemStat::Instance()->GetData().vip_pay_all;
    m_stData.trd_pay_all = NFSystemStat::Instance()->GetData().trd_pay_all;
    m_stData.all_draw = NFSystemStat::Instance()->GetData().all_draw;
    m_stData.all_give = NFSystemStat::Instance()->GetData().all_give;
    m_stData.all_vip_zhuanru = NFSystemStat::Instance()->GetData().all_vip_zhuanru;
    m_stData.all_vip_zhuanchu = NFSystemStat::Instance()->GetData().all_vip_zhuanchu;

    MarkDirty();

    return 0;
}

int NFSystemDay::GetTodayFromSystemStat()
{
    m_stData.pour_day_all = NFSystemStat::Instance()->GetData().pour_day_all;
    m_stData.sys_win_day = NFSystemStat::Instance()->GetData().sys_win_day;
    m_stData.fee_day = NFSystemStat::Instance()->GetData().fee_day;
    m_stData.pay_day = NFSystemStat::Instance()->GetData().pay_day;
    m_stData.commision_day = NFSystemStat::Instance()->GetData().commision_day;
    m_stData.zhuangzhang_day = NFSystemStat::Instance()->GetData().zhuangzhang_day;
    m_stData.vip_pay_all = NFSystemStat::Instance()->GetData().vip_pay_all;
    m_stData.trd_pay_all = NFSystemStat::Instance()->GetData().trd_pay_all;
    m_stData.draw_day = NFSystemStat::Instance()->GetData().draw_day;
    m_stData.jetton_out = NFSystemStat::Instance()->GetData().jetton_out;
    m_stData.give_day = NFSystemStat::Instance()->GetData().give_day;
    m_stData.today_vip_zhuanru = NFSystemStat::Instance()->GetData().today_vip_zhuanru;
    m_stData.today_vip_zhuanchu = NFSystemStat::Instance()->GetData().today_vip_zhuanchu;

    MarkDirty();
    return 0;
}

int NFSystemDay::OnPlayerJettonChangeStat(const proto_ff::Proto_PlayerJettonChangeStatReq& req)
{
    NFSystemStat::Instance()->OnPlayerJettonChangeStat(req);

    if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_RECHARGE)
    {
        m_stData.jetton_in += req.money_change();
        m_stData.pay_times++;

        if (req.is_first_recharge())
        {
            m_stData.new_pay_player++;
            m_stData.new_pay_all += req.money_change();
        }
    }

    GetTodayFromSystemStat();
    GetSystemDataFromSystemStat();

    MarkDirty();
    return 0;
}

int NFSystemDay::OnGameRoomStatInfo(const proto_ff::Proto_GameTSns_GameRoomStatInfoReq& req)
{
    NFSystemStat::Instance()->OnGameRoomStatInfo(req);

    GetTodayFromSystemStat();
    GetSystemDataFromSystemStat();

    MarkDirty();
    return 0;
}