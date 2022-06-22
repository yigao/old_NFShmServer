// -------------------------------------------------------------------------
//    @FileName         :    NFSnsWebHandleTrans.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSnsWebHandleTrans.cpp
//
// -------------------------------------------------------------------------

#include "NFSnsWebHandleTrans.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleUtil.h"
#include "NFComm/NFMessageDefine/proto_svr_web.pb.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFSnsWebHandleTrans, EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID, NFTransSnsBase)

NFSnsWebHandleTrans::NFSnsWebHandleTrans()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    }
    else {
        ResumeInit();
    }
}

NFSnsWebHandleTrans::~NFSnsWebHandleTrans()
{

}

int NFSnsWebHandleTrans::CreateInit()
{
    m_requestId = 0;
    m_userId = 0;
    m_cmd = 0;
    m_BaoDi = 0;
    m_taxBaoDi = 0;
    m_agentId = 0;
    m_liuShui = 0;
    m_tmpAgentId = 0;
    m_countAgentId = 0;
    Init();
    return 0;
}

int NFSnsWebHandleTrans::ResumeInit()
{
    return 0;
}

int NFSnsWebHandleTrans::InitThisTrans(uint64_t userId, uint64_t requestId, uint32_t cmd)
{
    m_userId = userId;
    m_requestId = requestId;
    m_cmd = cmd;
    return 0;
}

