#include "cocos2d.h"
#include "DeviceInformation.h"

class DeviceInfoIO {
public:
    void readJsonFile(std::vector<DeviceInformation>& deviceInfoList);
    bool writeJsonFile(std::vector<DeviceInformation>& deviceInfoList);
    bool delJsonFile(std::vector<DeviceInformation>& deviceInfoList);
};