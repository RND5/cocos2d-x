#include "cocos2d.h"

class DeviceInformation
{
private:
    std::string str_deviceName;
    std::string str_ip;
    bool useFen;
    int portNum;
    std::string str_userID;
    std::string str_password;

public:
    DeviceInformation(const char* name, const char* ip, bool fenCheck, int portNumber, const char* id, const char* pass);

    void setDeviceName(const char* name);
    void setIp(const char* ip);
    void setUseFen(const bool use);
    void setPort(int portNumber);
    void setId(const char* id);
    void setPassword(const char* pass);

    const std::string getDeviceName() const;
    const std::string getIp() const;
    const bool getUseFen() const;
    const int getPort() const;
    const std::string getId() const;
    const std::string getPassword() const;

    ~DeviceInformation();
};