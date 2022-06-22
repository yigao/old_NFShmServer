// -------------------------------------------------------------------------
//    @FileName         :    NFTransMail.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFTransMail.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFTransBase.h"
#include "NFComm/NFShmCore/NFSizeString.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"
#include "NFUserMail.h"
#include "NFUserMailCacheInfo.h"

#include "NFComm/NFMessageDefine/proto_common.pb.h"
#include "NFComm/NFKernelMessage/storesvr_sqldata.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_email.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_login.pb.h"


class NFTransMail : public NFTransBase
{
    enum {
        CHECK_ACCOUNT_EXIST,
        CREATE_ACCOUNT,
    };
public:
    NFTransMail();
    virtual ~NFTransMail();
    int CreateInit();
    int ResumeInit();
public:
    virtual int Init(uint64_t roleID, uint64_t id = 0, int transID = -1, int cmd = 0, int begin = 0, int end = 0);
    virtual int Init(uint64_t roleID, int cmd, std::vector<uint64_t> &vec);

    virtual bool IsTimeOut();
    virtual int OnTimeOut();
    int OnTransFinished(int iRunLogicRetCode);
    int HandleTransFinished(int iRunLogicRetCode) { return 0; }

public:
    virtual int HandleCSMsgReq(const google::protobuf::Message *pCSMsgReq);
    virtual int
    HandleDBMsgRes(const google::protobuf::Message *pSSMsgRes, uint32_t cmd, uint32_t table_id, uint32_t seq,
                   uint32_t err_code);
public:
    int ProGetMailBaseInfoReq();
    int ProMailListReq(NFUserMail *roleMailExt, int simpleCount = 0);
    int LoadMailList(const std::vector<uint64_t>& vecMailId);
    int ProMailDelReq(NFUserMail *roleMailExt);
    int ProMailDelReq();
    int ProMailSaveReq(NFUserMail *roleMailExt);

    int ProMailListRes(const storesvr_sqldata::storesvr_sel_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
    int ProMailDelRes(const storesvr_sqldata::storesvr_del_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
    int ProGetMailBaseInfoRes(const storesvr_sqldata::storesvr_selobj_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
    int ProMailBaseCreateRes(const storesvr_sqldata::storesvr_ins_res* pSelRsp, uint32_t cmd, uint32_t table_id, uint32_t err_code);
    int ProSaveRoleMailRes(const storesvr_sqldata::storesvr_modobj_res* pSelectRsp, uint32_t cmd, uint32_t table_id, uint32_t seq, uint32_t err_code);
private:
    int HandleGetMailBaseInfoMsgParam(const google::protobuf::Message *pMsgRes);
    int HandleGetBaseInfoRes(NFUserMail *roleMailExt);
    int HandleGetMailCacheRes(NFUserMailCacheInfo* mailCacheInfo);
private:
    uint64_t m_mailID;
    uint64_t m_roleID;
    int m_cmd;
    int m_begin;
    int m_end;
    int m_transID;
    enTransMailHandleType m_type;
    NFArray<uint64_t, ROLE_MAIL_GET_MAIL_MAX*2> m_delMailID;
DECLARE_IDCREATE(NFTransMail)
};