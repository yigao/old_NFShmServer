// -------------------------------------------------------------------------
//    @FileName         :    NFCWebUserManagerModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCWebUserManagerModule.cpp
//
// -------------------------------------------------------------------------

#include "NFCWebUserManagerModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFServer/NFCommHead/NFICommLogicModule.h"
#include "NFComm/NFPluginModule/NFIMonitorModule.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFPluginModule/NFIAsyMysqlModule.h"
#include "NFComm/NFCore/NFMD5.h"
#include "NFComm/NFCore/NFHmacSha.h"
#include "NFComm/NFCore/NFBase64.h"
#include "NFComm/NFCore/NFStringUtility.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFProtobufCommon.h"
#include "NFComm/NFMessageDefine/proto_svr_web.pb.h"
#include "NFComm/NFCore/NFRandom.hpp"
#include <stdio.h>

NFCWebUserManagerModule::NFCWebUserManagerModule(NFIPluginManager* p):NFIDynamicModule(p)
{
}

NFCWebUserManagerModule::~NFCWebUserManagerModule()
{
}

bool NFCWebUserManagerModule::Awake() {

    //设置流水保底
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setbaodi", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleSetBaoDi);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setbaodi", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleSetBaoDi);
    //设置税收保底
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "settaxbaodi", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleSetTaxBaoDi);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "settaxbaodi", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleSetTaxBaoDi);
    //修改上级代理ID
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyagent", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleModifyAgent);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyagent", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleModifyAgent);
    //修改流水
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyliushui", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleModifyLiuShui);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyliushui", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleModifyLiuShui);
    //封号
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setban", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleModifySetBan);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setban", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleModifySetBan);
    //禁止转钱
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "settransfer", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleModifySetTransfer);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "settransfer", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleModifySetTransfer);
    //给玩家发送邮件
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "sendusermail", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleSendUserMail);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "sendusermail", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleSendUserMail);
    //转账充值
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "zhuangzhang", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleZhuangZhangRecharge);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "zhuangzhang", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleZhuangZhangRecharge);
    //web赠送
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "givemoney", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::HandleGiveMoney);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "givemoney", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleGiveMoney);

    //设置玩家游戏的黑白名单
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setuserwhiteblacklist", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleSetUserWhiteBlackList);

    //删除玩家游戏的黑白名单
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "deleteuserwhiteblacklist", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::DeleteSetUserWhiteBlackList);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "deleteuserwhiteblacklist", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::DeleteSetUserWhiteBlackList);

    //清理奖池
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "clearjiangchi", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ClearJiangChi);

    //配置奖池
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setjiangchi", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::SetJiangChi);

    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setroomstatus", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::SetRoomStatus);

    //设置玩家游戏的黑白名单
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "setgmctrlgivedata", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::HandleSetGMCtrlGiveData);

    //删除玩家游戏的黑白名单
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "deletegmctrlgivedata", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::DeleteGMCtrlGiveData);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "deletegmctrlgivedata", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::DeleteGMCtrlGiveData);

    //添加点卡
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "addtedeemcode", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::AddRedemCode);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "addtedeemcode", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::AddRedemCode);

    //修改代理靓号
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyuserid", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::ModifyShowUserid);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyuserid", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ModifyShowUserid);

    //修改昵称
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyname", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::ModifyNickName);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyname", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ModifyNickName);

    //修改Vip
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyviplevel", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::ModifyVipLevel);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifyviplevel", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ModifyVipLevel);

    //修改账号密码
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifypassword", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::ModifyAccountPassword);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifypassword", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ModifyAccountPassword);

    //修改银行密码
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifybankpassword", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::ModifyBankPassword);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "modifybankpassword", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::ModifyBankPassword);

    //vip recharge
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "viprecharge", NF_HTTP_REQ_GET, this, &NFCWebUserManagerModule::VipRecharge);
    NFMessageMgr::Instance()->AddHttpRequestHandler(NF_ST_WEB_SERVER, "viprecharge", NF_HTTP_REQ_POST, this, &NFCWebUserManagerModule::VipRecharge);


    return true;
}

bool NFCWebUserManagerModule::Init() {

    return true;
}

bool NFCWebUserManagerModule::Execute() {
    return true;
}

void NFCWebUserManagerModule::OnTimer(uint32_t nTimerID)
{
}

//设置流水保底
bool NFCWebUserManagerModule::HandleSetBaoDi(uint32_t serverType, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetBaoDi data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_SetBaoDi_REQ, data);

    return true;
}

//设置税收保底
bool NFCWebUserManagerModule::HandleSetTaxBaoDi(uint32_t serverType, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetTaxBaoDi data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_SetTaxBaoDi_REQ, data);

    return true;
}

bool NFCWebUserManagerModule::HandleModifyAgent(uint32_t serverType, const NFIHttpHandle &req) {
    proto_ff::Proto_Web_ModifyAgent data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0) {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_ModifyAgent_REQ, data);

    return true;
}

