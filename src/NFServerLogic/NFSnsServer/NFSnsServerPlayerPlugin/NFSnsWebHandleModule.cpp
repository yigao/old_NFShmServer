// -------------------------------------------------------------------------
//    @FileName         :    NFSnsWebHandleModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSnsWebHandleModule.cpp
//
// -------------------------------------------------------------------------

#include "NFSnsWebHandleModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFComm/NFMessageDefine/proto_common.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_web.pb.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailUtil.h"
#include "NFSnsWebHandleTrans.h"
#include "NFWhiteBlackListDesc.h"
#include "NFGMCtrlGiveDataDesc.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"

NFSnsWebHandleModule::NFSnsWebHandleModule(NFIPluginManager *p) : NFIDynamicModule(p) {

}

NFSnsWebHandleModule::~NFSnsWebHandleModule() {

}

bool NFSnsWebHandleModule::Awake() {
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_SetBaoDi_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandlePlayerSetBaoDi);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_SetTaxBaoDi_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandlePlayerSetTaxBaoDi);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_ModifyAgent_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandlePlayerModifyAgent);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_ModifyLiuShui_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandlePlayerModifyLiuShui);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_SendUserMail_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandleSendUserMail);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_SetWhiteBlack_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandleSetWhiteBlackReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_DeleteWhiteBlack_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandleDeleteWhiteBlackReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_GameTSns_WRITE_BACK_USER_MANAGER_IFNO, this,
                                                 &NFSnsWebHandleModule::OnHandleWriteBackUserManagerInfoReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_SetGMCtrlGiveData_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandleSetGMCtrlGiveDataReq);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::NF_WebToSns_DeleteGMCtrlGiveData_REQ, this,
                                                 &NFSnsWebHandleModule::OnHandleDeleteGMCtrlGiveDataReq);

    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_SNS_SERVER, proto_ff::E_GameTSns_FINISH_GM_CTRL_GIVE_DATA, this,
                                                 &NFSnsWebHandleModule::OnHandleFinishGMCtrlGiveData);
    return true;
}

