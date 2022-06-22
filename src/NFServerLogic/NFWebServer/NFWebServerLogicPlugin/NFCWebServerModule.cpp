﻿// -------------------------------------------------------------------------
//    @FileName         :    NFCWebServerModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCWebServerModule.cpp
//
// -------------------------------------------------------------------------

#include "NFCWebServerModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"
#include "NFServer/NFCommHead/NFICommLogicModule.h"
#include "NFComm/NFPluginModule/NFIMonitorModule.h"
#include "NFComm/NFMessageDefine/proto_svr_common.pb.h"
#include "NFComm/NFPluginModule/NFIAsyMysqlModule.h"
#include "NFComm/NFPluginModule/NFINamingModule.h"
#include "NFComm/NFMessageDefine/proto_event.pb.h"

#define WEB_SERVER_CONNECT_MASTER_SERVER "WebServer Connect MasterServer"
#define WEB_SERVER_CONNECT_ROUTE_AGENT_SERVER "WebServer Connect RouteAgentServer"

NFCWebServerModule::NFCWebServerModule(NFIPluginManager* p):NFIWebServerModule(p)
{
}

NFCWebServerModule::~NFCWebServerModule()
{
}

bool NFCWebServerModule::Awake() {
    FindModule<NFINamingModule>()->InitAppInfo(NF_ST_WEB_SERVER);
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_WEB_SERVER,
                                                       proto_ff::NF_MASTER_SERVER_SEND_OTHERS_TO_SERVER, this,
                                                       &NFCWebServerModule::OnHandleServerReport);

    /////////////////route agent msg///////////////////////////////////////
    NFMessageMgr::Instance()->AddMessageCallBack(NF_ST_WEB_SERVER, proto_ff::NF_SERVER_TO_SERVER_REGISTER_RSP, this, &NFCWebServerModule::OnRegisterRouteAgentRspProcess);


    //注册要完成的服务器启动任务
    m_pPluginManager->RegisterAppTask(NF_ST_WEB_SERVER, APP_INIT_CONNECT_MASTER, WEB_SERVER_CONNECT_MASTER_SERVER);
    m_pPluginManager->RegisterAppTask(NF_ST_WEB_SERVER, APP_INIT_CONNECT_ROUTE_AGENT_SERVER, WEB_SERVER_CONNECT_ROUTE_AGENT_SERVER);


    NFServerConfig *pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    if (pConfig) {
        std::string httpUrl = NF_FORMAT("http://{}:{}", pConfig->mServerIp, pConfig->mHttpPort);
        int ret = NFMessageMgr::Instance()->BindServer(NF_ST_WEB_SERVER, httpUrl, pConfig->mNetThreadNum, pConfig->mMaxConnectNum, PACKET_PARSE_TYPE_INTERNAL);
        if (ret < 0)
        {
            NFLogInfo(NF_LOG_MASTER_SERVER_PLUGIN, 0, "web server listen http failed!, serverId:{}, ip:{}, httpport:{}", pConfig->mBusName, pConfig->mServerIp, pConfig->mHttpPort);
            return false;
        }

        int64_t unlinkId = NFMessageMgr::Instance()->BindServer(NF_ST_WEB_SERVER, pConfig->mUrl, 1, 100, PACKET_PARSE_TYPE_INTERNAL);
        if (unlinkId >= 0)
        {
            /*
                注册客户端事件
            */
            uint64_t loginServerLinkId = (uint64_t) unlinkId;
            NFMessageMgr::Instance()->SetServerLinkId(NF_ST_WEB_SERVER, loginServerLinkId);
            NFMessageMgr::Instance()->AddEventCallBack(NF_ST_WEB_SERVER, loginServerLinkId, this, &NFCWebServerModule::OnWebSocketEvent);
            NFMessageMgr::Instance()->AddOtherCallBack(NF_ST_WEB_SERVER, loginServerLinkId, this, &NFCWebServerModule::OnHandleOtherMessage);
            NFLogInfo(NF_LOG_LOGIN_SERVER_PLUGIN, 0, "web server listen success, serverId:{}, ip:{}, port:{}", pConfig->mBusName, pConfig->mServerIp, pConfig->mServerPort);
        }
        else
        {
            NFLogInfo(NF_LOG_LOGIN_SERVER_PLUGIN, 0, "web server listen failed, serverId:{}, ip:{}, port:{}", pConfig->mBusName, pConfig->mServerIp, pConfig->mServerPort);
            return false;
        }

        if (pConfig->mLinkMode == "bus")
        {
            int iRet = NFMessageMgr::Instance()->ResumeConnect(NF_ST_WEB_SERVER);
            if (iRet == 0)
            {
                std::vector<NF_SHARE_PTR<NFServerData>> vecServer = NFMessageMgr::Instance()->GetAllServer(
                        NF_ST_WEB_SERVER);
                for (int i = 0; i < (int) vecServer.size(); i++)
                {
                    NF_SHARE_PTR<NFServerData> pServerData = vecServer[i];
                    if (pServerData && pServerData->mUnlinkId > 0)
                    {
                        if (pServerData->mServerInfo.server_type() == NF_ST_ROUTE_AGENT_SERVER)
                        {
                            NFMessageMgr::Instance()->AddEventCallBack(NF_ST_WEB_SERVER, pServerData->mUnlinkId, this, &NFCWebServerModule::OnRouteAgentServerSocketEvent);
                            NFMessageMgr::Instance()->AddOtherCallBack(NF_ST_WEB_SERVER, pServerData->mUnlinkId, this, &NFCWebServerModule::OnHandleRouteAgentOtherMessage);

                            auto pRouteServer = NFMessageMgr::Instance()->GetRouteData(NF_ST_WEB_SERVER);
                            pRouteServer->mUnlinkId = pServerData->mUnlinkId;
                            pRouteServer->mServerInfo = pServerData->mServerInfo;
                        }
                    }
                }
            }
        }
    }
    else
    {
        NFLogError(NF_LOG_WEB_SERVER_PLUGIN, 0, "I Can't get the web Server config!");
        return false;
    }

    Subscribe(proto_ff::NF_EVENT_SERVER_DEAD_EVENT, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    return true;
}