bool NFCWebUserManagerModule::HandleModifyLiuShui(uint32_t serverType, const NFIHttpHandle &req) {
    proto_ff::Proto_Web_ModifyLiuShui data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0) {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_ModifyLiuShui_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleModifySetBan(uint32_t serverType, const NFIHttpHandle &req) {
    proto_ff::Proto_Web_SetBan data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_SetBan_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleModifySetTransfer(uint32_t serverType, const NFIHttpHandle &req) {
    proto_ff::Proto_Web_SetTransfer data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_SetTransfer_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleZhuangZhangRecharge(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ZhuangZhang data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.amount() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("金币必须不等于0");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ZhuanZhang_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleSendUserMail(uint32_t, const NFIHttpHandle &req) {
    proto_ff::Proto_Web_SendUserMail data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_SendUserMail_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleGiveMoney(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_GiveMoney data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("user_id is not right");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.amount() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("金币必须不等于0");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_GiveMoney_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleSetUserWhiteBlackList(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetWhiteBlackReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("玩家ID错误");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.start_time() >= data.end_time())
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("结束时间必须大于开始时间");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.opt_mark() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("输盈最大总额必须大于0");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.rate_mark() <= 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("输盈概率必须大于0");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.max_win_jetton() <= 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("单次最大赢必须大于0");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.roster_type() == proto_ff::WHITE_BLACK_ROSTER_TYPE_BLACK &&  data.control_level() >= 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("黑名单控制等级必须是黑-等级");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.roster_type() == proto_ff::WHITE_BLACK_ROSTER_TYPE_WHITE &&  data.control_level() <= 0) {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("白名单控制等级必须是白-等级");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_SetWhiteBlack_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::DeleteSetUserWhiteBlackList(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_DeleteWhiteBlackReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_DeleteWhiteBlack_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::HandleSetGMCtrlGiveData(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetGMCtrlGiveDataReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    if (data.user_id() == 0)
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("玩家ID错误");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    if (data.start_time() >= data.end_time())
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("结束时间必须大于开始时间");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_SetGMCtrlGiveData_REQ, data);
    return true;
}

bool NFCWebUserManagerModule::DeleteGMCtrlGiveData(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_DeleteGMCtrlGiveDataReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSnsServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToSns_DeleteGMCtrlGiveData_REQ, data);
    return true;
}

//清理奖池
bool NFCWebUserManagerModule::ClearJiangChi(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ClearJiangChiReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    const ::proto_ff::Web_ModifyDbData& modify = data.modify_db();

    if (data.game_id() == 0 || data.room_id() == 0 || modify.db_name().empty()
        || modify.tb_name().empty() || modify.db_field_key_size() != modify.db_field_value_size()
        || modify.db_cond_key_size() != modify.db_cond_value_size())
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("gameid error/roomid error");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToWorldServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToWorld_ClearJiangChi_Req, data);
    return true;
}

//配置奖池
bool NFCWebUserManagerModule::SetJiangChi(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetJiangChiReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    const ::proto_ff::Web_ModifyDbData& modify = data.modify_db();

    if (data.game_id() == 0 || data.room_id() == 0 || modify.db_name().empty()
        || modify.tb_name().empty() || modify.db_field_key_size() != modify.db_field_value_size()
        || modify.db_cond_key_size() != modify.db_cond_value_size())
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("gameid error/roomid error");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToWorldServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToWorld_SetJiangChi_Req, data);
    return true;
}

bool NFCWebUserManagerModule::SetRoomStatus(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_SetRoomStatusReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    const ::proto_ff::Web_ModifyDbData& modify = data.modify_db();

    if (data.game_id() == 0 || data.room_id() == 0 || modify.db_name().empty()
        || modify.tb_name().empty() || modify.db_field_key_size() != modify.db_field_value_size()
        || modify.db_cond_key_size() != modify.db_cond_value_size())
    {
        proto_ff::Proto_Web_CommonRspNotify rspNotify;
        rspNotify.set_result(-1);
        rspNotify.set_msg("gameid error/roomid error");

        std::string json;
        NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

        NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
        return true;
    }

    NFMessageMgr::Instance()->SendMsgToWorldServer(NF_ST_WEB_SERVER, proto_ff::NF_WebToWorld_SetRoomStatus_Req, data);
    return true;
}

bool NFCWebUserManagerModule::AddRedemCode(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_AddTedeemCodeReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    for(int i = 0; i < (int)data.count(); i++)
    {
        std::string string = NFRandomString(18);
        NFStringUtility::ToUpper(&string);

        proto_ff::tbRedeemCode code;
        code.set_id(string);
        code.set_gold(data.gold());
        code.set_code_name(data.code_name());
        code.set_create_time(NFTime::Now().UnixSec());
        code.set_state(0);
        code.set_user_id(0);
        code.set_use_time(0);

        NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_WEB_SERVER,
                                                         proto_ff::E_STORESVR_C2S_INSERT, proto_ff::E_TABLE_NONE, NF_DEFAULT_MYSQL_DB_NAME, "tbRedeemCode", code,
                                                         0);
    }

    proto_ff::Proto_Web_CommonRspNotify rspNotify;
    rspNotify.set_result(0);

    std::string json;
    NFProtobufCommon::ProtoMessageToJson(rspNotify, &json);

    NFMessageMgr::Instance()->ResponseHttpMsg(NF_ST_WEB_SERVER, req.GetRequestId(), json, NFWebStatus::WEB_OK);
    return true;
}

bool NFCWebUserManagerModule::ModifyShowUserid(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyShowUserIdReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyShowUserId_Req, data);
    return true;
}

bool NFCWebUserManagerModule::ModifyNickName(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyNickNameReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyNickName_Req, data);
    return true;
}

bool NFCWebUserManagerModule::ModifyVipLevel(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyVipLevelReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyVipLevel_Req, data);
    return true;
}

bool NFCWebUserManagerModule::ModifyAccountPassword(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyAccountPasswordReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyAccountPassword_Req, data);
    return true;
}

bool NFCWebUserManagerModule::ModifyBankPassword(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyBankPasswordReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyBankPassword_Req, data);
    return true;
}

bool NFCWebUserManagerModule::VipRecharge(uint32_t, const NFIHttpHandle &req)
{
    proto_ff::Proto_Web_ModifyVipRechargeReq data;
    WEB_MSG_PROCESS_WITH_PRINTF(data, req);

    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_WEB_SERVER, data.user_id(), proto_ff::NF_WebToLogic_ModifyVipRecharge_Req, data);
    return true;
}