// -------------------------------------------------------------------------
//    @FileName         :    NFRankCommon.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRankCommon.cpp
//
// -------------------------------------------------------------------------

#include "NFRankCommon.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFRankCommon, EOT_RANK_COMMON_ID, NFBaseDBObj)

#define RANK_JOB_SEG 100

static bool compare_info_id(const proto_ff_s::RankCommonInfo_s &p1, const proto_ff_s::RankCommonInfo_s &p2)
{
    return p1.id < p2.id;
}

static bool compare_score(const proto_ff_s::RankCommonScore_s &p1, const proto_ff_s::RankCommonScore_s &p2)
{
    return p1.score > p2.score;
}

static void exchange_data(void *a, void *b, void *tmp, size_t size)
{
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

NFRankCommon::NFRankCommon()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode())
    {
        CreateInit();
    }
    else
    {
        ResumeInit();
    }
}

NFRankCommon::~NFRankCommon()
{

}

int NFRankCommon::CreateInit() {
    m_iRankTypeID = 0;
    m_bDisableRankDown = false;
    memset(&m_stData, 0, sizeof(m_stData));
    return 0;
}

int NFRankCommon::ResumeInit() {
    return 0;
}

int NFRankCommon::MakeLoadData(google::protobuf::Message* data)
{
    if (m_bDataInited) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "aleady inited !" );
        return -1;
    }
    CHECK_EXPR(m_iRankTypeID, -1, "No Rank Type ");

    CHECK_NULL(data);
    proto_ff::tbRankCommon* p = dynamic_cast<proto_ff::tbRankCommon*>(data);

    CHECK_NULL(p);
    p->set_id4db(m_iRankTypeID * RANK_JOB_SEG);

    return 0;
}
int NFRankCommon::MakeSaveData(google::protobuf::Message* data)
{
    if ( !m_bDataInited ) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "not init!" );
        return -1;
    }
    CHECK_NULL(data);

    proto_ff::tbRankCommon* p = dynamic_cast<proto_ff::tbRankCommon*>(data);
    CHECK_NULL(p);
    proto_ff_s::tbRankCommon_s::write_to_pbmsg(m_stData, *p);

    NFLogTrace(NF_LOG_SYSTEMLOG, 0, "id 4 db:{} {}", p->id4db(), m_stData.id4db);
    NFLogTrace(NF_LOG_SYSTEMLOG, 0, "rank count: {} {}", m_stData.body.score_list.GetSize(), m_stData.body.info_list.GetSize());
    NFLogTrace(NF_LOG_SYSTEMLOG, 0, "rank count: {} {}", p->body().score_list_size(), p->body().info_list_size());

    return 0;
}

int NFRankCommon::InitWithDBData(const std::string* data)
{
    CHECK_NULL( data );
    proto_ff::tbRankCommon pb;
    bool ok = pb.ParseFromString(*data);
    CHECK_EXPR( ok, -1, "parse failed!");
    proto_ff_s::tbRankCommon_s::read_from_pbmsg(pb, m_stData);
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init with db data: {} ", m_iRankTypeID);

    m_bDataInited = true;
    return 0;
}

int NFRankCommon::InitWithoutDBData()
{
    CHECK_EXPR( m_iRankTypeID, -1, "No Rank Type ");
    memset(&m_stData, 0, sizeof(m_stData));
    m_stData.id4db = (m_iRankTypeID * RANK_JOB_SEG );
    CHECK_EXPR( m_stData.id4db > 0, -1, "error: {}", m_stData.id4db);

    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "init without db data: randtype:{} ", m_iRankTypeID);
    m_stData.body.score_list.SetSize(1);
    m_bDataInited = true;
    return 0;
}

int NFRankCommon::Init(NF_SERVER_TYPES serverType, int iRankTypeID)
{
    SetServerType(serverType);
    m_iRankTypeID = iRankTypeID;
    return 0;
}

proto_ff_s::RankCommonInfo_s *NFRankCommon::GetRankInfo(uint64_t uID)
{
    CHECK_EXPR(m_bDataInited, NULL, "data not init! ");

    proto_ff_s::RankCommonInfo_s rk;
    rk.id = uID;
    return m_stData.body.info_list.BinarySearch(rk, compare_info_id);
}

