// -------------------------------------------------------------------------
//    @FileName         :    NFSystemStat.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSystemStat.cpp
//
// -------------------------------------------------------------------------

#include "NFSystemStat.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFCore/NFCommon.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFShmCore/NFDBObjMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFComm/NFCore/NFMagicTimeUtil.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFSystemStat, EOT_LOG_SYSTEM_STAT_ID, NFBaseDBObj)

NFSystemStat::NFSystemStat()
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

NFSystemStat::~NFSystemStat()
{

}

int NFSystemStat::CreateInit() {
    memset(&m_stData, 0, sizeof(m_stData));
    return 0;
}

int NFSystemStat::ResumeInit() {
    return 0;
}

int NFSystemStat::MakeLoadData(google::protobuf::Message* data)
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

int NFSystemStat::MakeSaveData(google::protobuf::Message* data)
{
    if ( !m_bDataInited ) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "not init!" );
        return -1;
    }
    CHECK_NULL(data);

    proto_ff::tbLogSystemDay* p = dynamic_cast<proto_ff::tbLogSystemDay*>(data);
    CHECK_NULL(p);
    proto_ff_s::tbLogSystemDay_s::write_to_pbmsg(m_stData, *p);

//    p->clear_all_jetton();
//    p->clear_player_jetton();
//    p->clear_robot_jetton();
//    p->clear_freeze_jetton();

    return 0;
}

int NFSystemStat::InitWithDBData(const std::string* data)
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

int NFSystemStat::InitWithoutDBData()
{
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init without db data: date_id:{} ", m_stData.date_id.GetString());
    m_bDataInited = true;
    MarkDirty();
    return 0;
}

int NFSystemStat::Init(NF_SERVER_TYPES serverType)
{
    SetServerType(serverType);
    return InitData();
}

int NFSystemStat::InitData()
{
    memset(&m_stData, 0, sizeof(m_stData));
    m_stData.date_id = "All";
    m_bDataInited = false;
    MarkDirty();
    CHECK_EXPR( m_stData.date_id.Size() > 0, -1, "error: {}", m_stData.date_id.GetString());
    return 0;
}

std::string NFSystemStat::GetDayStr() {
    return m_stData.date_id.GetString();
}

int NFSystemStat::OnPlayerLogin(NFSnsUserSimple *pSimple, NFOnlineUser *pUser) {
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    m_stData.login_count++;

    uint32_t maxOnline = NFOnlineUser::GetUsedCount();
    if (maxOnline > m_stData.max_online)
    {
        m_stData.max_online = maxOnline;
    }

    MarkDirty();

    return 0;
}

int NFSystemStat::OnPlayerLogout(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    return 0;
}

int NFSystemStat::OnNewPlayer(NFSnsUserSimple* pSimple, NFOnlineUser* pUser)
{
    CHECK_NULL(pSimple);
    CHECK_NULL(pUser);

    m_stData.active_player++;
    m_stData.new_player++;
    MarkDirty();

    return 0;
}

