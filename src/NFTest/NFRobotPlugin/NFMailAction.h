// -------------------------------------------------------------------------
//    @FileName         :    NFStatusAction.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFStatusAction.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFIDynamicModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFComm/NFMessageDefine/proto_cs_email.pb.h"
#include "NFStatusAction.h"

class NFTestRobot;

class NFMailAction : public StatusAction
{
public:
    enum {
        MAIL_STATUS_NONE = 0,
        MAIL_STATUS_GET_LIST_MAIL_REQ = 1,
        MAIL_STATUS_GET_LIST_MAIL = 2,
        MAIL_STATUS_READ_MAIL = 3,
        MAIL_STATUS_READ_MAIL_SUCCESS = 4,
        MAIL_STATUS_DEL_MAIL = 5,
        MAIL_STATUS_DEL_MAIL_SUCCESS = 6,
        MAIL_STATUS_READ_ALL_MAIL_SUCCESS = 7,
        MAIL_STATUS_MAX = 6,
    };
    NFMailAction(NFIPluginManager* pPluginManager, NFTestRobot* p) : StatusAction(pPluginManager, p)
    {
        mStatus = MAIL_STATUS_NONE;
    }

    virtual ~NFMailAction()
    {

    }

    virtual bool Awake();

    virtual bool Finalize();

    virtual int OnHandleAction();
    virtual int OnHandleMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);

    void SendGetMailListReq();
    void ReadOneMailReq();
    void DelOneMailReq();

    int OnHandleMailListRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleMailReadRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleMailGetItemRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleMailNtf(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);
    int OnHandleMailDelRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen);

    proto_email::Proto_CSMailListRsp m_mailList;
    uint32_t mStatus;
};