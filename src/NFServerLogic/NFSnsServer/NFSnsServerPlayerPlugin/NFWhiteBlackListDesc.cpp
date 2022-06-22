// -------------------------------------------------------------------------
//    @FileName         :    NFWhiteBlackListDesc.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFWhiteBlackListDesc.cpp
//
// -------------------------------------------------------------------------

#include "NFWhiteBlackListDesc.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFSnprintf.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include <vector>

IMPLEMENT_IDCREATE_WITHTYPE(NFWhiteBlackListDesc, EOT_WHILE_BLACK_LIST_DESC_ID, NFShmObj)

NFWhiteBlackListDesc::NFWhiteBlackListDesc()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode())
    {
        CreateInit();
    }
    else {
        ResumeInit();
    }
}

NFWhiteBlackListDesc::~NFWhiteBlackListDesc()
{
    if (m_secTimer != INVALID_ID)
    {
        DeleteTimer(m_secTimer);
        m_secTimer = INVALID_ID;
    }
}

int NFWhiteBlackListDesc::CreateInit()
{
    m_maxId = 0;
    m_secTimer = INVALID_ID;
    Initialize();
    return 0;
}

int NFWhiteBlackListDesc::ResumeInit()
{
    return 0;
}

bool compareWhiteBlack(const proto_ff_s::tbGameUserManagerData_s& a, const proto_ff_s::tbGameUserManagerData_s& b)
{
    if (a.user_id*1000000 + a.game_id*100 + a.room_id < b.user_id*1000000 + b.game_id*100 + b.room_id)
    {
        return true;
    }

    return false;
}

int NFWhiteBlackListDesc::Load(NFResDB *pDB)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");
    CHECK_EXPR(pDB != NULL, -1, "pDB == NULL");

    proto_ff::Sheet_tbGameUserManagerData table;
    NFResTable* pResTable = pDB->GetTable(GetFileName());
    CHECK_EXPR(pResTable != NULL, -1, "pTable == NULL, GetTable:{} Error", GetFileName());
    int iRet = pResTable->FindAllRecord(GetDBName(), &table);
    CHECK_EXPR(iRet == 0, -1, "FindAllRecord Error:{}", GetFileName());

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "{}", table.DebugString());

    Initialize();
    m_maxId = 0;

    if ((table.tbgameusermanagerdata_list_size() < 0) || (table.tbgameusermanagerdata_list_size() > (int)(m_astDesc.GetMaxSize())))
    {
        NFLogError(NF_LOG_SNS_SERVER_PLUGIN, 0, "Invalid TotalNum:{}", table.tbgameusermanagerdata_list_size());
        return -2;
    }

    m_astDesc.SetSize(table.tbgameusermanagerdata_list_size());
    for (int i = 0; i < table.tbgameusermanagerdata_list_size(); i++)
    {
        const proto_ff::tbGameUserManagerData& desc = table.tbgameusermanagerdata_list(i);
        proto_ff_s::tbGameUserManagerData_s::read_from_pbmsg(desc, m_astDesc[i]);
        if (m_astDesc[i].id > m_maxId)
        {
            m_maxId = m_astDesc[i].id;
        }
    }

    m_astDesc.Sort(compareWhiteBlack);

    if (m_secTimer == INVALID_ID)
    {
        m_secTimer = SetTimer(60000, 0, 0, 0, 0, 0);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "load {}, num={}", iRet, table.tbgameusermanagerdata_list_size());
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");
    return 0;
}

int NFWhiteBlackListDesc::CheckWhenAllDataLoaded()
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");

    return 0;
}

proto_ff_s::tbGameUserManagerData_s* NFWhiteBlackListDesc::GetDescByID(uint64_t ID)
{
    for(int i = 0; i < m_astDesc.GetSize(); i++)
    {
        if (m_astDesc[i].id == ID)
        {
            return &m_astDesc[i];
        }
    }
    return NULL;
}

proto_ff_s::tbGameUserManagerData_s* NFWhiteBlackListDesc::GetDesc(uint64_t userId, uint32_t gameId, uint32_t roomId)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");
    proto_ff_s::tbGameUserManagerData_s desc;
    desc.user_id = userId;
    desc.game_id = gameId;
    desc.room_id = roomId;

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");
    return m_astDesc.BinarySearch(desc, compareWhiteBlack);
}

proto_ff_s::tbGameUserManagerData_s* NFWhiteBlackListDesc::GetDesc(const proto_ff_s::tbGameUserManagerData_s& desc)
{
    return m_astDesc.BinarySearch(desc, compareWhiteBlack);
}

