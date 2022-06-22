// -------------------------------------------------------------------------
//    @FileName         :    NFCWebUserManagerModule.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCWebUserManagerModule.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFServerDefine.h"
#include "NFComm/NFCore/NFMapEx.hpp"
#include "NFComm/NFCore/NFMap.hpp"
#include "NFServer/NFCommHead/NFIWebServerModule.h"
#include "NFServer/NFCommHead/NFCommLogicHead.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_login.pb.h"

class NFCWebUserManagerModule : public NFIDynamicModule
{
public:
    explicit NFCWebUserManagerModule(NFIPluginManager* p);
    virtual ~NFCWebUserManagerModule();

    virtual bool Awake() override;

    virtual bool Init() override;

    virtual bool Execute() override;

    virtual void OnTimer(uint32_t nTimerID) override;
public:
    bool HandleSetBaoDi(uint32_t, const NFIHttpHandle &req);
    bool HandleSetTaxBaoDi(uint32_t, const NFIHttpHandle &req);
    bool HandleModifyAgent(uint32_t, const NFIHttpHandle &req);
    bool HandleModifyLiuShui(uint32_t, const NFIHttpHandle &req);
    bool HandleModifySetBan(uint32_t, const NFIHttpHandle &req);
    bool HandleModifySetTransfer(uint32_t, const NFIHttpHandle &req);
    bool HandleSendUserMail(uint32_t, const NFIHttpHandle &req);
    bool HandleZhuangZhangRecharge(uint32_t, const NFIHttpHandle &req);
    bool HandleGiveMoney(uint32_t, const NFIHttpHandle &req);
    bool HandleSetUserWhiteBlackList(uint32_t, const NFIHttpHandle &req);
    bool DeleteSetUserWhiteBlackList(uint32_t, const NFIHttpHandle &req);

    //清理奖池
    bool ClearJiangChi(uint32_t, const NFIHttpHandle &req);
    //配置奖池
    bool SetJiangChi(uint32_t, const NFIHttpHandle &req);

    bool SetRoomStatus(uint32_t, const NFIHttpHandle &req);

    bool HandleSetGMCtrlGiveData(uint32_t, const NFIHttpHandle &req);
    bool DeleteGMCtrlGiveData(uint32_t, const NFIHttpHandle &req);

    bool AddRedemCode(uint32_t, const NFIHttpHandle &req);

    bool ModifyShowUserid(uint32_t, const NFIHttpHandle &req);

    bool ModifyNickName(uint32_t, const NFIHttpHandle &req);

    bool ModifyVipLevel(uint32_t, const NFIHttpHandle &req);
    bool ModifyAccountPassword(uint32_t, const NFIHttpHandle &req);
    bool ModifyBankPassword(uint32_t, const NFIHttpHandle &req);

    bool VipRecharge(uint32_t, const NFIHttpHandle &req);
};


