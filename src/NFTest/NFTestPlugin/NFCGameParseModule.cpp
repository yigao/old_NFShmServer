// -------------------------------------------------------------------------
//    @FileName         :    NFCGameParseModule.cpp
//    @Author           :    xxxxx
//    @Date             :   xxxx-xx-xx
//    @Email			:    xxxxxxxxx@xxx.xxx
//    @Module           :    NFCGameParseModule.cpp
//
// -------------------------------------------------------------------------

#include "NFComm/NFCore/NFTime.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFLogMgr.h"
#include "NFComm/NFCore/NFCommon.h"
#include "NFComm/NFCore/NFFileUtility.h"
#include "NFComm/NFPluginModule/NFLogMgr.h"
#include "NFComm/NFShmCore/NFSizeString.h"
#include "NFComm/NFShmCore/NFArray.h"
#include "NFComm/NFMessageDefine/proto_common.pb.h"
#include "NFComm/NFMessageDefine/proto_common_s.h"
#include "NFCGameParseModule.h"

NFCGameParseModule::NFCGameParseModule(NFIPluginManager *p) : NFIModule(p) {

}

NFCGameParseModule::~NFCGameParseModule() {

}

bool NFCGameParseModule::Init() {
    SetTimer(1, 1000, 1);
    return true;
}

bool NFCGameParseModule::Execute() {
    return NFIModule::Execute();
}

bool NFCGameParseModule::BeforeShut() {
    return NFIModule::BeforeShut();
}

bool NFCGameParseModule::Shut() {
    return NFIModule::Shut();
}

void NFCGameParseModule::OnTimer(uint32_t nTimerID) {
    PasreLog(2020, 9, 30, 7);
}

uint64_t GetFormatTime(const std::string &str) {
    std::string year = str.substr(0, 4);
    std::string month = str.substr(4, 2);
    std::string day = str.substr(6, 2);
    std::string hour = str.substr(9, 2);
    std::string min = str.substr(11, 2);

    return NFTime::GetSecTime(NFCommon::strto<int>(year), NFCommon::strto<int>(month), NFCommon::strto<int>(day),
                              NFCommon::strto<int>(hour), NFCommon::strto<int>(min), 0);
}

uint64_t GetFileTime(const std::string &str) {
    std::string year = str.substr(0, 4);
    std::string month = str.substr(4, 2);
    std::string day = str.substr(6, 2);

    return NFTime::GetSecTime(NFCommon::strto<int>(year), NFCommon::strto<int>(month), NFCommon::strto<int>(day), 0, 0,
                              0);
}

struct LogoutData {
    LogoutData() {
        onlineTime = 0;
        maxLevel = 0;
    }

    uint32_t onlineTime;
    uint32_t maxLevel;
};

int NFCGameParseModule::CalcReltention(const std::map<int, std::map<std::string, int>> &regData,
                                       const std::map<int, std::map<std::string, int>> &logData, int day, int& reg_count,
                                       int& count_1, int& count_2, int& count_3) {
    reg_count = 0;
    count_1 = 0;
    count_2 = 0;
    count_3 = 0;
    auto reg_iter = regData.find(day);
    if (reg_iter != regData.end()) {
        for (auto iter = reg_iter->second.begin(); iter != reg_iter->second.end(); iter++) {
            const std::string &acc = iter->first;
            reg_count = reg_count + 1;
            auto log_iter_1 = logData.find(day + 1);
            if (log_iter_1 != logData.end()) {
                if (log_iter_1->second.find(acc) != log_iter_1->second.end()) {
                    count_1 = count_1 + 1;
                }
            }

            auto log_iter_2 = logData.find(day + 2);
            if (log_iter_2 != logData.end()) {
                if (log_iter_2->second.find(acc) != log_iter_2->second.end()) {
                    count_2 = count_2 + 1;
                }
            }

            auto log_iter_3 = logData.find(day + 3);
            if (log_iter_3 != logData.end()) {
                if (log_iter_3->second.find(acc) != log_iter_3->second.end()) {
                    count_3 = count_3 + 1;
                }
            }
        }
    }

    return 0;
}

