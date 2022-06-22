// -------------------------------------------------------------------------
//    @FileName         :    NFMailDesc.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFMailDesc.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFIDescStore.h"
#include "NFComm/NFMessageDefine/ResMeta_s.h"
#include "NFComm/NFShmCore/NFShmMgr.h"

#define MAX_MAIL_DESC_NUM 1000

class NFMailDesc : public NFIDescStore
{
public:
    NFMailDesc();
    virtual ~NFMailDesc();
    int CreateInit();
    int ResumeInit();

    const proto_ff_s::MailDesc_s* GetDesc(int32_t descId) const;
public:
    IMPL_RES_DESC(proto_ff_s::MailDesc_s, MailDesc, MAX_MAIL_DESC_NUM);
    int m_aiIndex[MAX_MAIL_DESC_NUM];
    DECLARE_IDCREATE(NFMailDesc);
};
