// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailCache.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailCache.cpp
//
// -------------------------------------------------------------------------

#include "NFUserMailUtil.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFRandom.hpp"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFCore/NFCommon.h"

#include "NFTransMail.h"
#include "NFTransMailCreate.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFUserMailMgr.h"
#include "NFMailDesc.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFUserMailUtil, EOT_USER_MAIL_CACHE_MNG_ID, NFShmObj)

NFUserMailUtil::NFUserMailUtil() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFUserMailUtil::~NFUserMailUtil() {

}

int NFUserMailUtil::CreateInit() {
    return 0;
}

int NFUserMailUtil::ResumeInit() {
    return 0;
}

bool NFUserMailUtil::CacheFull() {
    return NFUserMailCacheInfo::GetUsedCount() >= NFUserMailCacheInfo::GetItemCount();
}

NFUserMailCacheInfo *NFUserMailUtil::GetMailCache(uint64_t roleID) {
    return dynamic_cast<NFUserMailCacheInfo*>(NFShmMgr::Instance()->GetObjFromHashKey(roleID, EOT_USER_MAIL_CACHE_ID));
}

NFUserMailCacheInfo *NFUserMailUtil::AddMailCache(uint64_t roleID) {
    if (CacheFull()) {
        //random del one
        ReleaseNum(NFUserMailCacheInfo::GetItemCount()*0.1);
    }

    NFUserMailCacheInfo *pInfo = dynamic_cast<NFUserMailCacheInfo*>(NFShmMgr::Instance()->CreateObj(roleID, EOT_USER_MAIL_CACHE_ID));
    CHECK_EXPR(pInfo, NULL, "AddMailCache Failed! roleID:{}", roleID);
    pInfo->userID = roleID;

    return pInfo;
}

int NFUserMailUtil::ReleaseNum(int num) {
    NFShmMgr::Instance()->DestroyObjAutoErase(EOT_USER_MAIL_CACHE_ID, NFUserMailCacheInfo::GetUsedCount() >= num ? NFUserMailCacheInfo::GetUsedCount() - num : 0);
    return 0;
}

int NFUserMailUtil::AddMailCache(NFUserMailCacheInfo *mailInfo, proto_ff::tbUserMailDetail &newMail) {
    CHECK_NULL(mailInfo);

    if (mailInfo->GetSimpleMail(newMail.id()))
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "same mail int cache:{}", newMail.id());
        return 0;
    }

    proto_ff_s::tbUserMailDetail_s* pInfo = mailInfo->AddSimpleMail();
    if (pInfo)
    {
        proto_ff_s::tbUserMailDetail_s::read_from_pbmsg(newMail, *pInfo);
    }
    else
    {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "mailInfo->AddSimpleMail() Failed:{}", newMail.id());
        return -1;
    }
    return 0;
}