proto_ff_s::tbGameUserManagerData_s* NFWhiteBlackListDesc::InsertDesc(const proto_ff_s::tbGameUserManagerData_s& desc)
{
    auto pDesc = GetDesc(desc.user_id, desc.game_id, desc.room_id);
    CHECK_EXPR(!pDesc, NULL, "while black list exist, userId:{} gameId:{} roomId:{}", desc.user_id, desc.game_id, desc.room_id);
    CHECK_EXPR(!m_astDesc.IsFull(), NULL, "while black list full, userId:{} gameId:{} roomId:{}", desc.user_id, desc.game_id, desc.room_id);

    pDesc = m_astDesc.BinaryInsert(desc, compareWhiteBlack);
    if (pDesc)
    {
        if (pDesc->id == 0)
        {
            m_maxId++;
            pDesc->id = m_maxId;
        }
        InsertDescStore(*pDesc);
    }
    return pDesc;
}

proto_ff_s::tbGameUserManagerData_s* NFWhiteBlackListDesc::InsertDesc(const proto_ff::tbGameUserManagerData& protoDesc)
{
    proto_ff_s::tbGameUserManagerData_s desc;
    proto_ff_s::tbGameUserManagerData_s::read_from_pbmsg(protoDesc, desc);
    return InsertDesc(desc);
}

int32_t NFWhiteBlackListDesc::DeleteDesc(const proto_ff_s::tbGameUserManagerData_s& desc)
{
    auto pDesc = GetDesc(desc.user_id, desc.game_id, desc.room_id);
    CHECK_EXPR(pDesc, -1, "while black list not exist, userId:{} gameId:{} roomId:{}", desc.user_id, desc.game_id, desc.room_id);

    DeleteDescStore(*pDesc);

    return m_astDesc.BinaryDelete(*pDesc, compareWhiteBlack);
}

int32_t NFWhiteBlackListDesc::DeleteDesc(uint64_t userId, uint32_t gameId, uint32_t roomId)
{
    auto pDesc = GetDesc(userId, gameId, roomId);
    CHECK_EXPR(pDesc, -1, "while black list not exist, userId:{} gameId:{} roomId:{}", userId, gameId, roomId);

    DeleteDescStore(*pDesc);

    return m_astDesc.BinaryDelete(*pDesc, compareWhiteBlack);
}

void NFWhiteBlackListDesc::OnTimer(int timeId, int callcount)
{
    NFIDescStore::OnTimer(timeId, callcount);
    uint64_t now = NFTime::Now().UnixSec();
    if (m_secTimer == timeId)
    {
        std::vector<proto_ff_s::tbGameUserManagerData_s*> vec;
        for(int i = 0; i < (int)m_astDesc.GetSize(); i++)
        {
            if (m_astDesc[i].state == proto_ff::WHITE_BLACK_STATE_NONE)
            {
                if (now >= m_astDesc[i].start_time && now <= m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::WHITE_BLACK_STATE_USEING;
                    m_astDesc[i].MarkDirty();

                    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(m_astDesc[i].user_id);
                    if (pUser)
                    {
                        if (pUser->IsGaming())
                        {
                            proto_ff_s::tbGameUserManagerData_s* pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), pUser->GetRoomId());
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }

                            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), 0);
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }

                            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), 0, 0);
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }
                        }
                    }
                }

                if (now > m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::WHITE_BLACK_STATE_TIMEOUT;
                    m_astDesc[i].MarkDirty();
                    vec.push_back(&m_astDesc[i]);
                }
            }
            else if (m_astDesc[i].state == proto_ff::WHITE_BLACK_STATE_USEING)
            {
                if (now > m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::WHITE_BLACK_STATE_TIMEOUT;
                    m_astDesc[i].MarkDirty();
                    vec.push_back(&m_astDesc[i]);

                    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(m_astDesc[i].user_id);
                    if (pUser)
                    {
                        if (pUser->IsGaming())
                        {
                            proto_ff::Proto_SnsTGame_SetUserManagerInfo deleteMsg;
                            deleteMsg.set_player_id(pUser->GetUserID());
                            proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(m_astDesc[i], *deleteMsg.mutable_user_manager_data());
                            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, deleteMsg);

                            proto_ff_s::tbGameUserManagerData_s* pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), pUser->GetRoomId());
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }

                            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId(), 0);
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }

                            pOtherInfo = NFWhiteBlackListDesc::Instance()->GetDesc(pUser->GetUserID(), 0, 0);
                            if (pOtherInfo && pOtherInfo->state == proto_ff::WHITE_BLACK_STATE_USEING)
                            {
                                proto_ff::Proto_SnsTGame_SetUserManagerInfo gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGameUserManagerData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_user_manager_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_USER_MANAGER_INFO, gameMsg);
                            }
                        }
                    }
                }
            }
            else if (m_astDesc[i].state == proto_ff::WHITE_BLACK_STATE_TIMEOUT)
            {
                vec.push_back(&m_astDesc[i]);
            }
            else if (m_astDesc[i].state == proto_ff::WHITE_BLACK_STATE_FINISH)
            {
                vec.push_back(&m_astDesc[i]);
            }
        }

        for(int i = 0; i < (int)vec.size(); i++)
        {
            proto_ff_s::tbGameUserManagerData_s* pDesc = vec[i];
            if (pDesc)
            {
                DeleteDesc(*vec[i]);
            }
        }
    }
}