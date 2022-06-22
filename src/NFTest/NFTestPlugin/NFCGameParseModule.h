// -------------------------------------------------------------------------
//    @FileName         :    NFCGameParse.h
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCGameParse.h
//
// -------------------------------------------------------------------------

#pragma once

#include "NFComm/NFPluginModule/NFIModule.h"
#include "NFComm/NFPluginModule/NFTimerMgr.h"
#include "NFComm/NFPluginModule/NFServerDefine.h"

class NFCGameParseModule : public NFIModule, NFTimerObj
{
public:
    explicit NFCGameParseModule(NFIPluginManager* p);
    virtual ~NFCGameParseModule();

    virtual bool Init() override;

    virtual bool Execute() override;

    virtual bool BeforeShut() override;

    virtual bool Shut() override;

    virtual void OnTimer(uint32_t nTimerID) override;

    int CheckPoint();
    int PasreLog(int year, int month, int day, int days);
    int CalcReltention(const std::map<int, std::map<std::string, int>> &regData,
                       const std::map<int, std::map<std::string, int>> &logData, int day, int& reg_count,
                       int& count_1, int& count_2, int& count_3);
};