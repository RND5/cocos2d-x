#include "cocos2d.h"
#include "DeviceInfomation.h"

class DeviceInfoIO {
public:
    
    void readJsonFile(std::vector<DeviceInfomation>& deviceInfoList);

    bool writeJsonFile(std::vector<DeviceInfomation>& deviceInfoList);
};