int NFCGameParseModule::PasreLog(int year, int month, int day, int days) {
    std::string path = "./tlogd";
    std::list<std::string> files;
    NFFileUtility::GetFiles(path, files);
    uint64_t startTime = NFTime::GetSecTime(year, month, day, 0, 0, 0);

    std::map<int, std::map<std::string, int>> registerData;
    std::map<int, std::map<std::string, int>> loginData;
    std::map<int, std::map<std::string, LogoutData>> logoutData;
    for (int i = 1; i <= days; i++) {
        uint64_t nowTime = startTime + 86400 * (i - 1);
        for (auto f_iter = files.begin(); f_iter != files.end(); f_iter++) {
            std::string file = *f_iter;
            std::string fileName = NFFileUtility::GetFileNameWithoutExt(file);
            NFStringUtility::Trim(fileName, "65535_", true, false);
            uint64_t fileCreateTime = GetFileTime(fileName);
            if (fileCreateTime != nowTime) continue;

            std::list<std::string> lines;
            NFFileUtility::ReadFile(file.c_str(), lines);

            for (auto iter = lines.begin(); iter != lines.end(); iter++) {
                std::string line = *iter;
                NFStringUtility::Trim(line);
                std::vector<std::string> vec;
                NFStringUtility::SplitString(line, "|", vec);
                std::size_t lineSize = vec.size();

                if (lineSize <= 0) {
                    continue;
                }

                std::string logItem = vec[0];
                if (logItem == "PlayerRegister") {
                    if (lineSize >= 9) {
                        std::string openId = vec[8];
                        registerData[i][openId]++;
                    } else {
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "error data {}", line);
                    }
                } else if (logItem == "PlayerLogin") {
                    if (lineSize >= 9) {
                        std::string openId = vec[8];
                        loginData[i][openId]++;
                    } else {
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "error data {}", line);
                    }
                } else if (logItem == "PlayerLogout") {
                    if (lineSize == 51) {
                        std::string dataTime = vec[4];
                        std::string openId = vec[8];
                        std::string roleId = vec[9];
                        std::string job = vec[12];
                        int level = NFCommon::strto<int>(vec[13]);
                        int total_online = NFCommon::strto<int>(vec[31]);

                        logoutData[i][openId].onlineTime += total_online;
                        if (logoutData[i][openId].maxLevel < (uint32_t) level) {
                            logoutData[i][openId].maxLevel = level;
                        }
                    } else {
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "error data {}", line);
                    }
                }
            }
        }
    }

    for (int i = 1; i <= days; i++) {
        uint64_t nowTime = startTime + 86400 * (i - 1);
        int reg_count = 0;
        int count_1 = 0;
        int count_2 = 0;
        int count_3 = 0;

        CalcReltention(registerData, loginData, i, reg_count, count_1, count_2, count_3);

        if (reg_count == 0)
        {
            reg_count = 1;
        }
        NFLogError(NF_LOG_SYSTEMLOG, 0, "{} reg:{} Day+1:{} {} Day+2:{} {} DAY+3:{} {}", NFTime(nowTime, 0).GetFormatTime(), reg_count, count_1, (float)count_1*100/reg_count, count_2, (float)count_2*100/reg_count, count_3, (float)count_3*100/reg_count)
    }

    std::string loginAcc = "Login Acc:";
    for(auto iter = loginData.begin(); iter != loginData.end(); iter++)
    {
        loginAcc += NFCommon::tostr(iter->second.size()) + "\t";
    }
    NFLogError(NF_LOG_SYSTEMLOG, 0, "{}", loginAcc);
    return 0;
}

int NFCGameParseModule::CheckPoint() {
    std::string path = "./tlogd";
    std::list<std::string> files;
    NFFileUtility::GetFiles(path, files);
    uint64_t startTime = NFTime::GetSecTime(2020, 9, 30, 10, 0, 0);

    std::map<std::string, std::map<int, int>> OpenIdCheckPointMap;
    std::map<std::string, std::map<int, int>> RoleIdCheckPointMap;
    for (auto f_iter = files.begin(); f_iter != files.end(); f_iter++) {
        std::string file = *f_iter;
        std::string fileName = NFFileUtility::GetFileNameWithoutExt(file);
        NFStringUtility::Trim(fileName, "65535_", true, false);
        uint64_t fileCreateTime = GetFormatTime(fileName);
        if (fileCreateTime < startTime) continue;

        std::list<std::string> lines;
        NFFileUtility::ReadFile(file.c_str(), lines);

        for (auto iter = lines.begin(); iter != lines.end(); iter++) {
            std::string line = *iter;
            NFStringUtility::Trim(line);
            std::vector<std::string> vec;
            NFStringUtility::SplitString(line, "|", vec);
            std::size_t lineSize = vec.size();

            if (lineSize <= 0) {
                continue;
            }

            std::string logItem = vec[0];
            if (logItem == "ClientCheckPoint") {
                if (lineSize == 16) {
                    std::string openId = vec[8];
                    std::string roleId = vec[9];
                    int checkpoint = NFCommon::strto<int>(vec[15]);
                    OpenIdCheckPointMap[openId][checkpoint]++;
                    RoleIdCheckPointMap[roleId][checkpoint]++;
                    if (checkpoint > 104)
                    {
                        NFLogError(NF_LOG_SYSTEMLOG, 0, "error line:{}", line);
                    }
                }
                else {
                    NFLogError(NF_LOG_SYSTEMLOG, 0, "error line:{}", line);
                }
            }
        }
    }

    uint32_t maxPlayerNum = OpenIdCheckPointMap.size();
    uint32_t maxRoleNum = RoleIdCheckPointMap.size();
    std::map<int, int> checkPointData;

    std::map<int, int> checkPointMaxData;
    for(auto iter = OpenIdCheckPointMap.begin(); iter != OpenIdCheckPointMap.end(); iter++)
    {
        auto rbegin = iter->second.rbegin();
        if (rbegin != iter->second.rend())
        {
            checkPointMaxData[rbegin->first]++;
        }
        for(auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {
            checkPointData[iter2->first]++;
        }
    }

    std::string data;
    data += "max role num:" + NFCommon::tostr(maxRoleNum) + "\t\tmax player num:" + NFCommon::tostr(maxPlayerNum) + "\n";
    for(auto iter = checkPointData.begin(); iter != checkPointData.end(); iter++)
    {
        data += NFCommon::tostr(iter->first) + "\t\t\t" + NFCommon::tostr(iter->second) + "\n";
    }

    std::string maxData;
    maxData += "max role num:" + NFCommon::tostr(maxRoleNum) + "\t\tmax player num:" + NFCommon::tostr(maxPlayerNum) + "\n";
    uint32_t leftPlayer = maxPlayerNum;
    for(auto iter = checkPointMaxData.begin(); iter != checkPointMaxData.end(); iter++)
    {
        maxData += NFCommon::tostr(iter->first) + "\t\t\t" + NFCommon::tostr(leftPlayer) + "\n";
        leftPlayer = leftPlayer - iter->second;
    }

    NFFileUtility::Remove("checkpoint.txt");
    NFFileUtility::WriteFile("checkpoint.txt", data.c_str(), data.size());

    NFFileUtility::Remove("max_checkpoint.txt");
    NFFileUtility::WriteFile("max_checkpoint.txt", maxData.c_str(), maxData.size());

    return 0;
}
