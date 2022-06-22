// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCodeTrans
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCodeTrans.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransSnsBase.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFComm/NFMessageDefine/proto_svr_rank.pb.h"

class NFRedeemCodeTrans : public NFTransBase
{
public:
    NFRedeemCodeTrans();

    virtual ~NFRedeemCodeTrans();

    int CreateInit();

    int ResumeInit();

    virtual int
    HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id, uint32_t seq,
                   uint32_t err_code);
public:
    int InitThisTrans(uint64_t userId, uint32_t cmd, const std::string& id);
    int HandleRedeemCodeReq();
    int ReqGetRedeemCodeData();
    int ProRedeemCodeRes(const storesvr_sqldata::storesvr_selobj_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
public:
    int OnTransFinished(int iRunLogicRetCode) { return 0; }
    int HandleTransFinished(int iRunLogicRetCode) { return 0; }
private:
    uint64_t m_userId;
    uint32_t m_cmd;
    NFSizeString<128> m_redeemCodeId;
    DECLARE_IDCREATE(NFRedeemCodeTrans)
};