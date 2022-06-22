// -------------------------------------------------------------------------
//    @FileName         :    NFActivityMail.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFActivityMail.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFShmCore/NFArray.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"

struct sMailTemplateID
{
    sMailTemplateID()
    {
        if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
            CreateInit();
        } else {
            ResumeInit();
        }
    }

    int CreateInit()
    {
        id = 0;
        startTime = 0;
        endTime = 0;
        return 0;
    }

    int ResumeInit()
    {
        return 0;
    }
    int id;
    uint64_t startTime;
    uint64_t endTime;
};

class NFActivityMail : public NFShmObj {
public:
    NFActivityMail();

    ~NFActivityMail();

    int CreateInit();

    int ResumeInit();

    int Init();

    int OnTickGetMailID();
    int OnTickRoleTemplateMail();

    virtual void OnTimer(int timeId, int callcount);

private:
    int m_userGetMailIDTimer;
    int m_userTemplateMailTimer;
    NFArray<sMailTemplateID, 100> m_mailID;
DECLARE_IDCREATE(NFActivityMail)
};
