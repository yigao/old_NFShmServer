// -------------------------------------------------------------------------
//    @FileName         :    NFGMCtrlGiveDataDesc.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGMCtrlGiveDataDesc.cpp
//
// -------------------------------------------------------------------------

#include "NFGMCtrlGiveDataDesc.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFSnprintf.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_game.pb.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include <vector>

IMPLEMENT_IDCREATE_WITHTYPE(NFGMCtrlGiveDataDesc, EOT_GM_CTRL_GIVE_DATA_DESC_ID, NFShmObj)

NFGMCtrlGiveDataDesc::NFGMCtrlGiveDataDesc()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode())
    {
        CreateInit();
    }
    else {
        ResumeInit();
    }
}

NFGMCtrlGiveDataDesc::~NFGMCtrlGiveDataDesc()
{
    if (m_secTimer != INVALID_ID)
    {
        DeleteTimer(m_secTimer);
        m_secTimer = INVALID_ID;
    }
}

int NFGMCtrlGiveDataDesc::CreateInit()
{
    m_maxId = 0;
    m_secTimer = INVALID_ID;
    Initialize();
    return 0;
}

int NFGMCtrlGiveDataDesc::ResumeInit()
{
    return 0;
}

bool compareGmCtrlData(const proto_ff_s::tbGmCtrlGiveCtrlData_s& a, const proto_ff_s::tbGmCtrlGiveCtrlData_s& b)
{
    if (a.user_id*10000 + a.game_id < b.user_id*10000 + b.game_id)
    {
        return true;
    }

    return false;
}

int NFGMCtrlGiveDataDesc::Load(NFResDB *pDB)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");
    CHECK_EXPR(pDB != NULL, -1, "pDB == NULL");

    proto_ff::Sheet_tbGmCtrlGiveCtrlData table;
    NFResTable* pResTable = pDB->GetTable(GetFileName());
    CHECK_EXPR(pResTable != NULL, -1, "pTable == NULL, GetTable:{} Error", GetFileName());
    int iRet = pResTable->FindAllRecord(GetDBName(), &table);
    CHECK_EXPR(iRet == 0, -1, "FindAllRecord Error:{}", GetFileName());

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "{}", table.DebugString());

    Initialize();
    m_maxId = 0;

    if ((table.tbgmctrlgivectrldata_list_size() < 0) || (table.tbgmctrlgivectrldata_list_size() > (int)(m_astDesc.GetMaxSize())))
    {
        NFLogError(NF_LOG_SNS_SERVER_PLUGIN, 0, "Invalid TotalNum:{}", table.tbgmctrlgivectrldata_list_size());
        return -2;
    }

    m_astDesc.SetSize(table.tbgmctrlgivectrldata_list_size());
    for (int i = 0; i < table.tbgmctrlgivectrldata_list_size(); i++)
    {
        const proto_ff::tbGmCtrlGiveCtrlData& desc = table.tbgmctrlgivectrldata_list(i);
        proto_ff_s::tbGmCtrlGiveCtrlData_s::read_from_pbmsg(desc, m_astDesc[i]);
        if (m_astDesc[i].id > m_maxId)
        {
            m_maxId = m_astDesc[i].id;
        }
    }

    m_astDesc.Sort(compareGmCtrlData);

    if (m_secTimer == INVALID_ID)
    {
        m_secTimer = SetTimer(60000, 0, 0, 0, 0, 0);
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "load {}, num={}", iRet, table.tbgmctrlgivectrldata_list_size());
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");
    return 0;
}

int NFGMCtrlGiveDataDesc::CheckWhenAllDataLoaded()
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");

    return 0;
}

proto_ff_s::tbGmCtrlGiveCtrlData_s* NFGMCtrlGiveDataDesc::GetDescByID(uint64_t ID)
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

proto_ff_s::tbGmCtrlGiveCtrlData_s* NFGMCtrlGiveDataDesc::GetDesc(uint64_t userId, uint32_t gameId)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");
    proto_ff_s::tbGmCtrlGiveCtrlData_s desc;
    desc.user_id = userId;
    desc.game_id = gameId;

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--end--");
    return m_astDesc.BinarySearch(desc, compareGmCtrlData);
}

proto_ff_s::tbGmCtrlGiveCtrlData_s* NFGMCtrlGiveDataDesc::GetDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc)
{
    return m_astDesc.BinarySearch(desc, compareGmCtrlData);
}