int NFUserMailUtil::OnCreateMail(proto_ff::tbUserMailDetail& tb_role_mail, uint64_t roleID, bool isGM, uint64_t iSrcSvrID)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    int iRetCode = 0;
    proto_ff_s::tbUserMailDetail_s tmpItem;

    FillMailTemplate(tb_role_mail);

    NFTransMailCreate *pTransMail = (NFTransMailCreate *) NFShmMgr::Instance()->CreateTrans(
            EOT_TRANS_USER_MAIL_CREATE_ID);
    CHECK_EXPR(pTransMail, ERR_TRANS_RUNED_TOO_MUCH, "Create msg Trans Failed! UsedItem:{}",
               NFTransMailCreate::GetUsedCount());

    pTransMail->Init(roleID, isGM, iSrcSvrID);
    iRetCode = pTransMail->ProMailCreateReq(tb_role_mail);
    if (iRetCode) {
        pTransMail->SetFinished(iRetCode);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFUserMailUtil::FillMailTemplate(proto_ff::tbUserMailDetail &tb_role_mail) {
    int iRetCode = 0;
    if (tb_role_mail.static_id() > 0)
    {
        const proto_ff_s::MailDesc_s *pMailDesc = NFMailDesc::Instance()->GetDesc(tb_role_mail.static_id());
        CHECK_NULL(pMailDesc);

        tb_role_mail.set_title(pMailDesc->title.GetString());
        tb_role_mail.set_send_name(pMailDesc->send_name.GetString());
        tb_role_mail.set_add_gold(pMailDesc->add_gold);

        std::string* content = tb_role_mail.mutable_content();
        try {
            if (tb_role_mail.mail_name_size() == 0)
            {
               *content = pMailDesc->content.GetString();
            }
            else if (tb_role_mail.mail_name_size() == 1)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0));
            }
            else if (tb_role_mail.mail_name_size() == 2)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1));
            }
            else if (tb_role_mail.mail_name_size() == 3)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2));
            }
            else if (tb_role_mail.mail_name_size() == 4)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3));
            }
            else if (tb_role_mail.mail_name_size() == 5)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4));
            }
            else if (tb_role_mail.mail_name_size() == 6)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4), tb_role_mail.mail_name(5));
            }
            else if (tb_role_mail.mail_name_size() == 7)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4), tb_role_mail.mail_name(5)
                           , tb_role_mail.mail_name(6));
            }
            else if (tb_role_mail.mail_name_size() == 8)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4), tb_role_mail.mail_name(5)
                           , tb_role_mail.mail_name(6), tb_role_mail.mail_name(7));
            }
            else if (tb_role_mail.mail_name_size() == 9)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4), tb_role_mail.mail_name(5)
                           , tb_role_mail.mail_name(6), tb_role_mail.mail_name(7), tb_role_mail.mail_name(8));
            }
            else if (tb_role_mail.mail_name_size() == 10)
            {
                *content = NF_FORMAT(pMailDesc->content.GetBuffer(), tb_role_mail.mail_name(0), tb_role_mail.mail_name(1)
                           , tb_role_mail.mail_name(2), tb_role_mail.mail_name(3), tb_role_mail.mail_name(4), tb_role_mail.mail_name(5)
                           , tb_role_mail.mail_name(6), tb_role_mail.mail_name(7), tb_role_mail.mail_name(8), tb_role_mail.mail_name(9));
            }
            else
            {
                *content = "error, param too much";
            }
        }
        catch (fmt::v5::format_error& error) {
            *content = fmt::format("log format error------------{} error:{}", pMailDesc->content.GetBuffer(), error.what());\
        }
    }
    return iRetCode;
}

bool NFUserMailUtil::IsSimpleMailHasItem(proto_ff_s::tbUserMailDetail_s *pMail) {
    if (!pMail)
        return false;

    if (pMail->add_gold > 0)
    {
        return true;
    }

    return false;
}

int NFUserMailUtil::OnPlayerLogin(NFSnsUserSimple* pSimple)
{
    CHECK_NULL(pSimple);

    NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());

    pTransMail->Init(pSimple->GetUserId(), proto_ff::NF_LTS_PLAYER_LOGIN_REQ);
    int iRetCode = pTransMail->ProGetMailBaseInfoReq();
    if (iRetCode)
    {
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }

    return 0;
}

int NFUserMailUtil::OnPlayerLogout(NFSnsUserSimple* pSimple)
{
    CHECK_NULL(pSimple);
    return 0;
}

int NFUserMailUtil::OnSendTemplateMail(uint64_t roleID, int staticID)
{
    proto_ff::tbUserMailDetail tb_role_mail;

    tb_role_mail.set_static_id(staticID);

    return OnCreateMail(tb_role_mail, roleID);
}

