#include "DeviceInfoIO.h"

#include <fstream>
#include "cocos-ext.h"

//
// rapidjson 사용.
//
#include "CocoStudio\Json\rapidjson\document.h"
#include "CocoStudio\Json\rapidjson\writer.h"
#include "CocoStudio\Json\rapidjson\prettywriter.h"
#include "CocoStudio\Json\rapidjson\filestream.h"
#include "CocoStudio\Json\rapidjson\stringbuffer.h"
#include "CocoStudio\Json\rapidjson\rapidjson.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace rapidjson;

void DeviceInfoIO::readJsonFile(std::vector<DeviceInformation>& deviceInfoList)
{

    //
    // json file 데이터 가져오기.
    //
    unsigned long bufferSize = 0;
    unsigned char* pData = NULL;
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("deviceInformation.json");
    pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &bufferSize);

    if(pData == NULL) {
        CCLog("There is not json file");
    } 
    else {
        std::string data((const char*)pData, bufferSize);
        CCLog("read content %s", data.c_str());
        CC_SAFE_DELETE_ARRAY(pData);

        ////// 파일 저장이 알 수 없는 이유로 쓰레기 값이 붙어서 자장되어 clear한 data로 가공해준다.
        //size_t pos = data.rfind("}");
        //data = data.substr(0, pos + 1);
        //CCLog("clean data : %s", data.c_str());

        Document document;

        document.Parse<0>(data.c_str());

        if(document.Parse<0>(data.c_str()).HasParseError()) {
            CCLog(document.GetParseError());
        }
        else {
            const Value& membersArray = document["Device_Information"];

            for(rapidjson::SizeType i = 0; i < membersArray.Size(); i++) {

                const Value& c = membersArray[i];

                std::string name = c["device_name"].GetString();
                std::string ipAddress = c["ip_Address"].GetString();
                bool useFen = c["useFen"].GetBool();
                int portNum = c["port_Num"].GetInt();
                std::string userID = c["user_ID"].GetString();
                std::string password = c["user_password"].GetString();

                //
                // deviceInfoList vector에 객체 추가 저장.
                //
                deviceInfoList.push_back(DeviceInformation(name.c_str(), ipAddress.c_str(), useFen, portNum, userID.c_str(), password.c_str()));
            }
        }
    }
}