int NFSnsWebHandleModule::OnHandlePlayerSetBaoDi(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId,
                                                 const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_SetBaoDi xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSnsWebHandleTrans* pTrans = dynamic_cast<NFSnsWebHandleTrans *>(NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "pTrans createobj failed!");
    pTrans->InitThisTrans(xMsg.user_id(), xMsg.request_id(), nMsgId);
    pTrans->ProcessCSMsgReq(&xMsg);
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandlePlayerSetTaxBaoDi(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId,
                                                    const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_SetTaxBaoDi xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSnsWebHandleTrans* pTrans = dynamic_cast<NFSnsWebHandleTrans *>(NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "pTrans createobj failed!");
    pTrans->InitThisTrans(xMsg.user_id(), xMsg.request_id(), nMsgId);
    pTrans->ProcessCSMsgReq(&xMsg);
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandlePlayerModifyAgent(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId,
                                                    const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_ModifyAgent xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSnsWebHandleTrans* pTrans = dynamic_cast<NFSnsWebHandleTrans *>(NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "pTrans createobj failed!");
    pTrans->InitThisTrans(xMsg.user_id(), xMsg.request_id(), nMsgId);
    pTrans->ProcessCSMsgReq(&xMsg);
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int
NFSnsWebHandleModule::OnHandlePlayerModifyLiuShui(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId,
                                                  const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_ModifyLiuShui xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    NFSnsWebHandleTrans* pTrans = dynamic_cast<NFSnsWebHandleTrans *>(NFShmMgr::Instance()->CreateTrans(EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID));
    CHECK_EXPR(pTrans, -1, "pTrans createobj failed!");
    pTrans->InitThisTrans(xMsg.user_id(), xMsg.request_id(), nMsgId);
    pTrans->ProcessCSMsgReq(&xMsg);
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleSendUserMail(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_SendUserMail xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff::tbUserMailDetail tb_role_mail;
    tb_role_mail.set_user_id(xMsg.user_id());
    tb_role_mail.set_send_name(xMsg.send_name());
    tb_role_mail.set_title(xMsg.title());
    tb_role_mail.set_content(xMsg.content());
    NFUserMailUtil::OnCreateMail(tb_role_mail, xMsg.user_id());

    NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleSetWhiteBlackReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_SetWhiteBlackReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    for(int i = 0; i < (int)xMsg.game_list_size(); i++)
    {
        if (xMsg.game_list(i).game_id() == 0 && xMsg.game_list(i).room_id() > 0)
        {
            NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "需要选着具体的游戏，才能选房间");
            return 0;
        }

        if (xMsg.game_list(i).game_id() == 0 && xMsg.game_list(i).room_id() == 0)
        {
            proto_ff_s::tbGameUserManagerData_s* pInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), 0, 0);
            if (pInfo)
            {
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "玩家已经在名单里，请先删除存在的黑白名单");
                return 0;
            }
        }

        if (xMsg.game_list(i).game_id() > 0 && xMsg.game_list(i).room_id() == 0)
        {
            proto_ff_s::tbGameUserManagerData_s* pInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), xMsg.game_list(i).game_id(), 0);
            if (pInfo)
            {
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "玩家已经在名单里，请先删除存在的黑白名单");
                return 0;
            }
        }

        if (xMsg.game_list(i).game_id() > 0 && xMsg.game_list(i).room_id() > 0)
        {
            proto_ff_s::tbGameUserManagerData_s* pInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), xMsg.game_list(i).game_id(), xMsg.game_list(i).room_id());
            if (pInfo)
            {
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "玩家已经在名单里，请先删除存在的黑白名单");
                return 0;
            }
        }
    }

    for(int i = 0; i < (int)xMsg.game_list_size(); i++)
    {
        proto_ff_s::tbGameUserManagerData_s desc;
        desc.id = 0;
        desc.user_id = xMsg.user_id();
        desc.game_id = xMsg.game_list(i).game_id();
        desc.room_id = xMsg.game_list(i).room_id();
        desc.cur_win = 0;
        desc.create_date = NFTime::Now().GetFormatTime();
        desc.roster_type = xMsg.roster_type();
        desc.start_time = xMsg.start_time();
        desc.end_time = xMsg.end_time();
        desc.control_level = xMsg.control_level();
        desc.max_win_jetton = xMsg.max_win_jetton();
        if (desc.roster_type == proto_ff::WHITE_BLACK_ROSTER_TYPE_BLACK)
        {
            desc.opt_mark = -1 * (int64_t)xMsg.opt_mark();
            desc.rate_mark = -1 * xMsg.rate_mark();
        }
        else
        {
            desc.opt_mark = (int64_t)xMsg.opt_mark();
            desc.rate_mark = xMsg.rate_mark();
        }

        desc.state = proto_ff::WHITE_BLACK_STATE_NONE;
        uint64_t now = NFTime::Now().UnixSec();
        if (now >= desc.start_time && now <= desc.end_time)
        {
            desc.state = proto_ff::WHITE_BLACK_STATE_USEING;
        }

        proto_ff_s::tbGameUserManagerData_s* pInfo = NFWhiteBlackListDesc::Instance()->InsertDesc(desc);
        if (!pInfo)
        {
            NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "创建失败");
            return 0;
        }
    }

    NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);

    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(xMsg.user_id());
    if (pUser)
    {
        if (pUser->IsGaming())
        {
            proto_ff_s::tbGameUserManagerData_s* pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), pUser->GetGameId(), pUser->GetRoomId());
            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
            {
                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                gameMsg.set_player_id(xMsg.user_id());
                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                return 0;
            }

            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), pUser->GetGameId(), 0);
            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
            {
                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                gameMsg.set_player_id(xMsg.user_id());
                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                return 0;
            }

            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(xMsg.user_id(), 0, 0);
            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
            {
                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                gameMsg.set_player_id(xMsg.user_id());
                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                return 0;
            }
        }
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleDeleteWhiteBlackReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_DeleteWhiteBlackReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff_s::tbGameUserManagerData_s* pDesc = NFWhiteBlackListDesc::Instance()->GetDescByID(xMsg.whiteblack_id());
    if (pDesc)
    {
        pDesc->state = proto_ff::WHITE_BLACK_STATE_NONE;
        NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(pDesc->user_id);
        if (pUser)
        {
            if (pUser->IsGaming())
            {
                proto_ff::Proto_SnsTGame_SetUserManagerInfo deleteMsg;
                deleteMsg.set_player_id(pUser->GetUserID());
                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pDesc, *deleteMsg.mutable_user_manager_data());
                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, deleteMsg);

                NFWhiteBlackListDesc::Instance()->DeleteDesc(*pDesc);
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);

                proto_ff_s::tbGameUserManagerData_s* pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), pUser->GetRoomId());
                if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                {
                    proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                    gameMsg.set_player_id(pUser->GetUserID());
                    proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                    NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                    return 0;
                }

                pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), 0);
                if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                {
                    proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                    gameMsg.set_player_id(pUser->GetUserID());
                    proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                    NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                    return 0;
                }

                pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), 0, 0);
                if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                {
                    proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                    gameMsg.set_player_id(pUser->GetUserID());
                    proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                    NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                    return 0;
                }

                return 0;
            }
        }

        NFWhiteBlackListDesc::Instance()->DeleteDesc(*pDesc);
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);
    }
    else
    {
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "ID不存在");
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleSetGMCtrlGiveDataReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_SetGMCtrlGiveDataReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff_s::tbGmCtrlGiveCtrlData_s* pExistInfo = NFGMCtrlGiveDataDesc::Instance()->GetDesc(xMsg.user_id(), xMsg.game_id());
    if (pExistInfo)
    {
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "玩家已经有该游戏的赠送，还未消耗完，请先删除");
        return 0;
    }

    proto_ff_s::tbGmCtrlGiveCtrlData_s desc;
    desc.id = 0;
    desc.user_id = xMsg.user_id();
    desc.game_id = xMsg.game_id();
    desc.create_date = NFTime::Now().GetFormatTime();
    desc.control_type = xMsg.control_type();
    desc.start_time = xMsg.start_time();
    desc.end_time = xMsg.end_time();
    desc.jackpot_type = xMsg.jackpot_type();
    desc.jackpot_rate = xMsg.jackpot_rate();
    desc.jackpot_jetton = xMsg.jackpot_jetton();

    desc.state = proto_ff::GM_CTRL_GIVE_DATA_STATE_NONE;
    uint64_t now = NFTime::Now().UnixSec();
    if (now >= desc.start_time && now <= desc.end_time)
    {
        desc.state = proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING;
    }

    proto_ff_s::tbGmCtrlGiveCtrlData_s* pInfo = NFGMCtrlGiveDataDesc::Instance()->InsertDesc(desc);
    if (!pInfo)
    {
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "创建失败");
        return 0;
    }

    NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);

    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(xMsg.user_id());
    if (pUser)
    {
        if (pUser->IsGaming())
        {
            if (pUser->GetGameId() == xMsg.game_id() && pInfo->state == proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING)
            {
                proto_ff::Proto_SnsTGame_SetGmCtrlGiveData gameMsg;
                gameMsg.set_player_id(xMsg.user_id());
                proto_ff_s::tbGmCtrlGiveCtrlData_s::write_to_pbmsg(*pInfo, *gameMsg.mutable_gm_ctrl_data());
                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_GM_CTRL_GIVE_DATA, gameMsg);
                return 0;
            }
        }
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleDeleteGMCtrlGiveDataReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_Web_DeleteGMCtrlGiveDataReq xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff_s::tbGmCtrlGiveCtrlData_s* pDesc = NFGMCtrlGiveDataDesc::Instance()->GetDescByID(xMsg.id());
    if (pDesc)
    {
        pDesc->state = proto_ff::GM_CTRL_GIVE_DATA_STATE_NONE;
        NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(pDesc->user_id);
        if (pUser)
        {
            if (pUser->IsGaming())
            {
                if (pDesc->game_id == pUser->GetGameId())
                {
                    proto_ff::Proto_SnsTGame_SetGmCtrlGiveData deleteMsg;
                    deleteMsg.set_player_id(pUser->GetUserID());
                    proto_ff_s::tbGmCtrlGiveCtrlData_s::write_to_pbmsg(*pDesc, *deleteMsg.mutable_gm_ctrl_data());
                    NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_GM_CTRL_GIVE_DATA, deleteMsg);
                }

                NFGMCtrlGiveDataDesc::Instance()->DeleteDesc(*pDesc);
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);

                return 0;
            }
        }

        NFGMCtrlGiveDataDesc::Instance()->DeleteDesc(*pDesc);
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), 0);
    }
    else
    {
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, xMsg.request_id(), -1, "ID不存在");
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleWriteBackUserManagerInfoReq(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_GameTSns_WriteBackUserManagerInfo xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff_s::tbGameUserManagerData_s userManagerInfo;
    proto_ff_s::tbGameUserManagerData_s::read_from_pbmsg(xMsg.user_manager_data(), userManagerInfo);

    proto_ff_s::tbGameUserManagerData_s* pDesc = NFWhiteBlackListDesc::Instance()->GetDesc(userManagerInfo);
    CHECK_NULL(pDesc);
    CHECK_EXPR(pDesc->id == userManagerInfo.id, 0, "white-black list id:{} not exist.....", userManagerInfo.id);

    memcpy(pDesc, &userManagerInfo, sizeof(userManagerInfo));
    pDesc->MarkDirty();
    if (pDesc->state != proto_ff::WHITE_BLACK_STATE_USEING)
    {
        NFWhiteBlackListDesc::Instance()->DeleteDesc(*pDesc);
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleModule::OnHandleFinishGMCtrlGiveData(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    proto_ff::Proto_GameTSns_FinishGMCtrlGiveData xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    proto_ff_s::tbGmCtrlGiveCtrlData_s userManagerInfo;
    proto_ff_s::tbGmCtrlGiveCtrlData_s::read_from_pbmsg(xMsg.gm_ctrl_data(), userManagerInfo);

    proto_ff_s::tbGmCtrlGiveCtrlData_s* pDesc = NFGMCtrlGiveDataDesc::Instance()->GetDesc(userManagerInfo);
    CHECK_NULL(pDesc);
    CHECK_EXPR(pDesc->id == userManagerInfo.id, 0, "gm_ctrl list id:{} not exist.....", userManagerInfo.id);

    memcpy(pDesc, &userManagerInfo, sizeof(userManagerInfo));
    pDesc->MarkDirty();
    if (pDesc->state != proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING)
    {
        NFGMCtrlGiveDataDesc::Instance()->DeleteDesc(*pDesc);
    }

    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}