int NFSnsWebHandleTrans::QueryRole_CallBack(tagQueryRole &query)
{
    NFSnsUserSimple*  pUserSimple = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(m_userId, false);
    CHECK_NULL(pUserSimple);
    switch (m_cmd)
    {
        case proto_ff::NF_WebToSns_SetBaoDi_REQ:
        {
            pUserSimple->m_userData.getrate = m_BaoDi;
            pUserSimple->MarkDirty();
            pUserSimple->SaveToDB(true);
            NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);
            SetFinished(0);
            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_SetTaxBaoDi_REQ:
        {
            pUserSimple->m_userData.tax_getrate = m_taxBaoDi;
            pUserSimple->MarkDirty();
            pUserSimple->SaveToDB(true);
            NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);
            SetFinished(0);
            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_ModifyAgent_REQ:
        {
            if (m_agentId == 0)
            {
                pUserSimple->m_userData.agentid = m_agentId;
                pUserSimple->MarkDirty();
                pUserSimple->SaveToDB(true);
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                proto_ff::Proto_NotifyChangeAgent notify;
                notify.set_user_id(m_userId);
                notify.set_agent_id(m_agentId);
                NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);
                SetFinished(0);
                return 0;
            }

            NFSnsUserSimple*  pAgentUserSimple = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(m_agentId, false);
            if (!pAgentUserSimple)
            {
                return -1;
            }

            if (pUserSimple->m_userData.agentid == m_agentId)
            {
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);
                SetFinished(0);
                return 0;
            }
            else if (pUserSimple->m_userData.agentid == 0)
            {
                if (pAgentUserSimple->m_userData.agentid == 0)
                {
                    pUserSimple->m_userData.agentid = m_agentId;
                    pUserSimple->MarkDirty();
                    pUserSimple->SaveToDB(true);
                    NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                    proto_ff::Proto_NotifyChangeAgent notify;
                    notify.set_user_id(m_userId);
                    notify.set_agent_id(m_agentId);
                    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);
                    SetFinished(0);
                    return 0;
                }
                else
                {
                    if (pAgentUserSimple->m_userData.agentid != m_userId)
                    {
                        m_tmpAgentId = pAgentUserSimple->m_userData.agentid;
                        CheckAgentQuery();
                    }
                    else
                    {
                        return -1;
                    }
                }

                return 0;
            }
            else
            {
                if (pAgentUserSimple->m_userData.agentid == 0)
                {
                    pUserSimple->m_userData.agentid = m_agentId;
                    pUserSimple->MarkDirty();
                    pUserSimple->SaveToDB(true);
                    NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                    proto_ff::Proto_NotifyChangeAgent notify;
                    notify.set_user_id(m_userId);
                    notify.set_agent_id(m_agentId);
                    NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);
                    SetFinished(0);
                    return 0;
                }
                else
                {
                    if (pAgentUserSimple->m_userData.agentid != m_userId)
                    {
                        m_tmpAgentId = pAgentUserSimple->m_userData.agentid;
                        CheckAgentQuery();
                    }
                    else
                    {
                        return proto_ff::ERR_CODE_USER_AGENT_DEAD_CYCLE;
                    }
                }

                return 0;
            }


            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_ModifyLiuShui_REQ:
        {
            pUserSimple->m_userData.ach_all = m_liuShui;
            pUserSimple->MarkDirty();
            pUserSimple->SaveToDB(true);
            NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

            proto_ff::Proto_NotifyChangeAgent notify;
            notify.set_user_id(m_userId);
            notify.set_agent_id(m_agentId);
            NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);

            SetFinished(0);
            return 0;
        }
            break;
        case proto_ff::NF_SERVER_CMD_CheckAgent_REQ:
        {
            NFSnsUserSimple*  pAgentUserSimple = NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(m_tmpAgentId, false);
            if (!pAgentUserSimple)
            {
                pUserSimple->m_userData.agentid = m_agentId;
                pUserSimple->MarkDirty();
                pUserSimple->SaveToDB(true);
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                proto_ff::Proto_NotifyChangeAgent notify;
                notify.set_user_id(m_userId);
                notify.set_agent_id(m_agentId);
                NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);

                SetFinished(0);
                return 0;
            }

            if (pAgentUserSimple->m_userData.agentid == 0)
            {
                pUserSimple->m_userData.agentid = m_agentId;
                pUserSimple->MarkDirty();
                pUserSimple->SaveToDB(true);
                NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                proto_ff::Proto_NotifyChangeAgent notify;
                notify.set_user_id(m_userId);
                notify.set_agent_id(m_agentId);
                NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);

                SetFinished(0);
                return 0;
            }
            else
            {
                if (pAgentUserSimple->m_userData.agentid != m_userId)
                {
                    if (m_countAgentId >= 10)
                    {
                        pUserSimple->m_userData.agentid = m_agentId;
                        pUserSimple->MarkDirty();
                        pUserSimple->SaveToDB(true);
                        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, 0);

                        proto_ff::Proto_NotifyChangeAgent notify;
                        notify.set_user_id(m_userId);
                        notify.set_agent_id(m_agentId);
                        NFMessageMgr::Instance()->SendMsgToSuitLogicServer(NF_ST_SNS_SERVER, pUserSimple->GetUserId(), proto_ff::NF_SNSTLOGIC_CHANGE_AGENT_NOTIFY, notify);

                        SetFinished(0);
                        return 0;
                    }

                    m_tmpAgentId = pAgentUserSimple->m_userData.agentid;
                    CheckAgentQuery();
                    return 0;
                }
                else
                {
                    return proto_ff::ERR_CODE_USER_AGENT_DEAD_CYCLE;
                }
            }

            return 0;
        }
        break;
        default:
            return -1;
            break;
    }
    return -1;
}

int NFSnsWebHandleTrans::OnTransFinished(int iRunLogicRetCode)
{
    if (iRunLogicRetCode)
    {
        NFMessageMgr::Instance()->SendMsgToWebServer(NF_ST_SNS_SERVER, m_requestId, iRunLogicRetCode);
        return -1;
    }
    return 0;
}

int NFSnsWebHandleTrans::DoQuery()
{
    QueryRole(m_userId);
    return 0;
}

int NFSnsWebHandleTrans::DoAgentQuery()
{
    m_query.Add(m_userId);
    if (m_agentId > 0)
    {
        m_query.Add(m_agentId);
    }
    QueryRole();
    return 0;
}

