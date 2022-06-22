// -------------------------------------------------------------------------
//    @FileName         :    NFSystemStatMgr.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFSystemStatMgr.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFShmCore/NFShmObj.h"
#include "NFComm/NFShmCore/NFArray.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"

class NFGameDay;
class NFSystemStatMgr : public NFShmObj
{
public:
    NFSystemStatMgr();
    virtual ~NFSystemStatMgr();
    //非继承函数, 不要加virtual
    int CreateInit();
    //非继承函数, 不要加virtual
    int ResumeInit();
public:
    int Init();
    //must be virtual
    virtual void OnTimer(int timeId, int callcount);
    int DayTick();

    int InitSystemDay();
    int InitGameDay(uint32_t gameId, uint32_t roomId);

    NFGameDay* GetGameDay(uint32_t gameId, uint32_t roomId);
public:
    int InitGameReg(uint32_t gameId, uint32_t roomId);
private:
    bool m_bInited;
    int m_checkTimer;
    int m_dayTimer;
DECLARE_IDCREATE(NFSystemStatMgr)
};