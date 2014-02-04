#include "DeviceInfomation.h"

DeviceInfomation::DeviceInfomation(const char* name, const char* address, bool fenCheck) 
	: pDeviceName(name), pIpAddress(address), pFenCheck(fenCheck)
{
}

DeviceInfomation::~DeviceInfomation()
{
}

void DeviceInfomation::setDeviceName(const char* name)
{
	pDeviceName = name;
}

void DeviceInfomation::setIpAddress(const char* address)
{
	pIpAddress = address;
}

void DeviceInfomation::setFenCheck(const bool check)
{
	pFenCheck = check;
}

const std::string DeviceInfomation::getDeviceName() const
{
	return pDeviceName;
}

const std::string DeviceInfomation::getIpAddress() const
{
	return pIpAddress;
}

const bool DeviceInfomation::getFenCheck() const
{
	return pFenCheck;
}