bool DeviceInfoIO::writeJsonFile(std::vector<DeviceInformation>& deviceInfoList)
{

    if(deviceInfoList.size() == 1) {
        Document doc;
        doc.SetObject();

        // root 값은 배열로 설정.
        Value root(kArrayType);
        Document::AllocatorType& allocator = doc.GetAllocator();

        Value item;
        item.SetObject();

        Value vName;
        Value vIpAddr;
        Value vUseFen;
        Value vPortNum;
        Value vUserID;
        Value vUserPass;

        std::string name(deviceInfoList[0].getDeviceName());
        std::string ipAddress(deviceInfoList[0].getIp());
        bool useFen(deviceInfoList[0].getUseFen());
        int portNum(deviceInfoList[0].getPort());
        std::string userID(deviceInfoList[0].getId());
        std::string userPass(deviceInfoList[0].getPassword());

        vName.SetString(name.c_str(), name.length());
        vIpAddr.SetString(ipAddress.c_str(), ipAddress.length());
        vUseFen.SetBool(useFen);
        vPortNum.SetInt(portNum);
        vUserID.SetString(userID.c_str(), userID.length());
        vUserPass.SetString(userPass.c_str(), userPass.length());        

        // 각 요소들을 item으로 묶는다.
        item.AddMember("device_name", vName, allocator);
        item.AddMember("ip_Address", vIpAddr, allocator);
        item.AddMember("useFen", vUseFen, allocator);
        item.AddMember("port_Num", vPortNum, allocator);
        item.AddMember("user_ID", vUserID, allocator);
        item.AddMember("user_password", vUserPass, allocator);

        // 묶은 아이템을 root 배열에 넣는다.
        root.PushBack(item, allocator);

        doc.AddMember("Device_Information", root, allocator);   

        // json 파일에 쓰기.
        StringBuffer strBuffer;
        Writer<StringBuffer> writer(strBuffer);
        doc.Accept(writer);

        CCLog("strBuffer.GetString() : %s", strBuffer.GetString());

        std::string json = strBuffer.GetString();
        CCLog("clean data : \n %s", json.c_str());

        unsigned long size = 0;
        unsigned char* pData = NULL;
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
        path.append("deviceInformation.json");
        pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size );

        FILE *fp = fopen(path.c_str(), "w");

        if(!fp)
        {
            CCLog("can not create file %s", path.c_str());
        }


        fputs(json.c_str(), fp);

        CCLog("");

        fclose(fp);
    }

    else {
        unsigned long bufferSize = 0;
        unsigned char* pData = NULL;
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
        path.append("deviceInformation.json");
        pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &bufferSize);

        std::string data((const char*)pData, bufferSize);
        CCLog("read content %s", data.c_str());
        CC_SAFE_DELETE_ARRAY(pData);

        Document doc;        
        doc.Parse<0>(data.c_str());

        Value& root = doc["Device_Information"];
        Document::AllocatorType& allocator = doc.GetAllocator();

        Value item;
        item.SetObject();

        Value vName;
        Value vIpAddr;
        Value vUseFen;
        Value vPortNum;
        Value vUserID;
        Value vUserPass;

        std::string name(deviceInfoList[deviceInfoList.size() - 1].getDeviceName());
        std::string ipAddress(deviceInfoList[deviceInfoList.size() - 1].getIp());
        bool useFen(deviceInfoList[deviceInfoList.size() - 1].getUseFen());
        int portNum(deviceInfoList[deviceInfoList.size() - 1].getPort());
        std::string userID(deviceInfoList[deviceInfoList.size() - 1].getId());
        std::string userPass(deviceInfoList[deviceInfoList.size() - 1].getPassword());

        vName.SetString(name.c_str(), name.length());
        vIpAddr.SetString(ipAddress.c_str(), ipAddress.length());
        vUseFen.SetBool(useFen);
        vPortNum.SetInt(portNum);
        vUserID.SetString(userID.c_str(), userID.length());
        vUserPass.SetString(userPass.c_str(), userPass.length());    

        item.AddMember("device_name", vName, allocator);
        item.AddMember("ip_Address", vIpAddr, allocator);
        item.AddMember("useFen", vUseFen, allocator);
        item.AddMember("port_Num", vPortNum, allocator);
        item.AddMember("user_ID", vUserID, allocator);
        item.AddMember("user_password", vUserPass, allocator);

        root.PushBack(item, allocator);

        StringBuffer strBuffer;
        Writer<StringBuffer> writer(strBuffer);
        doc.Accept(writer);

        std::string json = strBuffer.GetString();
        CCLog("clean data : \n %s", json.c_str());

        unsigned long size1 = 0;
        unsigned char* pData1 = NULL;
        std::string path1 = CCFileUtils::sharedFileUtils()->getWritablePath();
        path1.append("deviceInformation.json");
        pData1 = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size1 );

        FILE *fp = fopen(path1.c_str(), "w");

        if(!fp) {
            CCLog("can not create file %s", path1.c_str());
        }


        fputs(json.c_str(), fp);

        CCLog("");

        fclose(fp);
    }

    return true;
}

