// -------------------------------------------------------------------------
//    @FileName         :    NFGameServerPlugin.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFGameServerPlugin
//
// -------------------------------------------------------------------------

#include "NFSnsServerPlugin.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFSnsServerModule.h"
#include "NFUserMailModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFTransMailCreate.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUser.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFOnlineUserMgr.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFOnlineModule.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransGetSnsUserSimple.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFSnsUserSimpleUtil.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransSaveSimpleDB.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFUserSimple/NFTransSnsBase.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFOnlineUser/NFTransSnsUserOnline.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFEventLog/NFTransSnsSendEventLog.h"

#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFMailDesc.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFActivityMail.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFMail/NFUserMailCacheInfo.h"

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFRankCommon.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFRankMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRank/NFGetRankTrans.h"
#include "NFSnsWebHandleModule.h"
#include "NFSnsWebHandleTrans.h"
#include "NFWhiteBlackListDesc.h"
#include "NFGMCtrlGiveDataDesc.h"

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemDay.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemStatMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFGameDay.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFSystemStat/NFSystemStat.h"

#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRedeemCode/NFRedeemCodeMgr.h"
#include "NFServerLogic/NFSnsServer/NFSnsServerPlayerPlugin/NFRedeemCode/NFRedeemCodeTrans.h"

#include "NFSnsSystemStatModule.h"


#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(NFIPluginManager* pm)
{
    CREATE_PLUGIN(pm, NFSnsServerPlugin)

};

NF_EXPORT void DllStopPlugin(NFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFSnsServerPlugin)
};

#endif


//////////////////////////////////////////////////////////////////////////

int NFSnsServerPlugin::GetPluginVersion()
{
	return 0;
}

std::string NFSnsServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(NFSnsServerPlugin);
}

void NFSnsServerPlugin::Install()
{
	REGISTER_MODULE(m_pPluginManager, NFISnsServerModule, NFCSnsServerModule);
    REGISTER_MODULE(m_pPluginManager, NFCUserMailModule, NFCUserMailModule);
	REGISTER_MODULE(m_pPluginManager, NFCOnlineModule, NFCOnlineModule);
    REGISTER_MODULE(m_pPluginManager, NFSnsWebHandleModule, NFSnsWebHandleModule);
    REGISTER_MODULE(m_pPluginManager, NFSnsSystemStatModule, NFSnsSystemStatModule);
}

void NFSnsServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(m_pPluginManager, NFISnsServerModule, NFCSnsServerModule);
    UNREGISTER_MODULE(m_pPluginManager, NFCUserMailModule, NFCUserMailModule);
	UNREGISTER_MODULE(m_pPluginManager, NFCOnlineModule, NFCOnlineModule);
    UNREGISTER_MODULE(m_pPluginManager, NFSnsWebHandleModule, NFSnsWebHandleModule);
    UNREGISTER_MODULE(m_pPluginManager, NFSnsSystemStatModule, NFSnsSystemStatModule);
}

