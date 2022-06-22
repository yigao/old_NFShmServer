// -------------------------------------------------------------------------
//    @FileName         :    NFBankAction.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFBankAction.cpp
//
// -------------------------------------------------------------------------

#include "NFBankAction.h"
#include "NFTestRobot.h"

#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFComm/NFCore/NFRandom.hpp"
#include "NFRobotModule.h"
#include "NFComm/NFMessageDefine/proto_common.pb.h"

bool NFBankAction::Awake()
{
    return true;
}

int NFBankAction::OnHandleMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    switch(nMsgId)
    {
        case proto_bank::NF_SC_BANK_GET_DATA_RSP:
        {
            OnHandleBankGetDataRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_bank::NF_SC_BANK_SAVE_MONEY_RSP:
        {
            OnHandleBankSaveJettonRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_bank::NF_SC_BANK_GET_MONEY_RSP:
        {
            OnHandleBankGetJettonRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_bank::NF_SC_BANK_SET_PASSWORD_RSP:
        {
            OnHandleBankSetPasswordRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_bank::NF_SC_BANK_GIVE_BANK_JETTON_RSP:
        {
            OnHandleBankGiveJettonRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_bank::NF_SC_BANK_GET_RECORD_RSP:
        {
            OnHandleBankGetRecordRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_rank::NF_CS_GET_COMMON_RANK_RSP:
        {
            OnHandleGetCommonRankRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_login::NF_SC_QUERY_USER_SIMPLE_DATA_RSP:
        {
            OnHandleQueryUserRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        default:
            break;
    }
    return true;
}

int NFBankAction::OnHandleAction()
{
    if (mStatus == BANK_STATUS_NONE)
    {
        SendBankGetDataReq();
    }
    else if (mStatus == BANK_STATUS_GET_DATA_SUCCESS)
    {
        SendSaveJettonReq(100);
    }
    else if (mStatus == BANK_STATUS_SAVE_JETTON_FAILED)
    {
        SendSaveJettonReq(10);
    }
    else if (mStatus == BANK_STATUS_SAVE_JETTON_SUCCESS)
    {
        SendGetJettonReq(10);
    }
    else if (mStatus == BANK_STATUS_GET_JETTON_FAILED)
    {
        SendGetJettonReq(1);
    }
    else if (mStatus == BANK_STATUS_GET_JETTON_SUCCESS)
    {
        SendGiveJettonReq(FindModule<NFCRobotModule>()->GetRandRobotUserId(), 1);
    }
    else if (mStatus == BANK_STATUS_GIVE_JETTON_SUCCESS || mStatus == BANK_STATUS_GIVE_JETTON_FAILED)
    {
       SendGetRecordReq();
    }
    else if (mStatus == BANK_STATUS_GET_RECORD_SUCCESS || mStatus == BANK_STATUS_GET_RECORD_FAILED)
    {
        SendBankGetDataReq();
    }
    return 0;
}

void NFBankAction::SendBankGetDataReq()
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendBankGetDataReq...........", m_pRobot->m_robotId);
    proto_bank::Proto_CSBankGetDataReq req;
    req.set_bank_password("8888");

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_GET_DATA_REQ, req);
    mStatus = BANK_STATUS_GET_DATA_REQ;
    SendGetCommonRankReq();
}

void NFBankAction::SendGetCommonRankReq()
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendGetCommonRankReq...........", m_pRobot->m_robotId);
    proto_rank::Proto_CSGetCommonRankReq req;
    req.set_rank_type(proto_ff::E_RANK_TYPE_GOLD);
    req.set_rank_from(1);
    req.set_rank_to(10);

    m_pRobot->SendMsgToServer(proto_rank::NF_CS_GET_COMMON_RANK_REQ, req);
}

void NFBankAction::SendCheckUserrReq(uint64_t userId)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendGetCommonRankReq...........", m_pRobot->m_robotId);
    proto_login::Proto_CSQueryUserReq req;
    req.add_query_user_id(userId);

    m_pRobot->SendMsgToServer(proto_login::NF_CS_QUERY_USER_SIMPLE_DATA_REQ, req);
}

void NFBankAction::SendSaveJettonReq(uint64_t jetton)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendSaveJettonReq...........", m_pRobot->m_robotId);
    proto_bank::Proto_CSBankSaveMoneyReq req;
    req.set_save_jetton(jetton);

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_SAVE_MONEY_REQ, req);
    mStatus = BANK_STATUS_SAVE_JETTON_REQ;
}

void NFBankAction::SendGetJettonReq(uint64_t jetton)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendGetJettonReq...........", m_pRobot->m_robotId);
    proto_bank::Proto_CSBankGetMoneyReq req;
    req.set_get_jetton(jetton);

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_GET_MONEY_REQ, req);
    mStatus = BANK_STATUS_GET_JETTON_REQ;
}

