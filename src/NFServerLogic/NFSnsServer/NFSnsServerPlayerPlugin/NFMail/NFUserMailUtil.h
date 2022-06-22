// -------------------------------------------------------------------------
//    @FileName         :    NFUserMailCache.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFUserMailCache.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFShmCore/NFShmHashTable.h"
#include "NFComm/NFShmCore/NFShmHashMap.h"
#include "NFServer/NFCommHead/NFUserMailDefine.h"
#include "NFComm/NFShmCore/NFShmStaticList.hpp"
#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_email.pb.h"
#include "NFUserMailCacheInfo.h"

class NFSnsUserSimple;
class NFUserMail;
class NFUserMailUtil : public NFShmObj
{
public:
    NFUserMailUtil();

    virtual ~NFUserMailUtil();

    int CreateInit();

    int ResumeInit();
public:
    bool CacheFull();
    NFUserMailCacheInfo *GetMailCache(uint64_t roleID);
    NFUserMailCacheInfo * AddMailCache(uint64_t roleID);
    int ReleaseNum(int num);
    bool DeleteMailCache(uint64_t roleID);
public:
    static int AddMailCache(NFUserMailCacheInfo *mailInfo, proto_ff::tbUserMailDetail &newMail);

    static bool IsSimpleMailHasItem(proto_ff_s::tbUserMailDetail_s* pMail);

    static int OnCreateMail(proto_ff::tbUserMailDetail& mailInfo, uint64_t roleID, bool isGM = false, uint64_t iSrcSvrID = 0);
    static int FillMailTemplate(proto_ff::tbUserMailDetail& tb_role_mail);

    static int OnSendTemplateMail(uint64_t roleID, int staticID);
public:
    static int MakeSimpleMailToClient(proto_email::UserMailData *clientMail, proto_ff_s::tbUserMailDetail_s &simpleMail, proto_ff::enSnsMailStatus status);
    static int AddMailRes(NFUserMail *roleMailExt, uint64_t roleID, proto_ff_s::tbUserMailDetail_s &mail);
    static int SendMailListToClient(NFUserMail* pUserMailExt, uint64_t roleId, NFUserMailCacheInfo* pMailInfo, int begin, int end);

    static int MakeAllMailRead(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_email::Proto_CSMailReadRsp& req);
    static int ClearRoleMailDB(uint64_t roleID);

    static int DeleteAllCacheMail(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, uint64_t roleID);
    static int SendGetMailItemToClient(NFUserMail *roleMailExt, uint64_t roleID, NFUserMailCacheInfo *mailInfo, uint64_t mailID);
    static int MakeAllGotMailItem(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_ff::Proto_STLMailReadItemReq& req);
    static int MakeGotMailItem(NFUserMail *roleMailExt, NFUserMailCacheInfo *mailInfo, proto_ff::Proto_STLMailReadItemReq& req, uint64_t mailID);

    static int ProDeleteOpGetCacheRes(uint64_t roleID, const std::vector<uint64_t>& vecDel);
public:
    static int ProGetMailListRes(NFUserMail* pUserMailExt, uint64_t roleId, int begin, int end);
    static int ProReadMailRes(NFUserMail* pUserMailExt, uint64_t roleId, uint64_t mailID);
    static int ProDeleteMailRes(NFUserMail* pUserMailExt, uint64_t roleId, const std::vector<uint64_t>& vecMail);
    static int ProGetMailItemRes(NFUserMail *roleMailExt, uint64_t roleID, uint64_t mailID);
public:
    static std::vector<uint64_t> GetDiffMailId(NFUserMail* pUserMailExt, NFUserMailCacheInfo *pMailCacheInfo);
    static int CheckUserMailInfo(uint64_t userId, NFUserMail* pUserMailExt, NFUserMailCacheInfo *pMailCacheInfo);
public:
    static int OnPlayerLogin(NFSnsUserSimple* pSimple);
    static int OnPlayerLogout(NFSnsUserSimple* pSimple);
private:
DECLARE_IDCREATE(NFUserMailUtil)
};