int NFCWebServerModule::OnExecute(uint32_t nEventID, uint64_t nSrcID, uint32_t bySrcType, const google::protobuf::Message& message)
{
    if (bySrcType == proto_ff::NF_EVENT_SERVER_TYPE)
    {
        if (nEventID == proto_ff::NF_EVENT_SERVER_DEAD_EVENT)
        {
            SetTimer(10000, 10000, 0);
        }
    }

    Subscribe(proto_ff::NF_EVENT_SERVER_DEAD_EVENT, 0, proto_ff::NF_EVENT_SERVER_TYPE, __FUNCTION__);
    return 0;
}

void NFCWebServerModule::OnTimer(uint32_t nTimerID) {
    if (nTimerID == 10000) {
        NFLogError(NF_LOG_SYSTEMLOG, 0, "kill the exe..................");
        NFSLEEP(1000);
        exit(0);
    }
}

int NFCWebServerModule::ConnectMasterServer(const proto_ff::ServerInfoReport& xData)
{
    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    if (pConfig)
    {
        auto pMasterServerData = NFMessageMgr::Instance()->GetMasterData(NF_ST_WEB_SERVER);
        if (pMasterServerData->mUnlinkId <= 0)
        {
            pMasterServerData->mUnlinkId = NFMessageMgr::Instance()->ConnectServer(NF_ST_WEB_SERVER, xData.url(), PACKET_PARSE_TYPE_INTERNAL);
            NFMessageMgr::Instance()->AddEventCallBack(NF_ST_WEB_SERVER, pMasterServerData->mUnlinkId, this,
                                                       &NFCWebServerModule::OnMasterSocketEvent);
            NFMessageMgr::Instance()->AddOtherCallBack(NF_ST_WEB_SERVER, pMasterServerData->mUnlinkId, this,
                                                       &NFCWebServerModule::OnHandleMasterOtherMessage);
        }

        pMasterServerData->mServerInfo = xData;
    }
    else
    {
        NFLogError(NF_LOG_WEB_SERVER_PLUGIN, 0, "I Can't get the web Server config!");
        return -1;
    }

    return 0;
}