int NFUserMailUtil::AddMailRes(NFUserMail *pUserMailExt, uint64_t roleID, proto_ff_s::tbUserMailDetail_s &mail)
{
    CHECK_NULL(pUserMailExt);

    proto_ff_s::SingleMailInfo_s *pMailInfo = pUserMailExt->GetSimpleMail(mail.id);
    if (pMailInfo == NULL)
    {
        pMailInfo = pUserMailExt->AddSimpleMail();
        CHECK_NULL(pMailInfo);
    }

    pMailInfo->id = mail.id;
    pMailInfo->status = proto_ff::EN_SNS_MAIL_NO_READ;
    pUserMailExt->MarkDirty();

    NFUserMailCacheInfo *pMailCacheInfo = NFUserMailUtil::GetInstance()->GetMailCache(roleID);
    if (pMailCacheInfo)
    {
        proto_ff_s::tbUserMailDetail_s* tmpSimpleMail = pMailCacheInfo->GetSimpleMail(mail.id);
        if (tmpSimpleMail == NULL)
        {
            tmpSimpleMail = pMailCacheInfo->AddSimpleMail();
            CHECK_NULL(tmpSimpleMail);
        }

        memcpy(tmpSimpleMail, &mail, sizeof(proto_ff_s::tbUserMailDetail_s));
    }

    NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(roleID);
    if (pOnline)
    {
        proto_ff::Proto_STLMailAutoPushRsp ntf;
        ntf.set_user_id(roleID);
        MakeSimpleMailToClient(ntf.add_role_mail_list(), mail, proto_ff::EN_SNS_MAIL_NO_READ);
        ntf.set_all_count(pUserMailExt->GetAllMailSize());
        ntf.set_no_read_count(pUserMailExt->GetAllNoReadMailSize());
        pOnline->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_MAIL_AUTO_PUSH_RSP, ntf);
    }

    return 0;
}

int NFUserMailUtil::MakeSimpleMailToClient(proto_email::UserMailData *clientMail, proto_ff_s::tbUserMailDetail_s &simpleMail, proto_ff::enSnsMailStatus status)
{
    CHECK_NULL(clientMail);
    clientMail->set_id(simpleMail.id);
    clientMail->set_send_name(simpleMail.send_name.GetString());
    clientMail->set_title(simpleMail.title.GetString());
    clientMail->set_content(simpleMail.content.GetString());
    clientMail->set_send_time(simpleMail.send_time);
    //clientMail->set_add_gold(simpleMail.add_gold);
    clientMail->set_status(status);
    return 0;
}

int NFUserMailUtil::SendMailListToClient(NFUserMail *pUserMailExt, uint64_t roleId, NFUserMailCacheInfo *pMailCacheInfo,
                                         int begin, int end) {
    NFOnlineUser* pOnline = NFOnlineUserMgr::GetInstance()->Find(roleId);
    CHECK_NULL(pOnline);

    proto_ff::Proto_STLMailListRsp rsp;
    rsp.set_user_id(roleId);
    rsp.mutable_cs_rsp()->set_result(0);

    std::vector<proto_email::UserMailData> vec;
    if (pMailCacheInfo)
    {
        if (pUserMailExt)
        {
            if (begin <= ROLE_MAIL_GET_MAIL_MAX && begin <= (int)pMailCacheInfo->mailInfo.simple_mail.GetSize())
            {
                for(int i = begin-1; i < (int)pMailCacheInfo->mailInfo.simple_mail.GetSize() && i < end; ++i)
                {
                    proto_ff_s::SingleMailInfo_s* tmpdata = pUserMailExt->GetSimpleMail(pMailCacheInfo->mailInfo.simple_mail[i].id);
                    if(tmpdata)
                    {
                        proto_email::UserMailData data;
                        MakeSimpleMailToClient(&data, pMailCacheInfo->mailInfo.simple_mail[i], (proto_ff::enSnsMailStatus)tmpdata->status);
                        vec.push_back(data);
                    }
                    else
                    {
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "mail error, id:{}", pMailCacheInfo->mailInfo.simple_mail[i].id);
                    }
                }
            }
        }
        else
        {
            rsp.mutable_cs_rsp()->set_result(-1);
        }
    }

    std::sort(vec.begin(), vec.end(), [](const proto_email::UserMailData& a1, const proto_email::UserMailData& a2) {
        if (a1.status() < a2.status())
        {
            return true;
        }
        else
        {
            if (a1.send_time() > a2.send_time())
            {
                return true;
            }
        }

        return false;
    });

    if (pUserMailExt)
    {
        for(int i = 0; i < (int)vec.size(); i++)
        {
            rsp.mutable_cs_rsp()->add_role_mail_list()->CopyFrom(vec[i]);
        }
        rsp.mutable_cs_rsp()->set_all_count(pUserMailExt->GetAllMailSize());
        rsp.mutable_cs_rsp()->set_no_read_count(pUserMailExt->GetAllNoReadMailSize());
    }

    pOnline->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_LIST_RSP, rsp);
    return 0;
}


