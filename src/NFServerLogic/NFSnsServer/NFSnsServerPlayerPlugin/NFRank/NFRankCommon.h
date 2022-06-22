// -------------------------------------------------------------------------
//    @FileName         :    NFRankCommon.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRankCommon.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFBaseDBObj.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"

class NFRankCommon : public NFBaseDBObj
{
public:
    NFRankCommon();
    virtual ~NFRankCommon();

    //非继承函数, 不要加virtual
    int CreateInit();
    //非继承函数, 不要加virtual
    int ResumeInit();
public:
    int Init(NF_SERVER_TYPES serverType, int iRankTypeID);
public:
    int GetRankType() { return m_iRankTypeID; }
    int GetMaxRank() { return m_stData.body.score_list.GetSize() - 1; }
    int GetRank(uint64_t uID);
    int Remove(uint64_t iID);
    proto_ff_s::RankCommonInfo_s* GetRankInfo(uint64_t uID);
    int InsertRankInfo(uint64_t iID, int iRank);
    int DeleteRankInfo(uint64_t iID);
public:
    const proto_ff_s::RankCommonScore_s* GetRankScore(int iRank);
    int UpdateRank(const proto_ff_s::RankCommonScore_s* score, int& old_rank, int& new_rank);
    int UpdateRank(const proto_ff::RankCommonScore* score, int& old_rank, int& new_rank);
private:
    virtual int on_score_remove( proto_ff_s::RankCommonScore_s* score) { return 0; }
    virtual int on_score_change( proto_ff_s::RankCommonScore_s* score, int iRank) { return 0; }
private:
    int m_iRankTypeID;
    bool m_bDisableRankDown;
    proto_ff_s::tbRankCommon_s m_stData;
DECLARE_DB_OBJ_SETTING(proto_ff::E_TABLE_RANK_COMMON, tbRankCommon, RANK_MAX_SAVE_TIME, EN_DW_RETRY_ANY_SHUTDOWN);
DECLARE_IDCREATE(NFRankCommon)
};