bool NFCWebServerModule::Init()
{
#if NF_PLATFORM == NF_PLATFORM_WIN
	proto_ff::ServerInfoReport masterData = FindModule<NFINamingModule>()->GetDefaultMasterInfo();
	int32_t ret = ConnectMasterServer(masterData);
	CHECK_EXPR(ret == 0, false, "ConnectMasterServer Failed, url:{}", masterData.DebugString());
#endif

    FindModule<NFINamingModule>()->WatchTcpUrls(NF_ST_WEB_SERVER, NF_ST_MASTER_SERVER, [this](const string &name, const proto_ff::ServerInfoReport& xData, int32_t errCode){
        if (errCode != 0)
        {
            NFLogError(NF_LOG_SYSTEMLOG, 0, "WebServer Watch, MasterServer Dump, errCode:{} name:{} serverInfo:{}", errCode, name, xData.DebugString());

            return;
        }
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "WebServer Watch MasterServer name:{} serverInfo:{}", name, xData.DebugString());

        int32_t ret = ConnectMasterServer(xData);
        CHECK_EXPR(ret == 0, , "ConnectMasterServer Failed, url:{}", xData.DebugString());
    });

    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    NF_ASSERT(pConfig);

    if (pConfig->mLinkMode == "bus")
    {
        FindModule<NFINamingModule>()->WatchBusUrls(NF_ST_WEB_SERVER, NF_ST_ROUTE_AGENT_SERVER, [this](const string &name, const proto_ff::ServerInfoReport& xData, int32_t errCode){
            if (errCode != 0)
            {
                NFLogError(NF_LOG_SYSTEMLOG, 0, "WebServer Watch, AgentServer Dump, errCode:{} name:{} serverInfo:{}", errCode, name, xData.DebugString());
                return;
            }
            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "WebServer Watch AgentServer name:{} serverInfo:{}", name, xData.DebugString());

            OnHandleRouteAgentReport(xData);
        });
    }
    else
    {
        FindModule<NFINamingModule>()->WatchTcpUrls(NF_ST_WEB_SERVER, NF_ST_ROUTE_AGENT_SERVER, [this](const string &name, const proto_ff::ServerInfoReport& xData, int32_t errCode){
            if (errCode != 0)
            {
                NFLogError(NF_LOG_SYSTEMLOG, 0, "WebServer Watch, AgentServer Dump, errCode:{} name:{} serverInfo:{}", errCode, name, xData.DebugString());
                return;
            }
            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "WebServer Watch AgentServer name:{} serverInfo:{}", name, xData.DebugString());

            OnHandleRouteAgentReport(xData);
        });
    }

    return true;
}

bool NFCWebServerModule::Execute()
{
    ServerReport();
    return true;
}

bool NFCWebServerModule::OnDynamicPlugin()
{
    NFMessageMgr::Instance()->CloseAllLink(NF_ST_WEB_SERVER);
    return true;
}