int NFUserMailUtil::MakeAllMailRead(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_email::Proto_CSMailReadRsp& req)
{
    CHECK_NULL(roleMailExt);
    CHECK_NULL(mailInfo);

    for(int i=0; i< (int)roleMailExt->GetData()->simple_mail.GetSize(); ++i)
    {
        proto_ff_s::SingleMailInfo_s* tmpdata = &roleMailExt->GetData()->simple_mail[i];
        if(tmpdata && tmpdata->status <= proto_ff::EN_SNS_MAIL_NO_READ)
        {
            proto_ff_s::tbUserMailDetail_s* pMailDetail = mailInfo->GetSimpleMail(tmpdata->id);
            if (pMailDetail && pMailDetail->add_gold <= 0)
            {
                tmpdata->status = proto_ff::EN_SNS_MAIL_ALREADY_READ;
                roleMailExt->MarkDirty();
                req.add_mail_id_list(tmpdata->id);
            }
        }
    }

    return 0;
}

int NFUserMailUtil::ClearRoleMailDB(uint64_t roleID)
{
    NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
    pTransMail->Init(roleID);
    int iRetCode = pTransMail->ProMailDelReq();
    if(iRetCode)
    {
        NFLogError(NF_LOG_SYSTEMLOG, roleID, "delete all mail error");
        pTransMail->SetFinished(iRetCode);
        return iRetCode;
    }

    return 0;
}

int NFUserMailUtil::DeleteAllCacheMail(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, uint64_t roleID)
{
    CHECK_NULL(roleMailExt);

    std::vector<uint64_t> delVec;
    std::vector<uint64_t> allMail;
    for(int i = 0; i < roleMailExt->GetData()->simple_mail.GetSize(); ++i)
    {
        allMail.push_back(roleMailExt->GetData()->simple_mail[i].id);
    }
    for(int i = 0; i < (int)allMail.size(); ++i)
    {
        proto_ff_s::SingleMailInfo_s *tmpdata = roleMailExt->GetSimpleMail(allMail[i]);
        if(tmpdata && tmpdata->status == proto_ff::EN_SNS_MAIL_ALREADY_READ)
        {
            int ret = roleMailExt->DelSimpleMail(tmpdata->id);
            if (ret == 0)
            {
                delVec.push_back(tmpdata->id);
                if (mailInfo)
                {
                    mailInfo->DelSimpleMail(tmpdata->id);
                }
            }
        }
    }

    if(delVec.size() > 0)
    {
        if(mailInfo && !roleMailExt->IsHaveMail())
        {
            ClearRoleMailDB(roleID);
            NFUserMailUtil::Instance()->DeleteMailCache(roleID);
            mailInfo = NULL;
            ProDeleteOpGetCacheRes(roleID, delVec);
            return 0;
        }

        if (mailInfo)
        {
            NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
            pTransMail->Init(roleID, proto_ff::NF_LTS_MAIL_DEL_REQ, delVec);
            int iRetCode = pTransMail->ProMailListReq(roleMailExt, mailInfo->mailInfo.simple_mail.GetSize());
            if(iRetCode)
            {
                pTransMail->SetFinished(0);
                ProDeleteOpGetCacheRes(roleID, delVec);
                return 0;
            }
        }
    }

    ProDeleteOpGetCacheRes(roleID, delVec);

    return 0;
}

int NFUserMailUtil::ProDeleteOpGetCacheRes(uint64_t roleID, const std::vector<uint64_t>& vecDel)
{
    NFOnlineUser *pUser = NFOnlineUserMgr::GetInstance()->Find(roleID);
    CHECK_NULL(pUser);

    proto_ff::Proto_STLMailDelRsp rspMsg;
    proto_email::Proto_CSMailDelRsp* pRsp = rspMsg.mutable_cs_rsp();
    rspMsg.set_user_id(roleID);

    if (vecDel.size() > 0)
    {
        pRsp->set_result(0);
    }
    else
    {
        pRsp->set_result(proto_ff::ERR_CODE_DEL_MAIL_FAIL);
    }

    for(int i = 0; i< (int)vecDel.size(); ++i)
    {
        pRsp->add_mail_id_list(vecDel[i]);
    }

    pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_DEL_RSP, rspMsg);

    return 0;
}