bool NFSnsServerPlugin::InitShmObjectRegister()
{
    NFServerConfig* pConfig = NFConfigMgr::Instance()->GetAppConfig(NF_ST_SNS_SERVER);
    NF_ASSERT(pConfig);

    uint32_t maxOnlinePlayerNum = pConfig->mMaxOnlinePlayerNum;

    REGISTER_DESCSTORE(NFMailDesc, EOT_MAIL_CONFIG_DESC_ID, NF_DEFAULT_MYSQL_DB_NAME);

    REGISTER_SHM_OBJ_WITH_HASH(NFUserMail, EOT_USER_MAIL_EXT_ID, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFTransMail, EOT_TRANS_USER_MAIL_ID, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFTransMailCreate, EOT_TRANS_USER_MAIL_CREATE_ID, maxOnlinePlayerNum);
    REGISTER_SINGLETON_SHM_OBJ(NFUserMailMgr, EOT_USER_MAIL_HASHTABLE_ID, 1);
    REGISTER_SHM_OBJ_WITH_HASH(NFUserMailCacheInfo, EOT_USER_MAIL_CACHE_ID, maxOnlinePlayerNum);
    REGISTER_SINGLETON_SHM_OBJ(NFUserMailUtil, EOT_USER_MAIL_CACHE_MNG_ID, 1);
    REGISTER_SINGLETON_SHM_OBJ(NFActivityMail, EOT_SNS_ACTIVITY_MAIL_DATA, 1);

    REGISTER_SHM_OBJ_WITH_HASH(NFOnlineUser, EOT_SNS_ONLINE_USER_ID, maxOnlinePlayerNum);
    REGISTER_SINGLETON_SHM_OBJ(NFOnlineUserMgr, EOT_SNS_ONLINE_USER_HASH_TABLE_ID, 1);

    REGISTER_SHM_OBJ_WITH_HASH(NFSnsUserSimple, EOT_SNS_USER_SIMPLE_ID, maxOnlinePlayerNum*5);
    REGISTER_SINGLETON_SHM_OBJ(NFSnsUserSimpleMgr, EOT_SNS_USER_SIMPLE_HASH_TABLE_ID, 1);
    REGISTER_SINGLETON_SHM_OBJ(NFSnsUserSimpleUtil, EOT_SNS_USER_SIMPLE_UTIL_ID, 1);
    REGISTER_SHM_OBJ(NFTransGetSnsUserSimple, EOT_TRANS_GET_USER_SIMPLE, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFTransSnsBase, EOT_TRANS_SNS_BASE, maxOnlinePlayerNum);
	REGISTER_SHM_OBJ(NFTransSnsUserOnline, EOT_TRANS_SNS_USER_ONLINE, maxOnlinePlayerNum/10);
	REGISTER_SHM_OBJ(NFTransSaveSimpleDB, EOT_TRANS_SAVE_USER_SIMPLEL, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFTransSnsSendEventLog, EOT_TRANS_SNS_SEND_EVENT_LOG_ID, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFGetRankTrans, EOT_TRANS_SNS_GET_TRANS_ID, maxOnlinePlayerNum);
    REGISTER_SHM_OBJ(NFRankCommon, EOT_RANK_COMMON_ID, 10);
    REGISTER_SINGLETON_SHM_OBJ(NFRankMgr, EOT_RANK_MGR_ID, 1);
    REGISTER_SHM_OBJ(NFSnsWebHandleTrans, EOT_TRANS_SNS_WEB_HANDLE_TRANS_ID, maxOnlinePlayerNum/10);

    REGISTER_DESCSTORE(NFWhiteBlackListDesc, EOT_WHILE_BLACK_LIST_DESC_ID, NF_DEFAULT_MYSQL_DB_NAME);
    REGISTER_DESCSTORE(NFGMCtrlGiveDataDesc, EOT_GM_CTRL_GIVE_DATA_DESC_ID, NF_DEFAULT_MYSQL_DB_NAME);
    REGISTER_SINGLETON_SHM_OBJ(NFSystemDay, EOT_LOG_SYSTEM_DAY_ID, 1);
    REGISTER_SINGLETON_SHM_OBJ(NFSystemStatMgr, EOT_SYSTEM_STAT_MGR_ID, 1);
    REGISTER_SINGLETON_SHM_OBJ(NFSystemStat, EOT_LOG_SYSTEM_STAT_ID, 1);
    REGISTER_SHM_OBJ_WITH_HASH(NFGameDay, EOT_LOG_GAME_DAY_ID, 100);

    REGISTER_SINGLETON_SHM_OBJ(NFRedeemCodeMgr, EOT_REDEEM_CODE_MGR_ID, 1);

    uint32_t redeemTransNum = maxOnlinePlayerNum / 10;
    if (redeemTransNum < 500)
    {
        redeemTransNum = 500;
    }
    REGISTER_SHM_OBJ(NFRedeemCodeTrans, EOT_REDEEM_CODE_TRANS_ID, redeemTransNum);
    return true;
}