int NFRankCommon::InsertRankInfo(uint64_t iID, int iRank)
{
    CHECK_EXPR(m_bDataInited, -1, "data not init! ");
    proto_ff_s::RankCommonInfo_s rk;
    rk.id = iID;
    proto_ff_s::RankCommonInfo_s *pInfo = m_stData.body.info_list.BinarySearch(rk, compare_info_id);
    if (pInfo)
    {
        CHECK_EXPR(pInfo->id == iID, -1, "m_stData.body.info_list.BinarySearch Error, ranktype:{}", m_iRankTypeID);
        pInfo->rank = iRank;
    }
    else
    {
        CHECK_EXPR(!m_stData.body.info_list.IsFull(), -1, "m_stData.body.info_list.IsFull() Error,, ranktype:{}",
                   m_iRankTypeID);
        rk.rank = iRank;
        pInfo = m_stData.body.info_list.BinaryInsert(rk, compare_info_id);
        CHECK_EXPR(pInfo && pInfo->id == iID && pInfo->rank == iRank, -1, "insert into rank failed:, ranktype:{}",
                   m_iRankTypeID);
    }

    return 0;
}

int NFRankCommon::DeleteRankInfo(uint64_t iID)
{
    CHECK_EXPR(m_bDataInited, -1, "data not init! ");
    proto_ff_s::RankCommonInfo_s rk;
    rk.id = iID;

    int iRet = m_stData.body.info_list.BinaryDelete(rk, compare_info_id);
    CHECK_RET(iRet, "m_stData.body.info_list.BinaryDelete Failed! ranktype:{}", m_iRankTypeID);
    return 0;
}

int NFRankCommon::GetRank(uint64_t uID)
{
    proto_ff_s::RankCommonInfo_s *pInfo = GetRankInfo(uID);
    if (pInfo)
    {
        return pInfo->rank;
    }
    return 0;
}

const proto_ff_s::RankCommonScore_s *NFRankCommon::GetRankScore(int iRank)
{
    CHECK_EXPR(iRank > 0 && iRank < m_stData.body.score_list.GetSize(), NULL, "error, {} ", iRank);

    return &m_stData.body.score_list[iRank];
}

int NFRankCommon::UpdateRank(const proto_ff::RankCommonScore *score, int &old_rank, int &new_rank)
{
    CHECK_NULL(score);
    proto_ff_s::RankCommonScore_s score_s;
    proto_ff_s::RankCommonScore_s::read_from_pbmsg(*score, score_s);
    return UpdateRank(&score_s, old_rank, new_rank);
}