int NFUserMailUtil::MakeAllGotMailItem(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_ff::Proto_STLMailReadItemReq& req)
{
    CHECK_NULL(roleMailExt);
    CHECK_NULL(mailInfo);

    for(int i = 0; i< (int)mailInfo->mailInfo.simple_mail.GetSize(); ++i)
    {
        proto_ff_s::SingleMailInfo_s* tmpdata = roleMailExt->GetSimpleMail(mailInfo->mailInfo.simple_mail[i].id);
        if(tmpdata && tmpdata->status <= proto_ff::EN_SNS_MAIL_NO_READ)
        {
            if (mailInfo->mailInfo.simple_mail[i].add_gold > 0)
            {
                proto_email::MailItem* pMailItem = req.add_item_list();
                pMailItem->set_id(mailInfo->mailInfo.simple_mail[i].id);
                pMailItem->set_add_gold(mailInfo->mailInfo.simple_mail[i].add_gold);
                tmpdata->status = proto_ff::EN_SNS_MAIL_ALREADY_READ;
                roleMailExt->MarkDirty();
            }
        }
    }

    return 0;
}

int NFUserMailUtil::MakeGotMailItem(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_ff::Proto_STLMailReadItemReq& req, uint64_t mailID)
{
    CHECK_NULL(roleMailExt);

    if(mailInfo)
    {
        proto_ff_s::tbUserMailDetail_s* getItemMail = mailInfo->GetSimpleMail(mailID);
        if(getItemMail)
        {
            proto_ff_s::SingleMailInfo_s* tmpdata = roleMailExt->GetSimpleMail(mailID);
            if(tmpdata)
            {
                if (tmpdata->status <= proto_ff::EN_SNS_MAIL_NO_READ)
                {
                    proto_email::MailItem* pMailItem = req.add_item_list();
                    pMailItem->set_id(mailID);
                    pMailItem->set_add_gold(getItemMail->add_gold);
                    tmpdata->status = proto_ff::EN_SNS_MAIL_ALREADY_READ;
                    roleMailExt->MarkDirty();
                }
            }
        }
    }

    return 0;
}

int NFUserMailUtil::SendGetMailItemToClient(NFUserMail *roleMailExt, uint64_t roleID, NFUserMailCacheInfo *mailInfo, uint64_t mailID)
{
    CHECK_NULL(roleMailExt);

    int iRetCode = 0;
    NFOnlineUser *pUser = NFOnlineUserMgr::GetInstance()->Find(roleID);
    CHECK_NULL(pUser);

    proto_ff::Proto_STLMailReadItemReq req;
    req.set_user_id(roleID);

    if(mailID == 0)
    {
        MakeAllGotMailItem(roleMailExt, mailInfo, req);
    }
    else
    {
        MakeGotMailItem(roleMailExt, mailInfo, req, mailID);
    }

    if(req.item_list_size() > 0)
    {
        roleMailExt->MarkDirty();
        pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_ITEM_REQ, req);
    }
    else
    {
        proto_ff::Proto_STLMailGetItemRsp rspClientMsg;
        proto_email::Proto_CSMailGetItemRsp *cs_rsp = rspClientMsg.mutable_cs_rsp();

        rspClientMsg.set_user_id(roleID);
        cs_rsp->set_no_read_count(roleMailExt->GetAllNoReadMailSize());
        pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_GET_ITEM_RSP, rspClientMsg);
    }

    return iRetCode;
}

