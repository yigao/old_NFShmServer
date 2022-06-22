// -------------------------------------------------------------------------
//    @FileName         :    NFTransMailCreate.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFTransMailCreate.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFTransBase.h"
#include "NFComm/NFShmCore/NFSizeString.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"
#include "NFUserMail.h"

#include "NFComm/NFMessageDefine/proto_common.pb.h"
#include "NFComm/NFKernelMessage/storesvr_sqldata.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"


class NFTransMailCreate : public NFTransBase
{
public:
    NFTransMailCreate();
    virtual ~NFTransMailCreate();
    int CreateInit();
    int ResumeInit();
public:
    virtual int Init(uint64_t roleID, bool isGM, uint64_t iSrcSvrID);

    virtual bool IsTimeOut();
    virtual int OnTimeOut();
    int OnTransFinished(int iRunLogicRetCode);
    int HandleTransFinished(int iRunLogicRetCode) { return 0; }
public:
    virtual int HandleCSMsgReq(const google::protobuf::Message *pCSMsgReq) { return 0; }
    virtual int
    HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id, uint32_t seq,
                   uint32_t err_code);
public:
    int TransGetMailBaseRes();
    int ProMailCreateRes(const storesvr_sqldata::storesvr_ins_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
    int ProMailCreateReq(proto_ff::tbUserMailDetail& tb_role_mail);
private:
    proto_ff_s::tbUserMailDetail_s m_tmp;
    uint64_t m_roleID;
    bool m_isGM;
    uint64_t m_iSrcSvrID;
DECLARE_IDCREATE(NFTransMailCreate)
};