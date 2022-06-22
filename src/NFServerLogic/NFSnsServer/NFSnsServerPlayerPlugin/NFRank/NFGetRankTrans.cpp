// -------------------------------------------------------------------------
//    @FileName         :    NFGetRankTrans.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGetRankTrans.cpp
//
// -------------------------------------------------------------------------

#include "NFGetRankTrans.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFRankCommon.h"
#include "NFRankMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleUtil.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFGetRankTrans, EOT_TRANS_SNS_GET_TRANS_ID, NFTransSnsBase)

NFGetRankTrans::NFGetRankTrans()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    }
    else {
        ResumeInit();
    }
}

NFGetRankTrans::~NFGetRankTrans()
{

}

int NFGetRankTrans::CreateInit()
{
    m_userId = 0;
    m_eRankType = proto_ff::E_RANK_TYPE_NONE;

    m_rank_list.CreateInit();
    m_score_list.CreateInit();

    Init();
    return 0;
}

int NFGetRankTrans::ResumeInit()
{
    return 0;
}

int NFGetRankTrans::QueryRole_CallBack(tagQueryRole &query)
{
    NFOnlineUser* pUser = NFOnlineUserMgr::GetInstance()->Find(m_userId);
    CHECK_NULL(pUser);

    NFRankCommon* pRank = NFRankMgr::Instance()->GetRank(m_eRankType);
    CHECK_NULL(pRank);

    proto_ff::Proto_STLGetCommonRankRsp rsp;
    rsp.set_result(0);

    int myRank = pRank->GetRank(pUser->GetUserID());
    rsp.set_my_rank(myRank);
    rsp.set_my_score(0);

    if (myRank > 0)
    {
        const proto_ff_s::RankCommonScore_s *pMyScore = pRank->GetRankScore(myRank);
        if (pMyScore)
        {
            rsp.set_my_score(pMyScore->score);
        }
    }

    rsp.set_user_id(m_userId);
    rsp.set_rank_type(m_eRankType);
    rsp.set_rank_max(pRank->GetMaxRank());

    for(int i = 0; i < m_rank_list.GetSize() && i < m_score_list.GetSize(); i++)
    {
        MakeRankInfo(m_eRankType, m_score_list[i], m_rank_list[i].rank, rsp.add_rank_list());
    }

    pUser->SendMsgToLogicServer(proto_ff::NF_STL_GET_COMMON_RANK_RSP, rsp);
    return 0;
}

int NFGetRankTrans::MakeRankInfo(proto_ff::enRankType eRankType, const proto_ff_s::RankCommonScore_s& score, int iRank, proto_rank::RankInfo* out)
{
    CHECK_NULL(out);

    NFSnsUserSimple*  pUserSimple = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(score.id, false);
    if (pUserSimple)
    {
        out->set_user_id(pUserSimple->m_userData.show_userid);
        out->set_user_name(pUserSimple->GetNickName());
        out->set_rank(iRank);
        out->set_score(score.score);
        out->set_face_id(pUserSimple->GetFace());
        return 0;
    }

    return -1;
}

int NFGetRankTrans::OnTransFinished(int iRunLogicRetCode)
{
    return 0;
}

int NFGetRankTrans::InitThisTrans(uint64_t userId, proto_ff::enRankType eRankType)
{
    m_userId = userId;
    m_eRankType = eRankType;
    return 0;
}

int NFGetRankTrans::AddScore(const proto_ff_s::RankCommonInfo_s &info, const proto_ff_s::RankCommonScore_s &score)
{
    m_query.Add(info.id);
    m_rank_list.AddMemCpy(info);
    m_score_list.AddMemCpy(score);
    return 0;
}

int NFGetRankTrans::DoQuery()
{
    QueryRole();
    return 0;
}
