// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailMgr.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailMgr.cpp
//
// -------------------------------------------------------------------------

#include "NFUserMailMgr.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFUserMail.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFUserMailMgr, EOT_USER_MAIL_HASHTABLE_ID, NFShmObj)

NFUserMailMgr::NFUserMailMgr()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFUserMailMgr::~NFUserMailMgr()
{

}

int NFUserMailMgr::CreateInit() {
    m_mailTimer = INVALID_ID;
    return 0;
}

int NFUserMailMgr::ResumeInit() {
    return 0;
}


NFUserMail * NFUserMailMgr::Find(uint64_t ullRoleID)
{
    return dynamic_cast<NFUserMail *>(NFShmMgr::Instance()->GetObjFromHashKey(ullRoleID, EOT_USER_MAIL_EXT_ID));
}

NFUserMail* NFUserMailMgr::Insert(uint64_t ullRoleID)
{
    NFUserMail* pRoleMail = NULL;
    pRoleMail = Find(ullRoleID);
    if(pRoleMail)
    {
        return pRoleMail;
    }

    if(IsFull())
    {
        ReleaseCount(GetItemCount()*0.1);
    }

    pRoleMail = dynamic_cast<NFUserMail *>(NFShmMgr::Instance()->CreateObj(ullRoleID, EOT_USER_MAIL_EXT_ID));
    if(!pRoleMail)
    {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "insert role mail failed, ullRoleID={}", ullRoleID);
        return NULL;
    }

    pRoleMail->SetRoleID(ullRoleID);

    return pRoleMail;
}

int NFUserMailMgr::ReleaseCount(int num)
{
    NFLogTrace(NF_LOG_USER_MAIL_PLUGIN, 0, "role mail release count :{} maxcount:{} usecount:{}", num, NFUserMail::GetItemCount(), NFUserMail::GetUsedCount());

    NFShmMgr::Instance()->DestroyObjAutoErase(EOT_USER_MAIL_EXT_ID, NFUserMail::GetUsedCount() >= num ? NFUserMail::GetUsedCount() - num : 0, [](NFShmObj* pObj) -> bool {
        NFUserMail * pRoleMail = dynamic_cast<NFUserMail *>(pObj);
        if (pRoleMail)
        {
            if (pRoleMail->IsDelete())
            {
                return true;
            }
        }
        return false;
    });

    return 0;
}

int NFUserMailMgr::Delete(uint64_t ullRoleID)
{
    NFUserMail* pRoleMail = Find(ullRoleID);
    CHECK_NULL(pRoleMail);

    NFShmMgr::Instance()->DestroyObj(pRoleMail);

    return 0;
}

void NFUserMailMgr::OnTickUserMailExt()
{
    NFUserMail *pMail = dynamic_cast<NFUserMail*>(NFShmMgr::Instance()->GetHeadObj(EOT_USER_MAIL_EXT_ID));
    while (pMail)
    {
        pMail->Tick();
        pMail = dynamic_cast<NFUserMail*>(NFShmMgr::Instance()->GetNextObj(EOT_USER_MAIL_EXT_ID, pMail));
    }
}

int NFUserMailMgr::Init()
{
    if (m_mailTimer == INVALID_ID)
    {
        m_mailTimer = SetTimer(SNSSVR_USER_MAIL_SAVE_TIME, 0, 0, 0, 10, 0);
    }
    return 0;
}

void NFUserMailMgr::OnTimer(int timeId, int callcount)
{
    if (timeId == m_mailTimer)
    {
        OnTickUserMailExt();
    }
}

bool NFUserMailMgr::IsFull()
{
    return NFUserMail::GetUsedCount() >= NFUserMail::GetItemCount();
}