bool DeviceInfoIO::delJsonFile(std::vector<DeviceInformation>& deviceInfoList)
{
    // list가 0일 때는 json 파일에 아무것도 없어야 됨.
    if(deviceInfoList.size() == 0) {        
        std::string path1 = CCFileUtils::sharedFileUtils()->getWritablePath();
        path1.append("deviceInformation.json");

        if(std::remove(path1.c_str()) != 0 )
            CCLog( "Error deleting file" );
        else
            CCLog( "File successfully deleted" );
        return true;
    }

    Document doc;
    doc.SetObject();

    // root 값은 배열로 설정.
    Value root(kArrayType);
    Document::AllocatorType& allocator = doc.GetAllocator();

    Value item;
    item.SetObject();

    Value vName;
    Value vIpAddr;
    Value vUseFen;
    Value vPortNum;
    Value vUserID;
    Value vUserPass;

    std::string name(deviceInfoList[0].getDeviceName());
    std::string ipAddress(deviceInfoList[0].getIp());
    bool useFen(deviceInfoList[0].getUseFen());
    int portNum(deviceInfoList[0].getPort());
    std::string userID(deviceInfoList[0].getId());
    std::string userPass(deviceInfoList[0].getPassword());

    vName.SetString(name.c_str(), name.length());
    vIpAddr.SetString(ipAddress.c_str(), ipAddress.length());
    vUseFen.SetBool(useFen);
    vPortNum.SetInt(portNum);
    vUserID.SetString(userID.c_str(), userID.length());
    vUserPass.SetString(userPass.c_str(), userPass.length());        

    // 각 요소들을 item으로 묶는다.
    item.AddMember("device_name", vName, allocator);
    item.AddMember("ip_Address", vIpAddr, allocator);
    item.AddMember("useFen", vUseFen, allocator);
    item.AddMember("port_Num", vPortNum, allocator);
    item.AddMember("user_ID", vUserID, allocator);
    item.AddMember("user_password", vUserPass, allocator);

    // 묶은 아이템을 root 배열에 넣는다.
    root.PushBack(item, allocator);

    doc.AddMember("Device_Information", root, allocator);   

    // json 파일에 쓰기.
    StringBuffer strBuffer;
    Writer<StringBuffer> writer(strBuffer);
    doc.Accept(writer);

    CCLog("strBuffer.GetString() : %s", strBuffer.GetString());

    std::string json = strBuffer.GetString();
    CCLog("clean data : \n %s", json.c_str());

    unsigned long size = 0;
    unsigned char* pData = NULL;
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("deviceInformation.json");
    pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size );

    FILE *fp = fopen(path.c_str(), "w");

    if(!fp)
    {
        CCLog("can not create file %s", path.c_str());
    }


    fputs(json.c_str(), fp);

    CCLog("");

    fclose(fp);



    for(int i = 1; i < deviceInfoList.size(); i++) {


        unsigned long bufferSize = 0;
        unsigned char* pData = NULL;
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
        path.append("deviceInformation.json");
        pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &bufferSize);

        std::string data((const char*)pData, bufferSize);
        CCLog("read content %s", data.c_str());
        CC_SAFE_DELETE_ARRAY(pData);

        Document doc;        
        doc.Parse<0>(data.c_str());

        Value& root = doc["Device_Information"];
        Document::AllocatorType& allocator = doc.GetAllocator();

        Value item;
        item.SetObject();

        Value vName;
        Value vIpAddr;
        Value vUseFen;
        Value vPortNum;
        Value vUserID;
        Value vUserPass;

        std::string name(deviceInfoList[i].getDeviceName());
        std::string ipAddress(deviceInfoList[i].getIp());
        bool useFen(deviceInfoList[i].getUseFen());
        int portNum(deviceInfoList[i].getPort());
        std::string userID(deviceInfoList[i].getId());
        std::string userPass(deviceInfoList[i].getPassword());

        vName.SetString(name.c_str(), name.length());
        vIpAddr.SetString(ipAddress.c_str(), ipAddress.length());
        vUseFen.SetBool(useFen);
        vPortNum.SetInt(portNum);
        vUserID.SetString(userID.c_str(), userID.length());
        vUserPass.SetString(userPass.c_str(), userPass.length());    

        item.AddMember("device_name", vName, allocator);
        item.AddMember("ip_Address", vIpAddr, allocator);
        item.AddMember("useFen", vUseFen, allocator);
        item.AddMember("port_Num", vPortNum, allocator);
        item.AddMember("user_ID", vUserID, allocator);
        item.AddMember("user_password", vUserPass, allocator);

        root.PushBack(item, allocator);

        StringBuffer strBuffer;
        Writer<StringBuffer> writer(strBuffer);
        doc.Accept(writer);

        std::string json = strBuffer.GetString();
        CCLog("clean data : \n %s", json.c_str());

        unsigned long size1 = 0;
        unsigned char* pData1 = NULL;
        std::string path1 = CCFileUtils::sharedFileUtils()->getWritablePath();
        path1.append("deviceInformation.json");
        pData1 = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size1 );

        FILE *fp = fopen(path1.c_str(), "w");

        if(!fp) {
            CCLog("can not create file %s", path1.c_str());
        }


        fputs(json.c_str(), fp);

        CCLog("");

        fclose(fp);
    }
    return true;

}