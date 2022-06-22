// -------------------------------------------------------------------------
//    @FileName         :    NFStatusAction.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFStatusAction.cpp
//
// -------------------------------------------------------------------------

#include "NFMailAction.h"
#include "NFTestRobot.h"

#include "NFComm/NFMessageDefine/proto_cs.pb.h"
#include "NFComm/NFCore/NFRandom.hpp"
#include "NFRobotModule.h"
#include "NFComm/NFMessageDefine/proto_common.pb.h"

bool NFMailAction::Awake()
{
    return true;
}

bool NFMailAction::Finalize()
{
    return true;
}

int NFMailAction::OnHandleMessage(uint64_t unLinkId, uint64_t playerId, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    switch(nMsgId)
    {
        case proto_email::NF_SC_SNS_MAIL_LIST_RSP:
        {
            OnHandleMailListRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_email::NF_SC_SNS_MAIL_READ_RSP:
        {
            OnHandleMailReadRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_email::NF_SC_SNS_MAIL_GET_ITEM_RSP:
        {
            OnHandleMailGetItemRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_email::NF_SC_SNS_MAIL_AUTO_PUSH_RSP:
        {
            OnHandleMailNtf(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        case proto_email::NF_SC_SNS_MAIL_DEL_RSP:
        {
            OnHandleMailDelRsp(unLinkId, playerId, value2, nMsgId, msg, nLen);
            break;
        }
        default:
            break;
    }
    return true;
}

int NFMailAction::OnHandleAction()
{
    if (mStatus == MAIL_STATUS_NONE || mStatus == MAIL_STATUS_DEL_MAIL_SUCCESS)
    {
        SendGetMailListReq();
    }
    else if (mStatus == MAIL_STATUS_GET_LIST_MAIL || mStatus == MAIL_STATUS_READ_MAIL_SUCCESS)
    {
        ReadOneMailReq();
    }
    else if (mStatus == MAIL_STATUS_READ_ALL_MAIL_SUCCESS)
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "read all mail...................");
        int rand = NFRandInt(0, 100);
        if (rand >= 50)
        {
            DelOneMailReq();
        }
        else
        {
            SendGetMailListReq();
        }
    }
    return 0;
}

int NFMailAction::OnHandleMailDelRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    proto_email::Proto_CSMailDelRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    mStatus = MAIL_STATUS_DEL_MAIL_SUCCESS;
    for(int i = 0; i < (int)xMsg.mail_id_list_size(); i++)
    {
        NFLogInfo(NF_LOG_SYSTEMLOG, 0, "del one mail:{} success...................", xMsg.mail_id_list(i));
    }
    return 0;
}

void NFMailAction::SendGetMailListReq()
{
    proto_email::Proto_CSMailListReq xMsg;
    xMsg.set_begin(1);
    xMsg.set_end(10);

    m_pRobot->SendMsgToServer(proto_email::NF_CS_SNS_MAIL_LIST_REQ, xMsg);
    mStatus = MAIL_STATUS_GET_LIST_MAIL_REQ;
    NFLogInfo(NF_LOG_SYSTEMLOG, 0, "get all mail...................");
}

void NFMailAction::ReadOneMailReq()
{
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++)
    {
        if (m_mailList.role_mail_list(i).status() == proto_ff::EN_SNS_MAIL_NO_READ)
        {
            proto_email::Proto_CSMailReadReq xMsg;
            xMsg.set_mail_id(m_mailList.role_mail_list(i).id());
            m_pRobot->SendMsgToServer(proto_email::NF_CS_SNS_MAIL_READ_REQ, xMsg);
            mStatus = MAIL_STATUS_READ_MAIL;
            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "read one mail:{}...................", m_mailList.role_mail_list(i).id());
            break;
        }
    }
}

void NFMailAction::DelOneMailReq()
{
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++)
    {
        if (m_mailList.role_mail_list(i).status() == proto_ff::EN_SNS_MAIL_ALREADY_READ)
        {
            proto_email::Proto_CSMailDelReq xMsg;
            xMsg.add_mail_id(m_mailList.role_mail_list(i).id());
            m_pRobot->SendMsgToServer(proto_email::NF_CS_SNS_MAIL_DEL_REQ, xMsg);
            mStatus = MAIL_STATUS_DEL_MAIL;
            NFLogInfo(NF_LOG_SYSTEMLOG, 0, "del one mail:{}...................", m_mailList.role_mail_list(i).id());
            break;
        }
    }
}

int NFMailAction::OnHandleMailListRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, m_mailList);

    mStatus = MAIL_STATUS_GET_LIST_MAIL;

    if (m_mailList.result() == 0)
    {
        FindModule<NFCRobotModule>()->AddUserId(m_pRobot->m_playerId);
    }

    bool flag = true;
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++) {
        if (m_mailList.role_mail_list(i).status() != proto_ff::EN_SNS_MAIL_ALREADY_READ)
        {
            flag = false;
        }
    }

    if (flag)
    {
        mStatus = MAIL_STATUS_READ_ALL_MAIL_SUCCESS;
    }
    return 0;
}

int NFMailAction::OnHandleMailReadRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    proto_email::Proto_CSMailReadRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++)
    {
        for(int j = 0; j < (int)xMsg.mail_id_list_size(); j++)
        {
            if (m_mailList.role_mail_list(i).id() == xMsg.mail_id_list(j))
            {
                m_mailList.mutable_role_mail_list(i)->set_status(proto_ff::EN_SNS_MAIL_ALREADY_READ);
                mStatus = MAIL_STATUS_READ_MAIL_SUCCESS;
                NFLogInfo(NF_LOG_SYSTEMLOG, 0, "read one mail:{} success...................", m_mailList.role_mail_list(i).id());
                break;
            }
        }
    }

    bool flag = true;
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++) {
        if (m_mailList.role_mail_list(i).status() != proto_ff::EN_SNS_MAIL_ALREADY_READ)
        {
           flag = false;
        }
    }

    if (flag)
    {
        mStatus = MAIL_STATUS_READ_ALL_MAIL_SUCCESS;
    }

    return 0;
}

int NFMailAction::OnHandleMailGetItemRsp(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    proto_email::Proto_CSMailGetItemRsp xMsg;
    CLIENT_MSG_PROCESS_WITH_PRINTF(nMsgId, value, msg, nLen, xMsg);

    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++)
    {
        for(int j = 0; j < (int)xMsg.item_list_size(); j++)
        {
            if (m_mailList.role_mail_list(i).id() == xMsg.item_list(j).id())
            {
                m_mailList.mutable_role_mail_list(i)->set_status(proto_ff::EN_SNS_MAIL_ALREADY_READ);
            }
        }
    }

    bool flag = true;
    for(int i = 0; i < (int)m_mailList.role_mail_list_size(); i++) {
        if (m_mailList.role_mail_list(i).status() != proto_ff::EN_SNS_MAIL_ALREADY_READ)
        {
            flag = false;
        }
    }

    if (flag)
    {
        mStatus = MAIL_STATUS_READ_ALL_MAIL_SUCCESS;
    }
    return 0;
}

int NFMailAction::OnHandleMailNtf(uint64_t unLinkId, uint64_t value, uint64_t value2, uint32_t nMsgId, const char* msg, uint32_t nLen)
{
    SendGetMailListReq();
    return 0;
}
