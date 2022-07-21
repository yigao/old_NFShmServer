-- server type
NF_ST_NONE = 0;    		-- NONE
NF_ST_MASTER_SERVER = 1;    	--
NF_ST_LOGIN_SERVER = 2;    	--
NF_ST_WORLD_SERVER = 3;    	--
NF_ST_GAME_SERVER = 4;    		--
NF_ST_PROXY_SERVER = 5;    	--
NF_ST_ROUTE_AGENT_SERVER = 6; --路由代理服务器  负责同一台机子服务器数据之间的转发
NF_ST_ROUTE_SERVER = 7; --路由集群服务器 负责不同机子服务器数据之间的转发
NF_ST_STORE_SERVER = 8; --DB服务器
NF_ST_SNS_SERVER = 9; --SNS服务器
NF_ST_LOGIC_SERVER = 10; --Logic服务器
NF_ST_WEB_SERVER = 11; --Web服务器
NF_ST_MONITOR_SERVER = 12; --Monitor服务器
NF_ST_MAX = 20;    		--

--ProxyServer 网管服务器， 负责与外部的客户端连接, 转发数据
--ServerId = "15.100.5.1" 15是世界服务ID， 范围1-15
-- 100是区服务ID， 范围1-65536
-- 5是服务器类型ID， 必须跟serverType一样 范围1-255
-- 1服务器索引，范围1-255
ProxyServer = {
    ProxyServer_5_1 = {
        ServerName = "ProxyServer_5_1",
        ServerType = 5,
        ServerId = "15.100.5.1",			--对每一个服务器来说都是唯一的， 应用程序需要通过这个ServerId才能知道需要加载的配置是他
        IdleSleepUS = 1000,
        BusLength = 20971520,     --20M共享内存
        MaxConnectNum = 1000000,
        NetThreadNum = 5,
        WorkThreadNum = 1,
        ParseType = 1, --0是内网协议，1是外网协议
        ServerIp = "127.0.0.1",
        ServerPort = 6051,
	    ExternalServerIp = "47.112.97.12",
	    ExternalServerPort = 7051,
        MaxOnlinePlayerNum = 100,
        --NamingHost = "127.0.0.1:2181,127.0.0.1:2182",
        --NamingPath = "99Puke",
        MasterIp = "127.0.0.1",
        MasterPort = 6011,
	};
};
