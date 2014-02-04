#include "cocos2d.h"

class DeviceInfomation
{
private:
	std::string pDeviceName;
	std::string pIpAddress;
	bool pFenCheck;

public:
	DeviceInfomation(const char* name, const char* address, bool fenCheck);

	void setDeviceName(const char* name);
	void setIpAddress(const char* address);
	void setFenCheck(const bool check);

	const std::string getDeviceName() const;
	const std::string getIpAddress() const;
	const bool getFenCheck() const;

	~DeviceInfomation();
};