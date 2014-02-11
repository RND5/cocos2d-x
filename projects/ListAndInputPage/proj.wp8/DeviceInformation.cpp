#include "DeviceInformation.h"

DeviceInformation::DeviceInformation(const char* name, const char* ip, bool fenCheck, int portNumber, const char* id, const char* pass)
    : str_deviceName(name), str_ip(ip), useFen(fenCheck), portNum(portNumber), str_userID(id), str_password(pass)
{
}

DeviceInformation::~DeviceInformation()
{
}

void DeviceInformation::setDeviceName(const char* name)
{
	str_deviceName = name;
}

void DeviceInformation::setIp(const char* address)
{
	str_ip = address;
}

void DeviceInformation::setUseFen(const bool check)
{
	useFen = check;
}

void DeviceInformation::setPort(int portNumber)
{
    portNum = portNumber;
}

void DeviceInformation::setId(const char* id)
{
    str_userID = id;
}
void DeviceInformation::setPassword(const char* pass)
{
    str_password = pass;
}



const std::string DeviceInformation::getDeviceName() const
{
	return str_deviceName;
}

const std::string DeviceInformation::getIp() const
{
	return str_ip;
}

const bool DeviceInformation::getUseFen() const
{
	return useFen;
}

const int DeviceInformation::getPort() const
{
	return portNum;
}

const std::string DeviceInformation::getId() const
{
	return str_userID;
}

const std::string DeviceInformation::getPassword() const
{
	return str_password;
}