proto_ff_s::tbGmCtrlGiveCtrlData_s* NFGMCtrlGiveDataDesc::InsertDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc)
{
    auto pDesc = GetDesc(desc.user_id, desc.game_id);
    CHECK_EXPR(!pDesc, NULL, "while black list exist, userId:{} gameId:{}", desc.user_id, desc.game_id);
    CHECK_EXPR(!m_astDesc.IsFull(), NULL, "while black list full, userId:{} gameId:{}", desc.user_id, desc.game_id);

    pDesc = m_astDesc.BinaryInsert(desc, compareGmCtrlData);
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

proto_ff_s::tbGmCtrlGiveCtrlData_s* NFGMCtrlGiveDataDesc::InsertDesc(const proto_ff::tbGmCtrlGiveCtrlData& protoDesc)
{
    proto_ff_s::tbGmCtrlGiveCtrlData_s desc;
    proto_ff_s::tbGmCtrlGiveCtrlData_s::read_from_pbmsg(protoDesc, desc);
    return InsertDesc(desc);
}

int32_t NFGMCtrlGiveDataDesc::DeleteDesc(const proto_ff_s::tbGmCtrlGiveCtrlData_s& desc)
{
    auto pDesc = GetDesc(desc.user_id, desc.game_id);
    CHECK_EXPR(pDesc, -1, "while black list not exist, userId:{} gameId:{}", desc.user_id, desc.game_id);

    DeleteDescStore(*pDesc);

    return m_astDesc.BinaryDelete(*pDesc, compareGmCtrlData);
}

int32_t NFGMCtrlGiveDataDesc::DeleteDesc(uint64_t userId, uint32_t gameId)
{
    auto pDesc = GetDesc(userId, gameId);
    CHECK_EXPR(pDesc, -1, "while black list not exist, userId:{} gameId:{} roomId:{}", userId, gameId);

    DeleteDescStore(*pDesc);

    return m_astDesc.BinaryDelete(*pDesc, compareGmCtrlData);
}

void NFGMCtrlGiveDataDesc::OnTimer(int timeId, int callcount)
{
    NFIDescStore::OnTimer(timeId, callcount);
    uint64_t now = NFTime::Now().UnixSec();
    if (m_secTimer == timeId)
    {
        std::vector<proto_ff_s::tbGmCtrlGiveCtrlData_s*> vec;
        for(int i = 0; i < (int)m_astDesc.GetSize(); i++)
        {
            if (m_astDesc[i].state == proto_ff::GM_CTRL_GIVE_DATA_STATE_NONE)
            {
                if (now >= m_astDesc[i].start_time && now <= m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING;
                    m_astDesc[i].MarkDirty();

                    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(m_astDesc[i].user_id);
                    if (pUser)
                    {
                        if (pUser->IsGaming())
                        {
                            proto_ff_s::tbGmCtrlGiveCtrlData_s* pOtherInfo = NFGMCtrlGiveDataDesc::Instance()->GetDesc(pUser->GetUserID(), pUser->GetGameId());
                            if (pOtherInfo && pOtherInfo->state == proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING)
                            {
                                proto_ff::Proto_SnsTGame_SetGmCtrlGiveData gameMsg;
                                gameMsg.set_player_id(pUser->GetUserID());
                                proto_ff_s::tbGmCtrlGiveCtrlData_s::write_to_pbmsg(*pOtherInfo, *gameMsg.mutable_gm_ctrl_data());
                                NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_GM_CTRL_GIVE_DATA, gameMsg);
                            }
                        }
                    }
                }

                if (now > m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::GM_CTRL_GIVE_DATA_STATE_TIMEOUT;
                    m_astDesc[i].MarkDirty();
                    vec.push_back(&m_astDesc[i]);
                }
            }
            else if (m_astDesc[i].state == proto_ff::GM_CTRL_GIVE_DATA_STATE_WAITING)
            {
                if (now > m_astDesc[i].end_time)
                {
                    m_astDesc[i].state = proto_ff::GM_CTRL_GIVE_DATA_STATE_TIMEOUT;
                    m_astDesc[i].MarkDirty();
                    vec.push_back(&m_astDesc[i]);

                    NFOnlineUser* pUser = NFOnlineUserMgr::Instance()->Find(m_astDesc[i].user_id);
                    if (pUser)
                    {
                        if (pUser->IsGaming())
                        {
                            proto_ff::Proto_SnsTGame_SetGmCtrlGiveData deleteMsg;
                            deleteMsg.set_player_id(pUser->GetUserID());
                            proto_ff_s::tbGmCtrlGiveCtrlData_s::write_to_pbmsg(m_astDesc[i], *deleteMsg.mutable_gm_ctrl_data());
                            NFMessageMgr::Instance()->SendMsgToGameServer(NF_ST_SNS_SERVER, pUser->GetGameBusId(), proto_ff::E_SnsTGame_SET_GM_CTRL_GIVE_DATA, deleteMsg);
                        }
                    }
                }
            }
            else if (m_astDesc[i].state == proto_ff::GM_CTRL_GIVE_DATA_STATE_TIMEOUT)
            {
                vec.push_back(&m_astDesc[i]);
            }
            else if (m_astDesc[i].state == proto_ff::GM_CTRL_GIVE_DATA_STATE_FINISH)
            {
                vec.push_back(&m_astDesc[i]);
            }
        }

        for(int i = 0; i < (int)vec.size(); i++)
        {
            proto_ff_s::tbGmCtrlGiveCtrlData_s* pDesc = vec[i];
            if (pDesc)
            {
                DeleteDesc(*vec[i]);
            }
        }
    }
}