void NFBankAction::SendGiveJettonReq(uint64_t userId, uint64_t jetton)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendGetJettonReq...........", m_pRobot->m_robotId);
    if (userId == 0)
    {
        userId = m_pRobot->m_playerId;
    }

    SendCheckUserrReq(userId);

    proto_bank::Proto_CSBankGiveMoneyReq req;
    req.set_give_user_id(userId);
    req.set_give_jetton(jetton);

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_GIVE_BANK_JETTON_REQ, req);
    mStatus = BANK_STATUS_GIVE_JETTON_REQ;
}

void NFBankAction::SendGetRecordReq()
{
    proto_bank::Proto_CSBankGetRecordReq req;
    req.set_begin(1);
    req.set_end(10);

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_GET_RECORD_REQ, req);
    mStatus = BANK_STATUS_GET_RECORD_REQ;
}

void NFBankAction::SendChangPassword()
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} SendGetJettonReq...........", m_pRobot->m_robotId);
    proto_bank::Proto_CSBankSetPasswordReq req;
    int rand = NFRandomInt(1, 100);
    if (rand > 50)
    {
       req.set_old_password("123456");
       req.set_new_password("12345678");
    }
    else
    {
        req.set_old_password("12345678");
        req.set_new_password("123456");
    }

    m_pRobot->SendMsgToServer(proto_bank::NF_CS_BANK_SET_PASSWORD_REQ, req);
}

int NFBankAction::OnHandleBankGetDataRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                         uint32_t nLen) {

    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankGetDataRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_SCBankGetDataRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result() == 0)
    {
        mJetton = xMsg.jetton();
        mBankJetton = xMsg.bank_jetton();
        mStatus = BANK_STATUS_GET_DATA_SUCCESS;
    } else {
        mStatus = BANK_STATUS_NONE;
    }
    return 0;
}

int NFBankAction::OnHandleBankSaveJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                            uint32_t nLen) {
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankSaveJettonRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_SCBankSaveMoneyRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result() == 0)
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "save jetton to bank success, jetton:{} bank_jetton:{}...........", xMsg.jetton(), xMsg.bank_jetton());
        mJetton = xMsg.jetton();
        mBankJetton = xMsg.bank_jetton();
        mStatus = BANK_STATUS_SAVE_JETTON_SUCCESS;
    }
    else
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "save jetton to bank failed, errorId:{} jetton:{} bank_jetton:{}...........", xMsg.result(), xMsg.jetton(), xMsg.bank_jetton());
        mJetton = xMsg.jetton();
        mBankJetton = xMsg.bank_jetton();
        mStatus = BANK_STATUS_SAVE_JETTON_FAILED;
    }
    return 0;
}

int NFBankAction::OnHandleBankGetJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                           uint32_t nLen) {
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankSaveJettonRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_SCBankGetMoneyRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result() == 0)
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "get jetton to bank success, jetton:{} bank_jetton:{}...........", xMsg.jetton(), xMsg.bank_jetton());
        mJetton = xMsg.jetton();
        mBankJetton = xMsg.bank_jetton();
        mStatus = BANK_STATUS_GET_JETTON_SUCCESS;
    }
    else
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "get jetton to bank failed,errorId:{} jetton:{} bank_jetton:{}...........", xMsg.result(), xMsg.jetton(), xMsg.bank_jetton());
        mJetton = xMsg.jetton();
        mBankJetton = xMsg.bank_jetton();
        mStatus = BANK_STATUS_GET_JETTON_FAILED;
    }
    return 0;
}

int NFBankAction::OnHandleBankSetPasswordRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg,
                                             uint32_t nLen) {
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankSetPasswordRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_SCBankSetPasswordRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result())
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "Set Password Success...........");
    }
    else
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "Set Password Failed...........");
    }
    return 0;
}

int NFBankAction::OnHandleBankGiveJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankGiveJettonRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_CSBankGiveMoneyRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result())
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "give money Success...........");
        mStatus = BANK_STATUS_GIVE_JETTON_SUCCESS;
    }
    else
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "give money Failed...........");
        mStatus = BANK_STATUS_GIVE_JETTON_FAILED;
    }
    return 0;
}

int NFBankAction::OnHandleBankGetRecordRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleBankGetRecordRsp...........", m_pRobot->m_robotId);
    proto_bank::Proto_SCBankGetRecordRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    if (xMsg.result())
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "get record Success...........");
        mStatus = BANK_STATUS_GET_RECORD_SUCCESS;
    }
    else
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "give record Failed...........");
        mStatus = BANK_STATUS_GET_RECORD_FAILED;
    }

    return 0;
}

int NFBankAction::OnHandleGetCommonRankRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleGetCommonRankRsp...........", m_pRobot->m_robotId);
    proto_rank::Proto_SCGetCommonRankRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);
    return 0;
}

int NFBankAction::OnHandleQueryUserRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "robot:{} OnHandleQueryUserRsp...........", m_pRobot->m_robotId);
    proto_login::Proto_SCQueryUserRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);
    return 0;
}

