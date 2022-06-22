// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCodeMgr.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCodeMgr.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFShmCore/NFShmHashMap.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"
#include "NFRedeemCode.h"
#define MAX_REDEEM_CODE_NUM 500

class NFRedeemCodeMgr: public NFShmObj
{
public:
    NFRedeemCodeMgr();

    virtual ~NFRedeemCodeMgr();

    int CreateInit();

    int ResumeInit();

    NFRedeemCode * Find(const std::string& id);

    NFRedeemCode* Insert(const std::string& id, const proto_ff::tbRedeemCode& code);

    int Delete(const std::string &id);

    bool IsFull() { return m_redeemCodeMgr.IsFull(); }

    void ClearTimeOut();

    void ClearFull();

    //must be virtual
    virtual void OnTimer(int timeId, int callcount);
private:
    typedef NFSizeString<128> RedeemKey;
    NFShmHashMap<RedeemKey, NFRedeemCode, MAX_REDEEM_CODE_NUM> m_redeemCodeMgr;
    int m_timeId;
DECLARE_IDCREATE(NFRedeemCodeMgr)
};