int NFUserMailUtil::ProGetMailItemRes(NFUserMail *roleMailExt, uint64_t roleID, uint64_t mailID)
{
    CHECK_NULL(roleMailExt);
    int iRetCode = 0;

    NFUserMailCacheInfo* pCacheInfo = NFUserMailUtil::GetInstance()->GetMailCache(roleID);
    if(pCacheInfo)
    {
        iRetCode = NFUserMailUtil::SendGetMailItemToClient(roleMailExt, roleID, pCacheInfo, mailID);
    }
    else
    {
        if(roleMailExt->IsHaveMail())
        {
            NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
            pTransMail->Init(roleID, mailID, 0, proto_ff::NF_LTS_MAIL_GET_ITEM_REQ);
            iRetCode = pTransMail->ProMailListReq(roleMailExt);
            if(iRetCode)
            {
                pTransMail->SetFinished(iRetCode);
                return iRetCode;
            }
        }
        else
        {
            iRetCode = NFUserMailUtil::SendGetMailItemToClient(roleMailExt, roleID, NULL, mailID);
        }
    }

    return iRetCode;
}

int NFUserMailUtil::ProGetMailListRes(NFUserMail *pUserMailExt, uint64_t roleId, int begin, int end) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");

    int iRetCode = 0;

    if (pUserMailExt) {
        NFUserMailCacheInfo *pMailInfo = NFUserMailUtil::GetInstance()->GetMailCache(roleId);
        if (pMailInfo) {
            CheckUserMailInfo(roleId, pUserMailExt, pMailInfo);
            iRetCode = NFUserMailUtil::SendMailListToClient(pUserMailExt, roleId, pMailInfo, begin, end);
        } else {
            if (pUserMailExt->IsHaveMail()) {
                NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
                CHECK_EXPR(pTransMail, ERR_TRANS_RUNED_TOO_MUCH, "Create msg Trans Failed! UsedItem:{}",
                           NFTransMail::GetUsedCount());
                pTransMail->Init(roleId, 0, 0, proto_ff::NF_LTS_MAIL_LIST_REQ, begin, end);
                iRetCode = pTransMail->ProMailListReq(pUserMailExt);
                if (iRetCode) {
                    pTransMail->SetFinished(0);
                    return iRetCode;
                }
            } else {
                iRetCode = NFUserMailUtil::SendMailListToClient(pUserMailExt, roleId, NULL, begin, end);
            }
        }
    }
    else
    {
        iRetCode = NFUserMailUtil::SendMailListToClient(NULL, roleId, NULL, begin, end);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFUserMailUtil::ProReadMailRes(NFUserMail *pUserMailExt, uint64_t roleId, uint64_t mailID) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    CHECK_NULL(pUserMailExt);
    int iRetCode = 0;

    NFOnlineUser *pUser = NFOnlineUserMgr::GetInstance()->Find(roleId);
    CHECK_NULL(pUser);

    NFUserMailCacheInfo *pMailCacheInfo = NFUserMailUtil::GetInstance()->GetMailCache(roleId);
    if (pMailCacheInfo)
    {
        if (mailID != 0)
        {
            proto_ff_s::SingleMailInfo_s *tmpItemMail = pUserMailExt->GetSimpleMail(mailID);
            if(tmpItemMail)
            {
                if (tmpItemMail->status == proto_ff::EN_SNS_MAIL_NO_READ)
                {
                    proto_ff_s::tbUserMailDetail_s* pMailDetail = pMailCacheInfo->GetSimpleMail(mailID);
                    if (pMailDetail)
                    {
                        if (!NFUserMailUtil::IsSimpleMailHasItem(pMailDetail))
                        {
                            tmpItemMail->status = proto_ff::EN_SNS_MAIL_ALREADY_READ;
                            pUserMailExt->MarkDirty();
                        } else {
                            tmpItemMail->status = proto_ff::EN_SNS_MAIL_NO_READ;
                            pUserMailExt->MarkDirty();
                        }
                    }
                    else
                    {
                        iRetCode = proto_ff::ERR_CODE_ROLE_MAIL_NOT_FIND;
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "roleId:{} can' find the mail id:{} int the cache", roleId, mailID);
                    }
                }
            }
            else
            {
                iRetCode = proto_ff::ERR_CODE_ROLE_MAIL_NOT_FIND;
                NFLogError(NF_LOG_SYSTEMLOG, 0, "can' find the mail id:{} int the simple maillist", mailID);
            }

            proto_ff::Proto_STLMailReadRsp rsp;
            rsp.set_user_id(roleId);
            proto_email::Proto_CSMailReadRsp* cs_rsp = rsp.mutable_cs_rsp();

            cs_rsp->set_result(iRetCode);
            cs_rsp->add_mail_id_list(mailID);

            pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_RSP, rsp);
        }
        else
        {
            proto_ff::Proto_STLMailReadRsp rsp;
            rsp.set_user_id(roleId);
            proto_email::Proto_CSMailReadRsp* cs_rsp = rsp.mutable_cs_rsp();
            iRetCode = NFUserMailUtil::MakeAllMailRead(pUserMailExt, pMailCacheInfo, *cs_rsp);
            cs_rsp->set_result(iRetCode);
            pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_RSP, rsp);
        }
    }
    else
    {
        if(pUserMailExt->IsHaveMail())
        {
            NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
            pTransMail->Init(roleId, mailID, 0, proto_ff::NF_LTS_MAIL_READ_REQ);
            iRetCode = pTransMail->ProMailListReq(pUserMailExt);
            if(iRetCode)
            {
                pTransMail->SetFinished(iRetCode);
                return iRetCode;
            }
        }
        else
        {
            proto_ff::Proto_STLMailReadRsp rsp;
            rsp.set_user_id(roleId);
            proto_email::Proto_CSMailReadRsp* cs_rsp = rsp.mutable_cs_rsp();
            cs_rsp->set_result(proto_ff::ERR_CODE_READ_MAIL_FAIL);
            pUser->SendMsgToLogicServer(proto_ff::NF_STL_MAIL_READ_RSP, rsp);
        }
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return iRetCode;
}

