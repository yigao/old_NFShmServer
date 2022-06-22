// -------------------------------------------------------------------------
//    @FileName         :    NFUserMail.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMail.cpp
//
// -------------------------------------------------------------------------

#include "NFUserMail.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFTransMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFUserMail, EOT_USER_MAIL_EXT_ID, NFShmObj)

NFUserMail::NFUserMail() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFUserMail::~NFUserMail() {

}

int NFUserMail::CreateInit() {
    m_bIsInited = false;
    m_role_id = 0;
    memset(&m_stData, 0, sizeof(m_stData));
    m_dwSavedSeq = 0;
    m_dwSavingDBTime = 0;
    m_bInSaving = false;

    return 0;
}

int NFUserMail::ResumeInit() {
    return 0;
}

int NFUserMail::GetHashKey(void *pvKey, int &iKeyLength) {
    *((uint64_t *) pvKey) = m_role_id;
    iKeyLength = sizeof(m_role_id);
    return 0;
}

int NFUserMail::SetHashKey(const void *pvKey, int iKeyLength) {
    m_role_id = *((uint64_t *) pvKey);
    return 0;
}

int NFUserMail::MakeDataCS(proto_ff::UserMailInfo *pstScoreCS) {
    CHECK_EXPR(pstScoreCS, -1, "pstScoreCS == NULL");

    proto_ff_s::UserMailInfo_s::write_to_pbmsg(m_stData, *pstScoreCS);
    return 0;
}

int NFUserMail::Init(const proto_ff::UserMailInfo *pDBRoleData) {
    CHECK_EXPR(pDBRoleData, -1, "pDBRoleData == NULL");
    proto_ff_s::UserMailInfo_s::read_from_pbmsg(*pDBRoleData, m_stData);

    m_bIsInited = true;
    ResetCurSeq();
    RefreshMail();
    return 0;
}

int NFUserMail::RefreshMail() {
    if (!m_bIsInited)
        return -1;

    uint64_t timeNow = NFTime::Now().UnixSec();
    for (int i = 0; i < m_stData.receive_data.GetSize();) {
        if (m_stData.receive_data[i].time <= timeNow) {
            m_stData.receive_data.MemShiftDel(i);
            MarkDirty();
        } else {
            ++i;
        }
    }

    if (m_stData.del_role_mail.GetSize() >= ROLE_MAIL_GET_MAIL_MAX && timeNow - m_lastDelTime > 5) {
        NFTransMail *pTransDel = (NFTransMail *)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
        if (pTransDel) {
            m_lastDelTime = timeNow;
            pTransDel->Init(m_role_id);
            int iRetCode = pTransDel->ProMailDelReq(this);
            if (iRetCode) {
                NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_role_id, "tick delete mail error:{}", m_role_id);
                pTransDel->SetFinished(iRetCode);
            }
        }
    }

    return 0;
}

bool NFUserMail::IsTimeToSave() {
    if (NFTime::Now().UnixSec() - m_dwSavingDBTime >= 60) {
        return true;
    }

    return false;
}

bool NFUserMail::IsRoleDetailNeedSave(uint32_t dwTimeNow) const {
    if (!IsRoleDetailSaved()) {
        return true;
    }

    return false;
}

bool NFUserMail::IsRoleDetailSaved() const {
    return GetCurSeq() == m_dwSavedSeq;
}

int NFUserMail::Tick() {
    uint32_t tNow = NFTime::Now().UnixSec();

    if (IsTimeToSave() && IsRoleDetailNeedSave(tNow) && !IsInSaving()) {
        NFLogInfo(NF_LOG_USER_MAIL_PLUGIN, m_role_id, "RoleID:{} Save Role mail for Normal", m_role_id);

        NFTransMail *pTransSaveRoleDetail = (NFTransMail *) NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
        CHECK_PLAYER_EXPR(m_role_id, pTransSaveRoleDetail, -1,
                          "RoleID:{}  Create SaveTrans Failed!", m_role_id);

        pTransSaveRoleDetail->Init(m_role_id);
        if (pTransSaveRoleDetail->ProMailSaveReq(this) == 0) {
            SetRoleDetailSavingDBTime(tNow);
            SetSaving(true);
        } else {
            NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_role_id, "save mail error:{}", m_role_id);
            pTransSaveRoleDetail->SetFinished(-1);
        }
    }

    return 0;
}

int NFUserMail::SaveBeforeShutDown() {
    if (!IsRoleDetailSaved() && !IsInSaving()) {
        NFTransMail *pTransSaveRoleDetail = (NFTransMail *)NFShmMgr::Instance()->CreateTrans(EOT_TRANS_USER_MAIL_ID);
        CHECK_PLAYER_EXPR(m_role_id, pTransSaveRoleDetail, -1,
                          "RoleID:{} Create SaveTrans Failed!", m_role_id);

        pTransSaveRoleDetail->Init(m_role_id);
        if (pTransSaveRoleDetail->ProMailSaveReq(this) == 0) {
            SetRoleDetailSavingDBTime(NFTime::Now().UnixSec());
            SetSaving(true);
        } else {
            NFLogError(NF_LOG_USER_MAIL_PLUGIN, m_role_id, "save mail error:{}", m_role_id);
            pTransSaveRoleDetail->SetFinished(-1);
        }
    }

    return 0;
}