int NFSystemStat::OnPlayerJettonChangeStat(const proto_ff::Proto_PlayerJettonChangeStatReq& req)
{
    if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_RECHARGE)
    {
        m_stData.pay_day += req.money_change();
        m_stData.pay_week += req.money_change();
        m_stData.pay_month += req.money_change();
        m_stData.pay_all += req.money_change();
        m_stData.pay_times++;

        m_stData.jetton_in += req.money_change();

        if (req.is_first_recharge())
        {
            m_stData.new_pay_player++;
            m_stData.new_pay_all += req.money_change();
        }

        if (req.opt_reason() == proto_ff::E_RECHARGE_PAY_TYPE_WEB_ZHUANGZHANG_PLATFORM)
        {
            m_stData.zhuangzhang_day += req.money_change();
            m_stData.zhuangzhang_week += req.money_change();
            m_stData.zhuangzhang_month += req.money_change();
            m_stData.zhuangzhang_all += req.money_change();
        }
        else if (req.opt_reason() == proto_ff::E_RECHARGE_PAY_TYPE_VIP_RECHARGE)
        {
            m_stData.vip_pay_day += req.money_change();
            m_stData.vip_pay_week += req.money_change();
            m_stData.vip_pay_month += req.money_change();
            m_stData.vip_pay_all += req.money_change();
        }
        else
        {
            m_stData.trd_pay_day += req.money_change();
            m_stData.trd_pay_week += req.money_change();
            m_stData.trd_pay_month += req.money_change();
            m_stData.trd_pay_all += req.money_change();
        }
    }
    else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_DRAW)
    {
        m_stData.draw_day += req.money_change();
        m_stData.draw_week += req.money_change();
        m_stData.draw_month += req.money_change();
        m_stData.all_draw += req.money_change();
    }

    if (req.account_type() == proto_ff::E_ACCOUNT_TYPE_JETTON)
    {
        if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_GAME_BALANCED_WIN)
        {
            m_stData.all_jetton += req.money_change();
            m_stData.player_jetton += req.money_change();
        }
        else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_GAME_BALANCED_LOST)
        {
            if (m_stData.all_jetton >= (uint64_t)req.money_change())
            {
                m_stData.all_jetton -= req.money_change();
            }
            else
            {
                m_stData.all_jetton = 0;
            }

            if (m_stData.player_jetton >= (uint64_t)req.money_change())
            {
                m_stData.player_jetton -= req.money_change();
            }
            else
            {
                m_stData.player_jetton = 0;
            }
        }
        else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_EXCHANGE)
        {
            if (req.opt_reason() == proto_ff::E_EXCHANGE_REASON_SAVE_MONEY)
            {
                if (m_stData.all_jetton >= (uint64_t)req.money_change())
                {
                    m_stData.all_jetton -= req.money_change();
                }
                else
                {
                    m_stData.all_jetton = 0;
                }

                if (m_stData.player_jetton >= (uint64_t)req.money_change())
                {
                    m_stData.player_jetton -= req.money_change();
                }
                else
                {
                    m_stData.player_jetton = 0;
                }
            }
            else if (req.opt_reason() == proto_ff::E_EXCHANGE_REASON_DRAW_MONEY)
            {
                m_stData.all_jetton += req.money_change();
                m_stData.player_jetton += req.money_change();
            }
        }
        else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_WEB_DEDUCT_NONEY)
        {
            if (m_stData.all_jetton >= (uint64_t)req.money_change())
            {
                m_stData.all_jetton -= req.money_change();
            }
            else
            {
                m_stData.all_jetton = 0;
            }

            if (m_stData.player_jetton >= (uint64_t)req.money_change())
            {
                m_stData.player_jetton -= req.money_change();
            }
            else
            {
                m_stData.player_jetton = 0;
            }

            m_stData.draw_day += req.money_change();
            m_stData.draw_week += req.money_change();
            m_stData.draw_month += req.money_change();
            m_stData.jetton_out += req.money_change();
            m_stData.all_draw += req.money_change();
        }
        else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_WEB_GIVE_MONEY)
        {
            m_stData.all_jetton += req.money_change();
            m_stData.player_jetton += req.money_change();

            m_stData.give_day += req.money_change();
            m_stData.give_week += req.money_change();
            m_stData.give_month += req.money_change();
            m_stData.all_give += req.money_change();
        }
        else
        {
            m_stData.all_jetton += req.money_change();
            m_stData.player_jetton += req.money_change();
        }
    }
    else if (req.account_type() == proto_ff::E_ACCOUNT_TYPE_BANK_JETTON)
    {
        if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_EXCHANGE)
        {
            if (req.opt_reason() == proto_ff::E_EXCHANGE_REASON_SAVE_MONEY)
            {
                m_stData.all_bank_jetton += req.money_change();
            }
            else if (req.opt_reason() == proto_ff::E_EXCHANGE_REASON_DRAW_MONEY)
            {
                if (m_stData.all_bank_jetton >= (uint64_t)req.money_change())
                {
                    m_stData.all_bank_jetton -= req.money_change();
                }
                else
                {
                    m_stData.all_bank_jetton = 0;
                }
            }
        }
        else if (req.opt_type() == proto_ff::E_USER_JETTON_OPER_TYPE_TRANSFER)
        {
            if (req.opt_reason() == proto_ff::E_TRANSFER_REASON_USER)
            {
                if (m_stData.all_bank_jetton >= (uint64_t)req.money_change())
                {
                    m_stData.all_bank_jetton -= req.money_change();
                }
                else
                {
                    m_stData.all_bank_jetton = 0;
                }
            }
            else if (req.opt_reason() == proto_ff::E_TRANSFER_REASON_FROM_USER)
            {
                m_stData.all_bank_jetton += req.money_change();
            }
            else if (req.opt_reason() == proto_ff::E_TRANSFER_REASON_VIP_ZHUANRU)
            {
                m_stData.today_vip_zhuanru += req.money_change();
                m_stData.week_vip_zhuanru += req.money_change();
                m_stData.month_vip_zhuanru += req.money_change();
                m_stData.all_vip_zhuanru += req.money_change();
                m_stData.all_bank_jetton += req.money_change();
            }
            else if (req.opt_reason() == proto_ff::E_TRANSFER_REASON_VIP_ZHUANCHU)
            {
                if (m_stData.all_bank_jetton >= (uint64_t)req.money_change())
                {
                    m_stData.all_bank_jetton -= req.money_change();
                }
                else
                {
                    m_stData.all_bank_jetton = 0;
                }
                m_stData.today_vip_zhuanchu += req.money_change();
                m_stData.week_vip_zhuanchu += req.money_change();
                m_stData.month_vip_zhuanchu += req.money_change();
                m_stData.all_vip_zhuanchu += req.money_change();
            }
        }
    }

    MarkDirty();

    return 0;
}

