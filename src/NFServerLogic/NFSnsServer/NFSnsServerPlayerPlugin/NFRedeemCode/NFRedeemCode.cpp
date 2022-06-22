// -------------------------------------------------------------------------
//    @FileName         :    NFRedeemCode.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFRedeemCode.cpp
//
// -------------------------------------------------------------------------

#include "NFRedeemCode.h"
#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFPluginModule/NFMessageMgr.h"

NFRedeemCode::NFRedeemCode() {
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFRedeemCode::~NFRedeemCode() {

}

int NFRedeemCode::CreateInit() {
    m_lastTime = NFTime::Now().UnixSec();
    m_redeemCode.CreateInit();
    return 0;
}

int NFRedeemCode::ResumeInit() {
    return 0;
}

bool NFRedeemCode::IsTimeOver() {
    if (NFTime::Now().UnixSec() - m_lastTime >= 60)
    {
        return true;
    }
    return false;
}

int NFRedeemCode::Save()
{
    proto_ff::tbRedeemCode code;
    proto_ff_s::tbRedeemCode_s::write_to_pbmsg(m_redeemCode, code);

    return NFMessageMgr::Instance()->SendTransToStoreServer(NF_ST_SNS_SERVER,
                                                            proto_ff::E_STORESVR_C2S_MODIFYOBJ,
                                                            proto_ff::E_TABLE_NONE,
                                                            NF_DEFAULT_MYSQL_DB_NAME, "tbRedeemCode", code,
                                                            0, 0, std::hash<std::string>()(m_redeemCode.id.GetString()));
}
