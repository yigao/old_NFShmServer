// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCodeMgr.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCodeMgr.cpp
//
// -------------------------------------------------------------------------

#include "NFRedeemCodeMgr.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFRedeemCode.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFRedeemCodeMgr, EOT_REDEEM_CODE_MGR_ID, NFShmObj)

NFRedeemCodeMgr::NFRedeemCodeMgr() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFRedeemCodeMgr::~NFRedeemCodeMgr() {
    if (m_timeId != INVALID_ID)
    {
        DeleteTimer(m_timeId);
        m_timeId = INVALID_ID;
    }
}

int NFRedeemCodeMgr::CreateInit() {
    m_timeId = INVALID_ID;
    m_redeemCodeMgr.CreateInit();
    m_timeId = SetTimer(1000, 0, 0, 0, 10, 0);
    return 0;
}

int NFRedeemCodeMgr::ResumeInit() {
    return 0;
}

NFRedeemCode *NFRedeemCodeMgr::Find(const std::string &id) {
    RedeemKey key;
    key = id;
    return m_redeemCodeMgr.Find(key);
}

NFRedeemCode *NFRedeemCodeMgr::Insert(const std::string &id, const proto_ff::tbRedeemCode& code) {
    RedeemKey key;
    key = id;
    NFRedeemCode *pCode = m_redeemCodeMgr.Insert(key);
    if (pCode)
    {
        proto_ff_s::tbRedeemCode_s::read_from_pbmsg(code, pCode->m_redeemCode);
    }

    return pCode;
}

int NFRedeemCodeMgr::Delete(const std::string &id) {
    return 0;
}

void NFRedeemCodeMgr::ClearTimeOut()
{
    for(int i = 0; i < m_redeemCodeMgr.GetSize(); i++)
    {
        NFRedeemCode* pCode =  m_redeemCodeMgr.GetByIndex(i);
        if (pCode)
        {
            if (pCode->IsTimeOver())
            {
                m_redeemCodeMgr.EraseBySID(i);
            }
        }
    }
}

void NFRedeemCodeMgr::OnTimer(int timeId, int callcount)
{
    if (m_timeId == timeId)
    {
        ClearTimeOut();
    }
}

void NFRedeemCodeMgr::ClearFull()
{
    if (IsFull())
    {
        for(int i = 0; i < m_redeemCodeMgr.GetSize(); i++)
        {
            NFRedeemCode* pCode =  m_redeemCodeMgr.GetByIndex(i);
            if (pCode)
            {
                if (pCode->IsTimeOver())
                {
                    m_redeemCodeMgr.EraseBySID(i);
                }
            }
        }
    }

    if (IsFull())
    {
        for(int i = 0; i < m_redeemCodeMgr.GetSize(); i++)
        {
            NFRedeemCode* pCode =  m_redeemCodeMgr.GetByIndex(i);
            if (pCode)
            {
                if (pCode->IsUsed())
                {
                    m_redeemCodeMgr.EraseBySID(i);
                    return;
                }
            }
        }
    }
}