bool NFUserMail::IsDelete() {
    if (IsRoleDetailSaved() && !IsInSaving()) {
        NFOnlineUser *pRole = NFOnlineUserMgr::GetInstance()->Find(m_role_id);
        if (!pRole) {
            return true;
        }
        return false;
    }

    return false;
}

bool NFUserMail::ActivityMailIsExist(int32_t desc_id)
{
   for (int i = 0; i < m_stData.receive_data.GetSize(); i++)
   {
       if (m_stData.receive_data[i].static_id == desc_id)
       {
            return true;
       }
   }
   return false;
}

proto_ff_s::SingleMailInfo_s *NFUserMail::GetSimpleMailByIndex(int index) {
    if (index < 0 || index >= m_stData.simple_mail.GetSize())
        return NULL;

    return &m_stData.simple_mail[index];
}

proto_ff_s::SingleMailInfo_s *NFUserMail::AddSimpleMail() {
    if (m_stData.simple_mail.IsFull() && m_stData.simple_mail.GetSize() > 0) {
        uint64_t id = m_stData.simple_mail[0].id;
        m_stData.simple_mail.MemShiftDel(0);
        AddDeletedMail(id);
    }

    proto_ff_s::SingleMailInfo_s *tMailInfo = m_stData.simple_mail.Add();

    memset(tMailInfo, 0, sizeof(proto_ff_s::SingleMailInfo_s));
    MarkDirty();

    return tMailInfo;
}

bool NFUserMail::SetSimpleMailStatusRead(uint64_t mailID) {
    bool is_find = false;

    for (int i = 0; i < m_stData.simple_mail.GetSize(); ++i) {
        if (m_stData.simple_mail[i].id == mailID) {
            m_stData.simple_mail[i].status = proto_ff::EN_SNS_MAIL_ALREADY_READ;
            is_find = true;
            MarkDirty();
            break;
        }
    }

    return is_find;
}

proto_ff_s::SingleMailInfo_s *NFUserMail::GetSimpleMail(uint64_t mailID) {
    for (int i = 0; i < m_stData.simple_mail.GetSize(); ++i) {
        if (m_stData.simple_mail[i].id == mailID) {
            return &m_stData.simple_mail[i];
        }
    }

    return NULL;
}

int NFUserMail::AddDeletedMail(uint64_t mailID) {
    if (m_stData.del_role_mail.IsFull()) {
        NFLogError(NF_LOG_USER_MAIL_PLUGIN, 0, "del role mail err:{} {}", mailID, m_role_id);
        m_stData.del_role_mail.MemShiftDel(0);
    }

    m_stData.del_role_mail.Add(mailID);
    MarkDirty();
    RefreshMail();

    return 0;
}

bool NFUserMail::IsDeletedMail(uint64_t mailID)
{
    for(int i = 0; i < m_stData.del_role_mail.GetSize(); i++)
    {
        if (m_stData.del_role_mail[i] == mailID)
        {
            return true;
        }
    }
    return false;
}

int NFUserMail::ClearDeletedMail(const std::vector<uint64_t>& mailID)
{
    if (mailID.size() > 0) {
        for (int i = 0; i < (int)mailID.size(); ++i) {
            for (int j = 0; j < (int)m_stData.del_role_mail.GetSize(); ++j) {
                if (mailID[i] == m_stData.del_role_mail[j]) {
                    m_stData.del_role_mail.MemShiftDel(j);
                    break;
                }
            }
        }
    } else {
        m_stData.del_role_mail.CreateInit();
        m_stData.del_role_mail.SetSize(0);
    }

    MarkDirty();

    return 0;
}

int NFUserMail::GetAllNoReadMailSize()
{
    int count = 0;
    for(int i = 0; i < m_stData.simple_mail.GetSize(); ++i)
    {
        if(m_stData.simple_mail[i].status == proto_ff::EN_SNS_MAIL_NO_READ)
            ++count;
    }

    return count;
}

int NFUserMail::DelSimpleMail(uint64_t id)
{
    for(int i = 0; i < m_stData.simple_mail.GetSize(); ++i)
    {
        if(m_stData.simple_mail[i].id == id)
        {
            if(m_stData.simple_mail[i].status == proto_ff::EN_SNS_MAIL_NO_READ)
            {
                return proto_ff::ERR_CODE_MAIL_CANT_DEL_NO_READ;
            }
            else
            {
                m_stData.simple_mail.MemShiftDel(i);
                AddDeletedMail(id);
                MarkDirty();

                return 0;
            }
        }
    }

    return -1;
}
