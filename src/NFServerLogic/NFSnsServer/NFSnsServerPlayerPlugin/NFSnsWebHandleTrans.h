// -------------------------------------------------------------------------
//    @FileName         :    NFSnsWebHandleTrans
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSnsWebHandleTrans.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransSnsBase.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFMessageDefine/proto_svr_rank.pb.h"

class NFSnsWebHandleTrans : public NFTransSnsBase
{
public:
    NFSnsWebHandleTrans();

    virtual ~NFSnsWebHandleTrans();

    int CreateInit();

    int ResumeInit();

    virtual int HandleCSMsgReq(const google::protobuf::Message *pCSMsgReq);
public:
    int InitThisTrans(uint64_t userId, uint64_t requestId, uint32_t cmd);
    virtual int QueryRole_CallBack(tagQueryRole& query);
    virtual int QueryRole(tagQueryRole& query);
    virtual int QueryRole(uint64_t roleID);
    virtual int QueryRole();
    int DoQuery();
    int DoAgentQuery();
    int CheckAgentQuery();
    virtual int HandleGetRoleRes(int iRunLogicRetCode, uint64_t roleID);
public:
    int OnTransFinished(int iRunLogicRetCode);
    int HandleTransFinished(int iRunLogicRetCode) { return 0; }
    virtual int OnTimeOut() { return 0; }
private:
    uint64_t m_requestId;
    uint64_t m_userId;
    uint32_t m_cmd;
    uint32_t m_BaoDi;
    uint32_t m_taxBaoDi;
    uint64_t m_agentId;
    uint64_t m_liuShui;
    uint64_t m_tmpAgentId;
    uint64_t m_countAgentId;
DECLARE_IDCREATE(NFSnsWebHandleTrans)
};