int NFUserMailUtil::ProDeleteMailRes(NFUserMail *pUserMailExt, uint64_t roleId, const std::vector<uint64_t>& vecMail) {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");

    int iRetCode = 0;
    CHECK_NULL(pUserMailExt);

    NFOnlineUser *pUser = NFOnlineUserMgr::GetInstance()->Find(roleId);
    CHECK_NULL(pUser);

    NFUserMailCacheInfo* pCacheInfo = NFUserMailUtil::GetInstance()->GetMailCache(roleId);
    if(vecMail.size() > 0)
    {
        std::vector<uint64_t> delSuccess;
        for(int i = 0; i < (int)vecMail.size(); i++) {
            uint64_t mailID = vecMail[i];
            iRetCode = pUserMailExt->DelSimpleMail(mailID);
            if (iRetCode == 0) {
                if (pCacheInfo) {
                    pCacheInfo->DelSimpleMail(mailID);
                }

                delSuccess.push_back(mailID);
            } else {
                NFLogError(NF_LOG_SYSTEMLOG, 0, "delete mail:{} failed", mailID);
            }
        }

        if(delSuccess.size() > 0)
        {
            if(pCacheInfo)
            {
                if(!pUserMailExt->IsHaveMail())
                {
                    NFUserMailUtil::ClearRoleMailDB(roleId);
                    NFUserMailUtil::GetInstance()->DeleteMailCache(roleId);
                    pCacheInfo = NULL;
                    NFUserMailUtil::ProDeleteOpGetCacheRes(roleId, delSuccess);
                }
                else
                {
                    NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
                    CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
                    pTransMail->Init(roleId, proto_ff::NF_LTS_MAIL_DEL_REQ, delSuccess);
                    iRetCode = pTransMail->ProMailListReq(pUserMailExt, pCacheInfo->mailInfo.simple_mail.GetSize());
                    if(iRetCode)
                    {
                        pTransMail->SetFinished(0);
                        NFUserMailUtil::ProDeleteOpGetCacheRes(roleId, delSuccess);
                    }
                }
            }
        }
        else
        {
            std::vector<uint64_t> vec;
            NFUserMailUtil::ProDeleteOpGetCacheRes(roleId, vec);
        }
    }
    else
    {
        if(!pCacheInfo && pUserMailExt->IsHaveMail())
        {
            NFTransMail* pTransMail = (NFTransMail*)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, -1, "Create Msg Trans Failed! UsedItem:{}", NFTransMail::GetUsedCount());
            pTransMail->Init(roleId, 0, 0, proto_ff::NF_LTS_MAIL_DEL_REQ);
            iRetCode = pTransMail->ProMailListReq(pUserMailExt);
            if(iRetCode)
            {
                pTransMail->SetFinished(0);
                NFUserMailUtil::ProDeleteOpGetCacheRes(roleId, std::vector<uint64_t>());
            }
        }
        else
        {
            NFUserMailUtil::DeleteAllCacheMail(pUserMailExt, pCacheInfo, roleId);
        }
    }
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFUserMailUtil::CheckUserMailInfo(uint64_t userId, NFUserMail* pUserMailExt, NFUserMailCacheInfo *pMailCacheInfo)
{
    CHECK_NULL(pUserMailExt);
    CHECK_NULL(pMailCacheInfo);

    if (pUserMailExt->GetSimpleMailSize() <= ROLE_MAIL_GET_MAIL_MAX && pMailCacheInfo->GetSimpleMailSize() != pUserMailExt->GetSimpleMailSize())
    {
        std::vector<uint64_t> vecMailId = GetDiffMailId(pUserMailExt, pMailCacheInfo);
        if (vecMailId.size() > 0)
        {
            NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, ERR_TRANS_RUNED_TOO_MUCH, "Create msg Trans Failed! UsedItem:{}",
                       NFTransMail::GetUsedCount());
            pTransMail->Init(userId, 0, 0, 0);
            int iRetCode = pTransMail->LoadMailList(vecMailId);
            if (iRetCode) {
                pTransMail->SetFinished(0);
                return iRetCode;
            }

            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "user:{} email data is not right, load diff mail:{} from db..................", userId, NFCommon::tostr(vecMailId));
        }
    }
    else if (pUserMailExt->GetSimpleMailSize() > ROLE_MAIL_GET_MAIL_MAX)
    {
        std::vector<uint64_t> vecMailId = GetDiffMailId(pUserMailExt, pMailCacheInfo);
        if (vecMailId.size() > 0)
        {
            NFTransMail *pTransMail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
            CHECK_EXPR(pTransMail, ERR_TRANS_RUNED_TOO_MUCH, "Create msg Trans Failed! UsedItem:{}",
                       NFTransMail::GetUsedCount());
            pTransMail->Init(userId, 0, 0, 0);
            int iRetCode = pTransMail->LoadMailList(vecMailId);
            if (iRetCode) {
                pTransMail->SetFinished(0);
                return iRetCode;
            }
            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "user:{} email data is not right, load diff mail:{} from db..................", userId, NFCommon::tostr(vecMailId));
        }
    }
    return 0;
}

