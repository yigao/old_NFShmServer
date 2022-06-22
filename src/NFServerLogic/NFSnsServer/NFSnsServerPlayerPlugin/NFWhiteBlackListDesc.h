// -------------------------------------------------------------------------
//    @FileName         :    NFWhiteBlackListDesc.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFWhiteBlackListDesc.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFIDescStore.h"
#include "NFComm/NFShmCore/NFShmMgr.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"
#include "NFComm/NFCore/NFRandom.hpp"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include <map>
#include <algorithm>

#define MAX_WHITE_BLACK_LIST_SIZE 5000

class NFWhiteBlackListDesc : public NFIDescStore
{
public:
    NFWhiteBlackListDesc();
    virtual ~NFWhiteBlackListDesc();
    int CreateInit();
    int ResumeInit();

    proto_ff_s::tbGameUserManagerData_s* GetDescByID(uint64_t ID);
    proto_ff_s::tbGameUserManagerData_s* GetDesc(uint64_t userId, uint32_t gameId, uint32_t roomId);
    proto_ff_s::tbGameUserManagerData_s* GetDesc(const proto_ff_s::tbGameUserManagerData_s& desc);
    proto_ff_s::tbGameUserManagerData_s* InsertDesc(const proto_ff_s::tbGameUserManagerData_s& desc);
    proto_ff_s::tbGameUserManagerData_s* InsertDesc(const proto_ff::tbGameUserManagerData& desc);
    int32_t DeleteDesc(const proto_ff_s::tbGameUserManagerData_s& desc);
    int32_t DeleteDesc(uint64_t userId, uint32_t gameId, uint32_t roomId);

    //must be virtual
    virtual void OnTimer(int timeId, int callcount);
public:
    uint64_t m_maxId;
    int32_t m_secTimer;
IMPL_RES_DESC(proto_ff_s::tbGameUserManagerData_s, tbGameUserManagerData, MAX_WHITE_BLACK_LIST_SIZE);
DECLARE_IDCREATE(NFWhiteBlackListDesc);
};