// -------------------------------------------------------------------------
//    @FileName         :    NFRankMgr.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRankMgr.cpp
//
// -------------------------------------------------------------------------

#include "NFRankMgr.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFShmCore/NFShmMgr.h"
#include "NFRankCommon.h"
#include "NFComm/NFShmCore/NFDBObjMgr.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFRankMgr, EOT_RANK_MGR_ID, NFShmObj)

NFRankMgr::NFRankMgr() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFRankMgr::~NFRankMgr() {

}

int NFRankMgr::CreateInit() {
    m_bInited = false;
    m_rankObjId.CreateInit();
    m_rankObjId.SetSize(m_rankObjId.GetMaxSize());
    m_checkTimer = INVALID_ID;
    return 0;
}

int NFRankMgr::ResumeInit() {
    return 0;
}

void NFRankMgr::OnTimer(int timeId, int callcount)
{
    if (m_checkTimer == timeId)
    {
        bool flag = true;
        for(int i = 0; i < m_rankObjId.GetSize(); i++)
        {
            NFRankCommon* pRank = dynamic_cast<NFRankCommon*>(NFShmMgr::Instance()->GetObjFromGlobalID(m_rankObjId[i], EOT_RANK_COMMON_ID, 0));
            if (pRank)
            {
                if (!pRank->IsDataInited())
                {
                    flag = false;
                    break;
                }
            }
        }

        if (flag)
        {
            DeleteTimer(m_checkTimer);
            m_checkTimer = INVALID_ID;
            NFIPluginManager::Instance()->FinishAppTask(NF_ST_SNS_SERVER, APP_INIT_LOAD_RANK_FROM_DB, APP_INIT_STATUS_SERVER_LOAD_OBJ_FROM_DB);
        }
    }
}

int NFRankMgr::Init()
{
    if (m_bInited)
    {
        return 0;
    }

    m_checkTimer = SetTimer(1000, 0, 0, 0, 0, 0);
    NFIPluginManager::Instance()->RegisterAppTask(NF_ST_SNS_SERVER, APP_INIT_LOAD_RANK_FROM_DB, "Load Rank From DB", APP_INIT_STATUS_SERVER_LOAD_OBJ_FROM_DB);

    int iRet = 0;
    iRet = InitOneRank(proto_ff::E_RANK_TYPE_GOLD);
    CHECK_RET(iRet, "init ranktype:{} faled, iRet:{}", proto_ff::E_RANK_TYPE_GOLD, iRet);

    iRet = InitOneRank(proto_ff::E_RANK_TYPE_TODAY_WIN_GOLD);
    CHECK_RET(iRet, "init ranktype:{} faled, iRet:{}", proto_ff::E_RANK_TYPE_TODAY_WIN_GOLD, iRet);

    m_bInited = true;
    return 0;
}

int NFRankMgr::InitOneRank(proto_ff::enRankType rankType)
{
    CHECK_EXPR(rankType > 0 && rankType < m_rankObjId.GetSize() && rankType < proto_ff::enConstType_ARRAYSIZE, -1, "");
    NFRankCommon* pRank = dynamic_cast<NFRankCommon*>(NFShmMgr::Instance()->CreateObj(EOT_RANK_COMMON_ID));
    CHECK_EXPR(pRank, -1, "Create NFRankCommon Failed, use count:{}", NFRankCommon::GetUsedCount());
    CHECK_EXPR(pRank->IsDataInited() == false, -1, "rank:{} already inited!", enRankType_Name(rankType));
    m_rankObjId[rankType] = pRank->GetGlobalID();

    pRank->Init(NF_ST_SNS_SERVER, rankType);
    int iRet = NFDBObjMgr::Instance()->LoadFromDB(pRank);
    CHECK_RET(iRet, "inti failed, rank:{} iRet:{}", enRankType_Name(rankType), iRet);
    return 0;
}

NFRankCommon* NFRankMgr::GetRank(proto_ff::enRankType eRankType)
{
    CHECK_EXPR(eRankType > 0 && eRankType < m_rankObjId.GetSize() && eRankType < proto_ff::enRankType_ARRAYSIZE, NULL, "param error: {}", eRankType);

    CHECK_EXPR(m_rankObjId[eRankType] >= 0, NULL, "no rank: {}", eRankType);
    NFRankCommon* pRank = dynamic_cast<NFRankCommon*>(NFShmMgr::Instance()->GetObjFromGlobalID(m_rankObjId[eRankType], EOT_RANK_COMMON_ID, 0));
    CHECK_EXPR (pRank, NULL, " Rank Error: ", eRankType);

    return pRank;
}

int NFRankMgr::Remove(proto_ff::enRankType rankType, uint64_t iID)
{
    CHECK_EXPR(rankType >= 0 && rankType < m_rankObjId.GetSize() && rankType < proto_ff::enConstType_ARRAYSIZE, -1, "");
    if (rankType == proto_ff::E_RANK_TYPE_NONE)
    {
        return DeleteWithAll(iID);
    }
    else
    {
        NFRankCommon* pRank = GetRank(rankType);
        CHECK_NULL(pRank);

        return pRank->Remove(iID);
    }
    return 0;
}

int NFRankMgr::DeleteWithAll(uint64_t iID)
{
    NFRankCommon* pRank = dynamic_cast<NFRankCommon*>(NFShmMgr::Instance()->GetHeadObj(EOT_RANK_COMMON_ID));
    while(pRank)
    {
        CHECK_EXPR(pRank->GetRankType() >= 0 && pRank->GetRankType() < m_rankObjId.GetSize() && pRank->GetRankType() < proto_ff::enConstType_ARRAYSIZE, -1, "");
        CHECK_EXPR(pRank->IsDataInited(), -1, "");
        int iRet = pRank->Remove(iID);
        CHECK_RET(iRet, "rank type:{} delete ID:{} failed!", pRank->GetRankType(), iID);

        pRank = dynamic_cast<NFRankCommon*>(NFShmMgr::Instance()->GetNextObj(EOT_RANK_COMMON_ID, pRank));
    }
    return 0;
}

int NFRankMgr::UpdateRank(proto_ff::enRankType eRankType, const proto_ff::RankCommonScore* score, int& old_rank, int& new_rank)
{
    NFRankCommon* pRank = GetRank(eRankType);
    CHECK_NULL(pRank);

    return pRank->UpdateRank(score, old_rank, new_rank);
}
