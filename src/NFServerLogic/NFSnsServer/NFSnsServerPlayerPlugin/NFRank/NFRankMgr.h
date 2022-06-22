// -------------------------------------------------------------------------
//    @FileName         :    NFRankMgr.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRankMgr.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFShmCore/NFArray.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"

#define MAX_RANK_LIST 10

class NFRankCommon;
class NFRankMgr : public NFShmObj
{
public:
    NFRankMgr();
    virtual ~NFRankMgr();
    //非继承函数, 不要加virtual
    int CreateInit();
    //非继承函数, 不要加virtual
    int ResumeInit();
public:
    int Init();
    int InitOneRank(proto_ff::enRankType rankType);
    //must be virtual
    virtual void OnTimer(int timeId, int callcount);
public:
    NFRankCommon* GetRank(proto_ff::enRankType eRankType);
    int Remove(proto_ff::enRankType eRankType, uint64_t iID);
    int DeleteWithAll(uint64_t iID);
    int UpdateRank(proto_ff::enRankType eRankType, const proto_ff::RankCommonScore* score, int& old_rank, int& new_rank);
private:
    bool m_bInited;
    NFArray<int, MAX_RANK_LIST> m_rankObjId;
    int m_checkTimer;
DECLARE_IDCREATE(NFRankMgr)
};