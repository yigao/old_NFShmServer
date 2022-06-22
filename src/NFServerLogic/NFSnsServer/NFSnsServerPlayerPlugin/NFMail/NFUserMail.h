// -------------------------------------------------------------------------
//    @FileName         :    NFUserMail.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMail.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFMessageDefine/proto_common.pb.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFShmCore/NFSeqOP.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"


class NFUserMail: public NFShmObj, public NFSeqOP {
public:
    NFUserMail();

    virtual ~NFUserMail();

    int CreateInit();

    int ResumeInit();

    virtual int GetHashKey(void *pvKey, int &iKeyLength);

    virtual int SetHashKey(const void *pvKey, int iKeyLength);

public:
    int Init(const proto_ff::UserMailInfo *pDBRoleData);

    int MakeDataCS(proto_ff::UserMailInfo *pstScoreCS);

    proto_ff_s::UserMailInfo_s *GetData() { return &m_stData; }

    const proto_ff_s::UserMailInfo_s *GetData() const { return &m_stData; }

    uint64_t GetRoleID() const { return m_role_id; }

    void SetRoleID(uint64_t roleId) { m_role_id = roleId; }
public:
    bool ActivityMailIsExist(int32_t desc_id);

    bool IsHaveMail() {
        return (m_stData.simple_mail.GetSize() > 0);
    }

    void SetRoleDetailSavedSeq(uint32_t seq) { m_dwSavedSeq = seq; }

    void SetRoleDetailSavingDBTime(uint32_t time) { m_dwSavingDBTime = time; }

    bool IsRoleDetailSaved() const;

    bool IsRoleDetailNeedSave(uint32_t dwTimeNow) const;

    bool IsTimeToSave();

    void SetSaving(bool bSet) { m_bInSaving = bSet; }

    bool IsInSaving() { return m_bInSaving; }

    // 是否可以释放
    bool IsDelete();

    // 定时清除过期邮件
    int RefreshMail();

    // 关服保存
    int SaveBeforeShutDown();

    int Tick();

    int GetSimpleRemainCount() {
        return (int) m_stData.simple_mail.GetMaxSize() - GetSimpleMailSize();
    }

    proto_ff_s::SingleMailInfo_s *GetSimpleMail(uint64_t mailID);

    bool SetSimpleMailStatusRead(uint64_t mailID);

    proto_ff_s::SingleMailInfo_s *AddSimpleMail();

    proto_ff_s::SingleMailInfo_s *GetSimpleMailByIndex(int index);

    int GetSimpleMailSize() {
        return m_stData.simple_mail.GetSize();
    }

    int GetAllMailSize() {
        return m_stData.simple_mail.GetSize();
    }

    int GetAllNoReadMailSize();

    int AddDeletedMail(uint64_t mailID);

    bool IsDeletedMail(uint64_t mailID);

    int ClearDeletedMail(const std::vector<uint64_t>& mailID);

    int DelSimpleMail(uint64_t id);

private:
    bool m_bIsInited;
    uint64_t m_role_id;
    proto_ff_s::UserMailInfo_s m_stData;
    uint32_t m_dwSavedSeq;
    uint32_t m_dwSavingDBTime;
    bool m_bInSaving;
    uint32_t m_lastDelTime;
DECLARE_IDCREATE(NFUserMail)
};