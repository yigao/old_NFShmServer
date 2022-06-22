// -------------------------------------------------------------------------
//    @FileName         :    NFMailDesc.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFMailDesc.cpp
//
// -------------------------------------------------------------------------

#include "NFMailDesc.h"
#include "NFComm/NFPluginModule/NFCheck.h"
#include "NFComm/NFCore/NFSnprintf.h"
#include "NFComm/NFShmCore/NFServerFrameTypeDefines.h"
#include "NFComm/NFPluginModule/NFConfigMgr.h"
#include "NFComm/NFCore/NFTimeUtil.h"

IMPLEMENT_IDCREATE_WITHTYPE(NFMailDesc, EOT_MAIL_CONFIG_DESC_ID, NFShmObj)

NFMailDesc::NFMailDesc()
{
    if (EN_OBJ_MODE_INIT == NFShmMgr::Instance()->GetCreateMode()) {
        CreateInit();
    } else {
        ResumeInit();
    }
}

NFMailDesc::~NFMailDesc()
{

}


int NFMailDesc::CreateInit() {
    Initialize();
    memset(&m_aiIndex, 0, sizeof(m_aiIndex));
    return 0;
}

int NFMailDesc::ResumeInit() {
    return 0;
}

int NFMailDesc::Load(NFResDB *pDB)
{
    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "--begin--");
    CHECK_EXPR(pDB != NULL, -1, "pDB == NULL");

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "NFMailDesc::Load() strFileName = {}", GetFileName());

    proto_ff::Sheet_MailDesc table;
    NFResTable* pResTable = pDB->GetTable(GetFileName());
    CHECK_EXPR(pResTable != NULL, -1, "pTable == NULL, GetTable:{} Error", GetFileName());

    int iRet = 0;
    iRet = pResTable->FindAllRecord(GetDBName(), &table);
    CHECK_EXPR(iRet == 0, -1, "FindAllRecord Error:{}", GetFileName());

    NFLogTrace(NF_LOG_SNS_SERVER_PLUGIN, 0, "{}", table.Utf8DebugString());

    CreateInit();

    if ((table.maildesc_list_size() < 0) || (table.maildesc_list_size() > (int)(m_astDesc.GetMaxSize())))
    {
        NFLogError(NF_LOG_SNS_SERVER_PLUGIN, 0, "Invalid TotalNum:{}", table.maildesc_list_size());
        return -2;
    }

    m_astDesc.SetSize(table.maildesc_list_size());
    for (int i = 0; i < table.maildesc_list_size(); i++)
    {
        const proto_ff::MailDesc& desc = table.maildesc_list(i);
        proto_ff_s::MailDesc_s::read_from_pbmsg(desc, m_astDesc[i]);
        m_aiIndex[desc.id()] = i;

        m_astDesc[i].start_time = StrToTimePure(m_astDesc[i].start_time_str.Get());
        m_astDesc[i].end_time = StrToTimePure(m_astDesc[i].end_time_str.Get());
    }

    NFLogTrace(NF_LOG_GAME_SERVER_PLUGIN, 0, "load {}, num={}", iRet, table.maildesc_list_size());
    NFLogTrace(NF_LOG_GAME_SERVER_PLUGIN, 0, "--end--");
    return 0;
}

int NFMailDesc::CheckWhenAllDataLoaded()
{
    NFLogTrace(NF_LOG_SUB_GAME_PLUGIN, 0, "--begin--");

    NFLogTrace(NF_LOG_SUB_GAME_PLUGIN, 0, "--end--");

    return 0;
}

const proto_ff_s::MailDesc_s *NFMailDesc::GetDesc(int32_t descId) const {
    CHECK_EXPR(m_aiIndex[descId] >= 0 && m_aiIndex[descId] < m_astDesc.GetSize(), NULL, "descId [{}] not configed.", descId);

    return &m_astDesc[m_aiIndex[descId]];
}