/*
	处理Master服务器链接事件
*/
int NFCWebServerModule::OnMasterSocketEvent(eMsgType nEvent, uint64_t unLinkId)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");

    if (nEvent == eMsgType_CONNECTED)
    {
        std::string ip = NFMessageMgr::Instance()->GetLinkIp(unLinkId);
        NFLogDebug(NF_LOG_WEB_SERVER_PLUGIN, 0, "web server connect master success!");
        RegisterMasterServer();

        //完成服务器启动任务
        if (!m_pPluginManager->IsInited())
        {
            m_pPluginManager->FinishAppTask(NF_ST_WEB_SERVER, APP_INIT_CONNECT_MASTER);
        }
    }
    else if (nEvent == eMsgType_DISCONNECTED)
    {
        std::string ip = NFMessageMgr::Instance()->GetLinkIp(unLinkId);
        NFLogError(NF_LOG_WEB_SERVER_PLUGIN, 0, "store server disconnect master success");
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

/*
	处理Master服务器未注册协议
*/
int NFCWebServerModule::OnHandleMasterOtherMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    std::string ip = NFMessageMgr::Instance()->GetLinkIp(unLinkId);
    NFLogWarning(NF_LOG_WEB_SERVER_PLUGIN, 0, "master server other message not handled:playerId:{},msgId:{},ip:{}", playerId, nMsgId, ip);
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::RegisterMasterServer()
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    if (pConfig)
    {
        proto_ff::ServerInfoReportList xMsg;
        proto_ff::ServerInfoReport* pData = xMsg.add_server_list();
        pData->set_bus_id(pConfig->mBusId);
        pData->set_bus_name(pConfig->mBusName);
        pData->set_server_type(pConfig->mServerType);
        pData->set_server_name(pConfig->mServerName);

        pData->set_bus_length(pConfig->mBusLength);
        pData->set_link_mode(pConfig->mLinkMode);
        pData->set_url(pConfig->mUrl);
        pData->set_server_ip(pConfig->mServerIp);
        pData->set_server_port(pConfig->mServerPort);
        pData->set_route_svr(pConfig->mRouteAgent);
        pData->set_server_state(proto_ff::EST_NARMAL);

        NFMessageMgr::Instance()->SendMsgToMasterServer(NF_ST_WEB_SERVER, proto_ff::NF_SERVER_TO_SERVER_REGISTER, xMsg);
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::ServerReport()
{
    if (m_pPluginManager->IsLoadAllServer())
    {
        return 0;
    }

    static uint64_t mLastReportTime = m_pPluginManager->GetNowTime();
    if (mLastReportTime + 100000 > m_pPluginManager->GetNowTime())
    {
        return 0;
    }

    mLastReportTime = m_pPluginManager->GetNowTime();

    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    if (pConfig)
    {
        proto_ff::ServerInfoReportList xMsg;
        proto_ff::ServerInfoReport* pData = xMsg.add_server_list();
        pData->set_bus_id(pConfig->mBusId);
        pData->set_bus_name(pConfig->mBusName);
        pData->set_server_type(pConfig->mServerType);
        pData->set_server_name(pConfig->mServerName);

        pData->set_bus_length(pConfig->mBusLength);
        pData->set_link_mode(pConfig->mLinkMode);
        pData->set_url(pConfig->mUrl);
        pData->set_server_ip(pConfig->mServerIp);
        pData->set_server_port(pConfig->mServerPort);
        pData->set_route_svr(pConfig->mRouteAgent);
        pData->set_server_state(proto_ff::EST_NARMAL);

        NFIMonitorModule* pMonitorModule = m_pPluginManager->FindModule<NFIMonitorModule>();
        if (pMonitorModule)
        {
            const NFSystemInfo& systemInfo = pMonitorModule->GetSystemInfo();

            pData->set_system_info(systemInfo.GetOsInfo().mOsDescription);
            pData->set_total_mem(systemInfo.GetMemInfo().mTotalMem);
            pData->set_free_mem(systemInfo.GetMemInfo().mFreeMem);
            pData->set_used_mem(systemInfo.GetMemInfo().mUsedMem);

            pData->set_proc_cpu(systemInfo.GetProcessInfo().mCpuUsed);
            pData->set_proc_mem(systemInfo.GetProcessInfo().mMemUsed);
            pData->set_proc_thread(systemInfo.GetProcessInfo().mThreads);
            pData->set_proc_name(systemInfo.GetProcessInfo().mName);
            pData->set_proc_cwd(systemInfo.GetProcessInfo().mCwd);
            pData->set_proc_pid(systemInfo.GetProcessInfo().mPid);
            pData->set_server_cur_online(systemInfo.GetUserCount());
        }

        if (pData->proc_cpu() > 0 && pData->proc_mem() > 0)
        {
            NFMessageMgr::Instance()->SendMsgToMasterServer(NF_ST_WEB_SERVER, proto_ff::NF_SERVER_TO_MASTER_SERVER_REPORT, xMsg);
        }
    }
    return 0;
}

int NFCWebServerModule::OnHandleServerReport(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");

    proto_ff::ServerInfoReportList xMsg;
    CLIENT_MSG_PROCESS_NO_PRINTF(nMsgId, playerId, msg, nLen, xMsg);


    for (int i = 0; i < xMsg.server_list_size(); ++i)
    {
        const proto_ff::ServerInfoReport& xData = xMsg.server_list(i);
        switch (xData.server_type())
        {
            case NF_SERVER_TYPES::NF_ST_ROUTE_AGENT_SERVER:
            {
                OnHandleRouteAgentReport(xData);
            }
                break;
            default:
                break;
        }
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnHandleRouteAgentReport(const proto_ff::ServerInfoReport& xData)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    CHECK_EXPR(xData.server_type() == NF_ST_ROUTE_AGENT_SERVER, -1, "xData.server_type() == NF_ST_ROUTE_AGENT_SERVER");
    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    CHECK_NULL(pConfig);

    if (!m_pPluginManager->IsLoadAllServer())
    {
        if (pConfig->mRouteAgent != xData.bus_name())
        {
            return 0;
        }
    }

    auto pRouteAgentServerData = NFMessageMgr::Instance()->GetRouteData(NF_ST_WEB_SERVER);
    CHECK_NULL(pRouteAgentServerData);

    if (pRouteAgentServerData->mUnlinkId == 0)
    {
        pRouteAgentServerData->mUnlinkId = NFMessageMgr::Instance()->ConnectServer(NF_ST_WEB_SERVER, xData.url(), PACKET_PARSE_TYPE_INTERNAL);

        NFMessageMgr::Instance()->AddEventCallBack(NF_ST_WEB_SERVER, pRouteAgentServerData->mUnlinkId, this, &NFCWebServerModule::OnRouteAgentServerSocketEvent);
        NFMessageMgr::Instance()->AddOtherCallBack(NF_ST_WEB_SERVER, pRouteAgentServerData->mUnlinkId, this, &NFCWebServerModule::OnHandleRouteAgentOtherMessage);
    }

    pRouteAgentServerData->mServerInfo = xData;
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnRouteAgentServerSocketEvent(eMsgType nEvent, uint64_t unLinkId)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    if (nEvent == eMsgType_CONNECTED)
    {
        NFLogDebug(NF_LOG_WEB_SERVER_PLUGIN, 0, "web server connect route server success!");

        RegisterRouteAgentServer(unLinkId);
    }
    else if (nEvent == eMsgType_DISCONNECTED)
    {
        NFLogError(NF_LOG_WEB_SERVER_PLUGIN, 0, "web server disconnect route server success");
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnHandleRouteAgentOtherMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    NFLogWarning(NF_LOG_WEB_SERVER_PLUGIN, playerId, "msg:{} not handled!", nMsgId);
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::RegisterRouteAgentServer(uint64_t unLinkId)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_WEB_SERVER);
    if (pConfig)
    {
        proto_ff::ServerInfoReportList xMsg;
        proto_ff::ServerInfoReport* pData = xMsg.add_server_list();
        pData->set_bus_id(pConfig->mBusId);
        pData->set_bus_name(pConfig->mBusName);
        pData->set_server_type(pConfig->mServerType);
        pData->set_server_name(pConfig->mServerName);

        pData->set_bus_length(pConfig->mBusLength);
        pData->set_link_mode(pConfig->mLinkMode);
        pData->set_url(pConfig->mUrl);
        pData->set_server_ip(pConfig->mServerIp);
        pData->set_server_port(pConfig->mServerPort);
        pData->set_route_svr(pConfig->mRouteAgent);
        pData->set_server_state(proto_ff::EST_NARMAL);

        NFMessageMgr::Instance()->Send(unLinkId, proto_ff::NF_SERVER_TO_SERVER_REGISTER, xMsg, 0);
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnWebSocketEvent(eMsgType nEvent, uint64_t unLinkId)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    if (nEvent == eMsgType_CONNECTED)
    {

    }
    else if (nEvent == eMsgType_DISCONNECTED)
    {
        OnHandleServerDisconnect(unLinkId);
    }
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnHandleOtherMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    NFLogWarning(NF_LOG_WEB_SERVER_PLUGIN, playerId, "msg:{} not handled!", nMsgId);
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnHandleServerDisconnect(uint64_t unLinkId)
{
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");
    NF_SHARE_PTR<NFServerData> pServerData = NFMessageMgr::Instance()->GetServerByUnlinkId(NF_ST_WEB_SERVER, unLinkId);
    if (pServerData)
    {
        pServerData->mServerInfo.set_server_state(proto_ff::EST_CRASH);
        pServerData->mUnlinkId = 0;

        NFLogError(NF_LOG_WEB_SERVER_PLUGIN, 0, "the server disconnect from web server, serverName:{}, busid:{}, serverIp:{}, serverPort:{}"
        , pServerData->mServerInfo.server_name(), pServerData->mServerInfo.bus_id(), pServerData->mServerInfo.server_ip(), pServerData->mServerInfo.server_port());
    }

    NFMessageMgr::Instance()->DelServerLink(NF_ST_WEB_SERVER, unLinkId);
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}

int NFCWebServerModule::OnRegisterRouteAgentRspProcess(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId,
                                                         const char *msg, uint32_t nLen) {
    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- begin --");

    //完成服务器启动任务
    if (!m_pPluginManager->IsInited())
    {
        m_pPluginManager->FinishAppTask(NF_ST_WEB_SERVER, APP_INIT_CONNECT_ROUTE_AGENT_SERVER);
    }

    FindModule<NFINamingModule>()->RegisterAppInfo(NF_ST_WEB_SERVER);

    NFLogTrace(NF_LOG_WEB_SERVER_PLUGIN, 0, "-- end --");
    return 0;
}