int NFRankCommon::UpdateRank(const proto_ff_s::RankCommonScore_s *score, int &old_rank, int &new_rank)
{
    CHECK_EXPR(m_bDataInited, -1, "data not init! ");
    CHECK_NULL(score);

    int iRetCode = 0;
    old_rank = 0;
    new_rank = 0;

    proto_ff_s::RankCommonInfo_s *pRank = GetRankInfo(score->id);
    if (pRank)
    {
        old_rank = pRank->rank;
        new_rank = pRank->rank;

        if (pRank->rank < 1 || pRank->rank >= m_stData.body.score_list.GetSize())
        {
            NFLogError(NF_LOG_SYSTEMLOG, 0, "rank error, ranktype:{} rankid:{} rank:{} maxrank:{}", m_iRankTypeID, pRank->id, pRank->rank,
                       m_stData.body.score_list.GetSize());
            return -1;
        }

        if (m_stData.body.score_list[pRank->rank].id != score->id)
        {
            NFLogError(NF_LOG_SYSTEMLOG, 0, "rank list error: score list id:{} != info list id:{}", m_stData.body.score_list[pRank->rank].id, score->id);
            return -1;
        }

        memcpy(&m_stData.body.score_list[pRank->rank], score, sizeof(proto_ff_s::RankCommonScore_s));
        MarkDirty();
    }
    else
    {
        if (m_stData.body.score_list.IsFull())
        {
            bool bLess = compare_score(*score, m_stData.body.score_list[m_stData.body.score_list.GetSize() - 1]);
            if (bLess)
            {
                iRetCode = on_score_remove(&m_stData.body.score_list[m_stData.body.score_list.GetSize() - 1]);
                CHECK_RET(iRetCode, "remove failed: {}", m_stData.body.score_list[m_stData.body.score_list.GetSize() - 1].id);

                DeleteRankInfo(m_stData.body.score_list[m_stData.body.score_list.GetSize() - 1].id);
                m_stData.body.score_list.MemShiftDel(m_stData.body.score_list.GetSize() - 1);
                MarkDirty();
            }
            else
            {
                NFLogDebug(NF_LOG_SYSTEMLOG, 0, "not on rank id:{} rank type:{} ", score->id, m_iRankTypeID);
                return 0;
            }
        }

        iRetCode = InsertRankInfo(score->id, m_stData.body.score_list.GetSize());
        CHECK_RET(iRetCode, "insert rank info failed:{} ", score->id);
        pRank = GetRankInfo(score->id);
        CHECK_NULL(pRank);

        pRank->rank = m_stData.body.score_list.GetSize();
        proto_ff_s::RankCommonScore_s *pNewScore = m_stData.body.score_list.Add();
        CHECK_NULL(pNewScore);

        memcpy(pNewScore, score, sizeof(proto_ff_s::RankCommonScore_s));

        MarkDirty();
    }

    if (pRank)
    {
        proto_ff_s::RankCommonScore_s tmp;
        while (pRank->rank > 1)
        {
            proto_ff_s::RankCommonScore_s *pup = &m_stData.body.score_list[pRank->rank - 1];
            if (compare_score(m_stData.body.score_list[pRank->rank], *pup))
            {
                proto_ff_s::RankCommonInfo_s *pi = GetRankInfo(pup->id);
                CHECK_NULL(pi);

                exchange_data(pup, &m_stData.body.score_list[pRank->rank], &tmp, sizeof(proto_ff_s::RankCommonScore_s));
                pi->rank += 1;
                pRank->rank -= 1;
            }
            else
            {
                break;
            }
        }

        while (pRank->rank < m_stData.body.score_list.GetSize() - 1)
        {
            proto_ff_s::RankCommonScore_s *pdo = &m_stData.body.score_list[pRank->rank + 1];
            if (compare_score(*pdo, m_stData.body.score_list[pRank->rank]))
            {
                proto_ff_s::RankCommonInfo_s *pi = GetRankInfo(pdo->id);
                CHECK_NULL(pi);

                exchange_data(pdo, &m_stData.body.score_list[pRank->rank], &tmp,
                              sizeof(proto_ff_s::RankCommonScore_s));
                pi->rank -= 1;
                pRank->rank += 1;
            }
            else
            {
                break;
            }
        }

        if (new_rank != pRank->rank)
        {
            new_rank = pRank->rank;
            MarkDirty();
        }
        on_score_change(&m_stData.body.score_list[new_rank], new_rank);
    }
    else
    {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "unkown error: score size:{} info size:{} id:{}", m_stData.body.score_list.GetSize(), m_stData.body.info_list.GetSize(), score->id);
        return -1;
    }

    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "Update Score: rankType:{} id:{} old rank:{} new rank:{}", m_iRankTypeID, score->id, old_rank, new_rank);
    return 0;
}

int NFRankCommon::Remove(uint64_t iID)
{
    CHECK_EXPR(m_bDataInited, -1, "data not init! ");
    NFLogDebug(NF_LOG_SYSTEMLOG, 0, "Remove RankType:{} ID:{}", m_iRankTypeID, iID);
    proto_ff_s::RankCommonInfo_s *pInfo = GetRankInfo(iID);
    if (pInfo)
    {
        CHECK_EXPR(m_stData.body.score_list[pInfo->rank].id == iID, -1, "Rank ERROR, RankType:{} ID:{} Rank:{} score list rank id:{} ", m_iRankTypeID, iID, pInfo->rank, m_stData.body.score_list[pInfo->rank].id);

        int iRet = on_score_remove(&m_stData.body.score_list[pInfo->rank]);
        CHECK_RET(iRet, " remove data error:{} ", iRet);

        for (int i = pInfo->rank + 1; i < m_stData.body.score_list.GetSize(); ++i)
        {
            proto_ff_s::RankCommonInfo_s *pNext = GetRankInfo(m_stData.body.score_list[i].id);
            CHECK_NULL(pNext);
            --pNext->rank;
            memcpy(&m_stData.body.score_list[i - 1], &m_stData.body.score_list[i], sizeof(proto_ff_s::RankCommonScore_s));
        }

        memset(&m_stData.body.score_list[m_stData.body.score_list.GetSize() - 1], 0, sizeof(proto_ff_s::RankCommonScore_s));
        m_stData.body.score_list.SetSize(m_stData.body.score_list.GetSize() - 1);

        DeleteRankInfo(iID);

        MarkDirty();
    }
    else
    {
        NFLogDebug(NF_LOG_SYSTEMLOG, 0, "no info at rankType:{} ID:{}", m_iRankTypeID, iID);
    }
    return 0;
}