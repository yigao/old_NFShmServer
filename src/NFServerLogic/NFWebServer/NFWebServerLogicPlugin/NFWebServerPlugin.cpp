// -------------------------------------------------------------------------
//    @FileName         :    NFWebServerPlugin.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFWebServerPlugin.cpp
//
// -------------------------------------------------------------------------


#include "NFWebServerPlugin.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFCWebServerModule.h"
#include "NFCWebMessageModule.h"
#include "NFCWebUserManagerModule.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(NFIPluginManager* pm)
{
    CREATE_PLUGIN(pm, NFWebServerPlugin)

};

NF_EXPORT void DllStopPlugin(NFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFWebServerPlugin)
};

#endif


//////////////////////////////////////////////////////////////////////////

int NFWebServerPlugin::GetPluginVersion()
{
    return 0;
}

std::string NFWebServerPlugin::GetPluginName()
{
    return GET_CLASS_NAME(NFWebServerPlugin);
}

void NFWebServerPlugin::Install()
{
    REGISTER_MODULE(m_pPluginManager, NFIWebServerModule, NFCWebServerModule);
    REGISTER_MODULE(m_pPluginManager, NFCWebMessageModule, NFCWebMessageModule);
    REGISTER_MODULE(m_pPluginManager, NFCWebUserManagerModule, NFCWebUserManagerModule);
}

void NFWebServerPlugin::Uninstall()
{
    UNREGISTER_MODULE(m_pPluginManager, NFIWebServerModule, NFCWebServerModule);
    UNREGISTER_MODULE(m_pPluginManager, NFCWebMessageModule, NFCWebMessageModule);
    UNREGISTER_MODULE(m_pPluginManager, NFCWebUserManagerModule, NFCWebUserManagerModule);
}

