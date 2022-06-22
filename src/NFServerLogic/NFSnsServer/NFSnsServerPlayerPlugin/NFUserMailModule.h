// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailModule.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailModule.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServer/NFCommHead/NFIUserMailModule.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
class NFUserMail;

class NFCUserMailModule : public NFIUserMailModule
{
public:
    NFCUserMailModule(NFIPluginManager* p);
    virtual ~NFCUserMailModule();

    virtual bool Awake();
    virtual bool Init();
    virtual void OnTimer(uint32_t nTimerID);
    virtual bool Execute();
    virtual int OnExecute(uint32_t nEventID, uint64_t nSrcID, uint32_t bySrcType, const google::protobuf::Message& message);
public:
    int OnHandleMailListReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
    int OnHandleMailCreateReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
    int OnHandleMailReadReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
    int OnHandleMailDelReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
    int OnHandleMailGetItemReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
    int OnHandleMailReadItemRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char *msg, uint32_t nLen);
};