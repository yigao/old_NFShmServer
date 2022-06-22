// -------------------------------------------------------------------------
//    @FileName         :    NFGetRankTrans.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGetRankTrans.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransSnsBase.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFMessageDefine/proto_svr_rank.pb.h"

class NFGetRankTrans : public NFTransSnsBase
{
public:
    NFGetRankTrans();

    virtual ~NFGetRankTrans();

    int CreateInit();

    int ResumeInit();
public:
    int InitThisTrans(uint64_t userId, proto_ff::enRankType eRankType);
    int AddScore( const proto_ff_s::RankCommonInfo_s& info, const proto_ff_s::RankCommonScore_s& score);
    int DoQuery();
public:
    virtual int QueryRole_CallBack(tagQueryRole& query);
    int MakeRankInfo(proto_ff::enRankType eRankType, const proto_ff_s::RankCommonScore_s& score, int iRank, proto_rank::RankInfo* out);
public:
    int OnTransFinished(int iRunLogicRetCode);
    int HandleTransFinished(int iRunLogicRetCode) { return 0; }
    virtual int OnTimeOut() { return 0; }
private:
    uint64_t m_userId;
    proto_ff::enRankType m_eRankType;

    NFArray<proto_ff_s::RankCommonInfo_s, MAX_QUERY_ROLE>    m_rank_list;
    NFArray<proto_ff_s::RankCommonScore_s, MAX_QUERY_ROLE>   m_score_list;

DECLARE_IDCREATE(NFGetRankTrans)
};