std::vector<uint64_t> NFUserMailUtil::GetDiffMailId(NFUserMail* pUserMailExt, NFUserMailCacheInfo *pMailCacheInfo)
{
    std::vector<uint64_t> vec;
    CHECK_EXPR(pUserMailExt, vec, "");
    CHECK_EXPR(pMailCacheInfo, vec, "");

    int simpleCount = 0;

    int needCount = pUserMailExt->GetData()->simple_mail.GetSize() < ROLE_MAIL_GET_MAIL_MAX ? (
            pUserMailExt->GetData()->simple_mail.GetSize() - simpleCount) : (ROLE_MAIL_GET_MAIL_MAX - simpleCount);

    int tmpCount = pUserMailExt->GetData()->simple_mail.GetSize();

    for (int i = tmpCount - simpleCount - needCount; i < tmpCount - simpleCount; ++i) {
        uint64_t mailId = pUserMailExt->GetData()->simple_mail[i].id;
        proto_ff_s::tbUserMailDetail_s* pMailInfo = pMailCacheInfo->GetSimpleMail(mailId);
        if (!pMailInfo)
        {
            vec.push_back(mailId);
        }
    }

    return vec;
}

bool NFUserMailUtil::DeleteMailCache(uint64_t roleID) {
    NFUserMailCacheInfo *pInfo = GetMailCache(roleID);
    if (!pInfo)
    {
        NFLogError(NF_LOG_SYSTEMLOG, roleID, "GetMailCache Failed!")
        return false;
    }

    NFShmMgr::Instance()->DestroyObj(pInfo);
    return true;
}