int NFSystemStat::CountValidPlayer()
{
    m_stData.valid_player++;
    MarkDirty();
    return 0;
}

int NFSystemStat::DayTick()
{
    m_stData.pour_day_all = 0;
    m_stData.sys_win_day = 0;
    m_stData.fee_day = 0;
    m_stData.commision_day = 0;
    m_stData.pay_day = 0;
    m_stData.draw_day = 0;
    m_stData.jetton_out = 0;
    m_stData.give_day = 0;
    m_stData.today_vip_zhuanchu = 0;
    m_stData.today_vip_zhuanru = 0;
    MarkDirty();
    return 0;
}

int NFSystemStat::WeekTick()
{
    DayTick();
    m_stData.pour_week_all = 0;
    m_stData.sys_win_week = 0;
    m_stData.fee_week = 0;
    m_stData.commision_week = 0;
    m_stData.pay_week = 0;
    m_stData.draw_week = 0;
    m_stData.give_week = 0;
    m_stData.week_vip_zhuanchu = 0;
    m_stData.week_vip_zhuanru = 0;
    MarkDirty();
    return 0;
}

int NFSystemStat::MonthTick()
{
    DayTick();
    m_stData.pour_month_all = 0;
    m_stData.sys_win_month = 0;
    m_stData.fee_month = 0;
    m_stData.commision_month = 0;
    m_stData.pay_month = 0;
    m_stData.draw_month = 0;
    m_stData.give_month = 0;
    m_stData.month_vip_zhuanchu = 0;
    m_stData.month_vip_zhuanru = 0;
    MarkDirty();
    return 0;
}

int NFSystemStat::OnGameRoomStatInfo(const proto_ff::Proto_GameTSns_GameRoomStatInfoReq& req)
{
    m_stData.fee_day += req.stat_info().cur_fee();
    m_stData.fee_week += req.stat_info().cur_fee();
    m_stData.fee_month += req.stat_info().cur_fee();
    m_stData.all_fee += req.stat_info().cur_fee();

    m_stData.pour_day_all += req.stat_info().cur_pour();
    m_stData.pour_week_all += req.stat_info().cur_pour();
    m_stData.pour_month_all += req.stat_info().cur_pour();
    m_stData.all_pour += req.stat_info().cur_pour();

    m_stData.sys_win_day += req.stat_info().cur_win();
    m_stData.sys_win_week += req.stat_info().cur_win();
    m_stData.sys_win_month += req.stat_info().cur_win();
    m_stData.all_win += req.stat_info().cur_win();

    MarkDirty();
    return 0;
}