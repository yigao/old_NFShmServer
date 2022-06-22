// -------------------------------------------------------------------------
//    @FileName         :    NFBankAction.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFBankAction.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFIDynamicModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFStatusAction.h"

class NFTestRobot;

class NFBankAction : public StatusAction
{
public:
    enum {
        BANK_STATUS_NONE = 0,
        BANK_STATUS_GET_DATA_REQ = 1,
        BANK_STATUS_GET_DATA_SUCCESS = 2,
        BANK_STATUS_SAVE_JETTON_REQ = 3,
        BANK_STATUS_SAVE_JETTON_FAILED = 4,
        BANK_STATUS_SAVE_JETTON_SUCCESS = 5,
        BANK_STATUS_GET_JETTON_REQ = 6,
        BANK_STATUS_GET_JETTON_FAILED = 7,
        BANK_STATUS_GET_JETTON_SUCCESS = 8,
        BANK_STATUS_GIVE_JETTON_REQ = 9,
        BANK_STATUS_GIVE_JETTON_FAILED = 10,
        BANK_STATUS_GIVE_JETTON_SUCCESS = 11,
        BANK_STATUS_GET_RECORD_REQ = 12,
        BANK_STATUS_GET_RECORD_FAILED = 13,
        BANK_STATUS_GET_RECORD_SUCCESS = 14,
    };
    NFBankAction(NFIPluginManager* pPluginManager, NFTestRobot* p) : StatusAction(pPluginManager, p)
    {
        mStatus = BANK_STATUS_NONE;
        mJetton = 0;
        mBankJetton = 0;
    }

    virtual ~NFBankAction()
    {

    }

    virtual bool Awake();

    virtual int OnHandleAction();
    virtual int OnHandleMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);

    int OnHandleBankGetDataRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleBankSaveJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleBankGetJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleBankSetPasswordRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleBankGiveJettonRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleBankGetRecordRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleGetCommonRankRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);

    int OnHandleQueryUserRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);

    void SendBankGetDataReq();
    void SendGetCommonRankReq();
    void SendCheckUserrReq(uint64_t userId);
    void SendSaveJettonReq(uint64_t jetton);
    void SendGetJettonReq(uint64_t jetton);
    void SendChangPassword();
    void SendGiveJettonReq(uint64_t userId, uint64_t jetton);
    void SendGetRecordReq();

    uint32_t mStatus;
    uint64_t mJetton;
    uint64_t mBankJetton;
};
