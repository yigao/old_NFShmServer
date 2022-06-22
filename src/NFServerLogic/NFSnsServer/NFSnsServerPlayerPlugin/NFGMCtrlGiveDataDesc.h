// -------------------------------------------------------------------------
//    @FileName         :    NFGMCtrlGiveDataDesc.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGMCtrlGiveDataDesc.h
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

#define MAX_GM_CTRL_GIVE_DATA_LIST_SIZE 5000

class NFGMCtrlGiveDataDesc : public NFIDescStore
{
public:
    NFGMCtrlGiveDataDesc();
    virtual ~NFGMCtrlGiveDataDesc();
    int CreateInit();
    int ResumeInit();

    proto_ff_s::tbGmCtrlGiveCtrlData_s* GetDescByID(uint64_t ID);
    proto_ff_s::tbGmCtrlGiveCtrlData_s* GetDesc(uint64_t userId, uint32_t gameId);
    proto_ff_s::tbGmCtrlGiveCtrlData_s* GetDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc);
    proto_ff_s::tbGmCtrlGiveCtrlData_s* InsertDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc);
    proto_ff_s::tbGmCtrlGiveCtrlData_s* InsertDesc(const proto_ff::tbGmCtrlGiveCtrlData& desc);
    int32_t DeleteDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc);
    int32_t DeleteDesc(uint64_t userId, uint32_t gameId);

    //must be virtual
    virtual void OnTimer(int timeId, int callcount);
public:
    uint64_t m_maxId;
    int32_t m_secTimer;
IMPL_RES_DESC(proto_ff_s::tbGmCtrlGiveCtrlData_s, tbGmCtrlGiveCtrlData, MAX_GM_CTRL_GIVE_DATA_LIST_SIZE);
DECLARE_IDCREATE(NFGMCtrlGiveDataDesc);
};