// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailCacheInfo.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailCacheInfo.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFCore/NFPlatform.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFShmCore/NFShmObj.h"

class NFUserMailCacheInfo : public NFShmObj {
public:
    NFUserMailCacheInfo() {
        if (NFShmMgr::Instance()->GetCreateMode() == EN_OBJ_MODE_INIT) {
            CreateInit();
        } else {
            ResumeInit();
        }
    }

    int CreateInit()
    {
        isInit = false;
        userID = 0;
        memset(&mailInfo, 0, sizeof(mailInfo));
        return 0;
    }

    int ResumeInit()
    {
        return 0;
    }

    int GetSimpleMailSize()
    {
        return mailInfo.simple_mail.GetSize();
    }

    proto_ff_s::tbUserMailDetail_s * GetSimpleMail(uint64_t mailID)
    {
        for(int i = 0; i < mailInfo.simple_mail.GetSize(); i++)
        {
            if (mailInfo.simple_mail[i].id == mailID)
            {
                return &mailInfo.simple_mail[i];
            }
        }
        return NULL;
    }

    proto_ff_s::tbUserMailDetail_s * AddSimpleMail()
    {
        if (mailInfo.simple_mail.IsFull())
        {
            mailInfo.simple_mail.MemShiftDel(0);
        }

        proto_ff_s::tbUserMailDetail_s* pInfo = mailInfo.simple_mail.Add();
        CHECK_EXPR(pInfo, NULL, "mailInfo.simple_mail.Add() Failed");

        memset(pInfo, 0, sizeof(proto_ff_s::tbUserMailDetail_s));
        return pInfo;
    }

    int DelSimpleMail(uint64_t id)
    {
        for(int i=0; i< mailInfo.simple_mail.GetSize(); ++i)
        {
            if(mailInfo.simple_mail[i].id == id)
            {
                mailInfo.simple_mail.MemShiftDel(i);
                break;
            }
        }

        return 0;
    }

    uint64_t userID;
    bool isInit;
    proto_ff_s::UserMailDetailInfo_s mailInfo;
    DECLARE_IDCREATE(NFUserMailCacheInfo)
};
