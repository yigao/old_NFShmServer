// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCode..h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCode..h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFMessageDefine/proto_error_code.pb.h"
#include "NFComm/NFCore/NFTime.h"

class NFRedeemCode {
public:
    enum {
        NF_REDEEM_CODE_NONE = 0,
        NF_REDEEM_CODE_USED = 1,
    };
    NFRedeemCode();

    ~NFRedeemCode();

    int CreateInit();

    int ResumeInit();

    bool IsTimeOver();

    std::string GetId() const { return m_redeemCode.id.GetString(); }
    bool IsUsed() const { return m_redeemCode.state == NF_REDEEM_CODE_USED; }
    void SetUsed(uint64_t userId) { m_redeemCode.user_id = userId; m_redeemCode.state = NF_REDEEM_CODE_USED; m_redeemCode.use_time = NFTime::Now().UnixSec(); }
    uint64_t GetGold() const { return m_redeemCode.gold; }

    int Save();
public:
    uint64_t m_lastTime;
    proto_ff_s::tbRedeemCode_s m_redeemCode;
};