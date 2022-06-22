// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailHastTable.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailHastTable.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"

class NFUserMail;

class NFUserMailMgr : public NFShmObj
{
public:
    NFUserMailMgr();

    virtual ~NFUserMailMgr();

    int CreateInit();

    int ResumeInit();
public:
    int Init();
    //must be virtual
    virtual void OnTimer(int timeId, int callcount);

    NFUserMail *Insert(uint64_t ullRoleID);
    NFUserMail *Find(uint64_t ullRoleID);
    int Delete(uint64_t ullRoleID);
    int ReleaseCount(int num);

    bool IsFull();

    void OnTickUserMailExt();
private:
    int m_mailTimer;
DECLARE_IDCREATE(NFUserMailMgr)
};