int NFSnsWebHandleTrans::CheckAgentQuery()
{
    m_cmd = proto_ff::NF_SERVER_CMD_CheckAgent_REQ;
    memset(&m_query, 0, sizeof(m_query));
    m_query.Add(m_tmpAgentId);
    m_countAgentId++;
    QueryRole();
    return 0;
}

int NFSnsWebHandleTrans::HandleCSMsgReq(const google::protobuf::Message *pCSMsgReq) {
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- begin --");
    switch (m_cmd)
    {
        case proto_ff::NF_WebToSns_SetBaoDi_REQ:
        {
            const proto_ff::Proto_Web_SetBaoDi *pLoginReq = dynamic_cast<const proto_ff::Proto_Web_SetBaoDi *>(pCSMsgReq);
            CHECK_EXPR(pLoginReq, -1, "pLoginReq = NULL");

            m_BaoDi = pLoginReq->new_baodi();

            DoQuery();
            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_SetTaxBaoDi_REQ:
        {
            const proto_ff::Proto_Web_SetTaxBaoDi *pLoginReq = dynamic_cast<const proto_ff::Proto_Web_SetTaxBaoDi *>(pCSMsgReq);
            CHECK_EXPR(pLoginReq, -1, "pLoginReq = NULL");

            m_taxBaoDi = pLoginReq->new_tax_baodi();
            DoQuery();
            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_ModifyAgent_REQ:
        {
            const proto_ff::Proto_Web_ModifyAgent *pLoginReq = dynamic_cast<const proto_ff::Proto_Web_ModifyAgent *>(pCSMsgReq);
            CHECK_EXPR(pLoginReq, -1, "pLoginReq = NULL");

            m_agentId = pLoginReq->new_agent_id();

            if (m_agentId == m_userId)
            {
                return -1;
            }

            DoAgentQuery();
            return 0;
        }
            break;
        case proto_ff::NF_WebToSns_ModifyLiuShui_REQ:
        {
            const proto_ff::Proto_Web_ModifyLiuShui *pLoginReq = dynamic_cast<const proto_ff::Proto_Web_ModifyLiuShui *>(pCSMsgReq);
            CHECK_EXPR(pLoginReq, -1, "pLoginReq = NULL");

            m_liuShui = pLoginReq->liu_shui();
            DoQuery();
            return 0;
        }
            break;
        default:
            return -1;
            break;
    }
    NFLogTrace(NF_LOG_LOGIC_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleTrans::HandleGetRoleRes(int iRunLogicRetCode, uint64_t roleID) {
    ++m_query.queryed_num;
    if (iRunLogicRetCode && iRunLogicRetCode != proto_ff::ERR_CODE_PLAYER_NOT_EXIST) {
        NFLogError(NF_LOG_SYSTEMLOG, roleID, "get sns role simple info err {} {}", roleID, iRunLogicRetCode);
    }

    if (m_query.query_role.GetSize() <= m_query.queryed_num) {
        int iRetCode = QueryRole_CallBack(m_query);
        if (iRetCode)
        {
            SetFinished(iRetCode);
        }
    }

    return 0;
}

int NFSnsWebHandleTrans::QueryRole() {
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- begin --");
    for (int i = 0; i < m_query.query_role.GetSize(); i++) {
        if (m_query.query_role[i] == 0) {
            ++m_query.queryed_num;
            continue;
        }

        if (NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpe(m_query.query_role[i], false)) {
            m_query.queryed_num++;
        } else {
            NFSnsUserSimpleUtil::GetInstance()->GetRoleSimpleInfo(m_query.query_role[i], GetGlobalID(),
                                                                  m_dwKeepAliveTime);
        }
    }

    if (m_query.queryed_num >= m_query.query_role.GetSize()) {
        int iRetCode = QueryRole_CallBack(m_query);
        if (iRetCode)
        {
            SetFinished(iRetCode);
        }
    }

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFSnsWebHandleTrans::QueryRole(tagQueryRole &query) {
    m_query = query;
    return QueryRole();
}

int NFSnsWebHandleTrans::QueryRole(uint64_t roleID) {
    m_query.Add(roleID);
    return QueryRole();
}