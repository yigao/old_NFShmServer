// -------------------------------------------------------------------------
//    @FileName         :    NFActivityMail.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFActivityMail.cpp
//
// -------------------------------------------------------------------------

#include "NFActivityMail.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFUserMail.h"
#include "NFUserMailMgr.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFComm/NFShmCore/NFShmMgr.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFMailDesc.h"
#include "NFComm/NFCore/NFMagicTimeUtil.h"
#include "NFUserMailUtil.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFActivityMail, EOT_SNS_ACTIVITY_MAIL_DATA, NFShmObj)

NFActivityMail::NFActivityMail()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFActivityMail::~NFActivityMail()
{

}

int NFActivityMail::CreateInit()
{
    m_userGetMailIDTimer = INVALID_ID;
    m_userTemplateMailTimer = INVALID_ID;
   return 0;
}

int NFActivityMail::ResumeInit()
{
    return 0;
}

int NFActivityMail::Init() {
    if (m_userGetMailIDTimer == INVALID_ID)
    {
        m_userGetMailIDTimer = SetDayTime(0, 0, 0, 1, 0);
        if (m_userGetMailIDTimer == INVALID_ID)
        {
            NFLogError(NF_LOG_SYSTEMLOG, 0, "get mail id timer error");
        }
    }
    return 0;
}

int NFActivityMail::OnTickGetMailID()
{
    auto& descData = NFMailDesc::Instance()->GetResDesc();
    int num = NFMailDesc::Instance()->GetResNum();
    uint64_t timeNow = NFTime::Now().UnixSec();

    for(int i = 0; i < num; i++)
    {
        if (m_mailID.IsFull())
            break;

        if (descData[i].start_time <= timeNow && timeNow < descData[i].end_time)
        {
            sMailTemplateID* pMail = m_mailID.Add();
            if (!pMail) break;

            pMail->id = descData[i].id;
            pMail->startTime = descData[i].start_time;
            pMail->endTime = descData[i].end_time;
        }
        else if (descData[i].start_time > timeNow)
        {
            if (NFMagicTimeUtil::GetTodayStartTime(descData[i].start_time) == NFMagicTimeUtil::GetTodayStartTime(timeNow))
            {
                sMailTemplateID* pMail = m_mailID.Add();
                if (!pMail) break;

                pMail->id = descData[i].id;
                pMail->startTime = descData[i].start_time;
                pMail->endTime = descData[i].end_time;
            }
        }
    }

    if (m_mailID.GetSize() > 0)
    {
        if (m_userTemplateMailTimer == INVALID_ID)
        {
            m_userTemplateMailTimer = SetTimer(1000, 0, 0, 0, 1, 0);
            if (m_userTemplateMailTimer == INVALID_ID)
            {
                NFLogError(NF_LOG_SYSTEMLOG, 0, "user template mail timer error");
            }
        }
    }
    else
    {
        if (m_userTemplateMailTimer != INVALID_ID)
        {
            DeleteTimer(m_userTemplateMailTimer);
            m_userTemplateMailTimer = INVALID_ID;
        }
    }
    return 0;
}

int NFActivityMail::OnTickRoleTemplateMail()
{
    uint64_t timeNow = NFTime::Now().UnixSec();

    NFOnlineUser *pOnlineRole = (NFOnlineUser *)NFShmMgr::Instance()->GetHeadObj(EOT_SNS_ONLINE_USER_ID);
    while(pOnlineRole)
    {
        NFSnsUserSimple* pSimple = NFSnsUserSimpleUtil::Instance()->GetRoleSimpe(pOnlineRole->GetUserID());
        NFUserMail* roleMailExt = NFUserMailMgr::Instance()->Find(pOnlineRole->GetUserID());
        if(roleMailExt && pSimple)
        {
            for(int i = 0; i < m_mailID.GetSize(); i++)
            {
                if (m_mailID[i].startTime <= timeNow && timeNow < m_mailID[i].endTime)
                {
                    if (!roleMailExt->ActivityMailIsExist(m_mailID[i].id))
                    {
                        if (NFUserMailUtil::OnSendTemplateMail(pOnlineRole->GetUserID(), m_mailID[i].id) == 0)
                        {
                            if (roleMailExt->GetData()->receive_data.IsFull())
                            {
                                roleMailExt->GetData()->receive_data.MemShiftDel(0);
                            }

                            proto_ff_s::UserSpecialMailData_s* pMail = roleMailExt->GetData()->receive_data.Add();
                            pMail->static_id = m_mailID[i].id;
                            pMail->time = m_mailID[i].endTime;
                            roleMailExt->MarkDirty();
                        }
                    }
                }
            }
        }

        pOnlineRole = (NFOnlineUser *)NFShmMgr::Instance()->GetNextObj(EOT_SNS_ONLINE_USER_ID, pOnlineRole);
    }
    return 0;
}

void NFActivityMail::OnTimer(int timeId, int callcount)
{
    if (timeId == m_userGetMailIDTimer)
    {
        OnTickGetMailID();
    }
    else if (timeId == m_userTemplateMailTimer)
    {
        OnTickRoleTemplateMail();
    }
}

