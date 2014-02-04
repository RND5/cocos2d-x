#include "HelloWorldScene.h"
//#include <iostream>
#include <fstream>


//
// rapidjson 사용
//
#include "CocoStudio\Json\rapidjson\document.h"
#include "CocoStudio\Json\rapidjson\writer.h"
#include "CocoStudio\Json\rapidjson\prettywriter.h"
#include "CocoStudio\Json\rapidjson\filestream.h"
#include "CocoStudio\Json\rapidjson\stringbuffer.h"
#include "CocoStudio\Json\rapidjson\rapidjson.h"

//#include "DeviceInfomation.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace rapidjson;
using namespace gui;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !TouchGroup::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();





	

	////////////////////////////////////////////////////////////////////////////////////
	/////
	/////	개발자 코드
	/////
	////////////////////////////////////////////////////////////////////////////////////

	// json 파일 가져오기
	Widget* pWidget = GUIReader::shareReader()->widgetFromJsonFile("inputProject_1.json");
	this->addWidget(pWidget);
	pWidget->setSize(ccp(visibleSize.width, visibleSize.height));
	
//#ifdef TESTTEST
//    pNameTextField = dynamic_cast<MyTextField*>(pWidget->getChildByName("Name_TextField"));
//	pNameTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
//
//#else
//    pNameTextField = dynamic_cast<TextField*>(pWidget->getChildByName("Name_TextField"));
//	pNameTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
//    pNameTextField->setSizeType(cocos2d::gui::SIZE_ABSOLUTE);
//
//#endif
    
    
    pNameTextField = dynamic_cast<TextField*>(pWidget->getChildByName("Name_TextField"));
	pNameTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
	

//#ifdef TESTTEST
//	pIpTextField = dynamic_cast<MyTextField*>(pWidget->getChildByName("IP_TextField"));
//	pIpTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
//
//#else
//	pIpTextField = dynamic_cast<TextField*>(pWidget->getChildByName("IP_TextField"));
//	pIpTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
//#endif

    
	pIpTextField = dynamic_cast<TextField*>(pWidget->getChildByName("IP_TextField"));
	pIpTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));

	pFenCheckBox = dynamic_cast<CheckBox*>(pWidget->getChildByName("Check_CheckBox"));

	pListView = dynamic_cast<ListView*>(pWidget->getChildByName("Info_ListView"));
	
	pInputBtn = dynamic_cast<Button*>(pWidget->getChildByName("Input"));
	pInputBtn->addTouchEventListener(this, toucheventselector(HelloWorld::touchInputBtn));
	
	//
	// listview에 달 panel 정의하고 label을 추가 시킨다.
	//
	pLayout = dynamic_cast<Layout*>(pWidget->getChildByName("Device_Panel"));
	pDevice_name = dynamic_cast<Label*>(pWidget->getChildByName("Device_Panel")->getChildByName("Device_Name"));
	pIpAddress = dynamic_cast<Label*>(pWidget->getChildByName("Device_Panel")->getChildByName("IpAddress"));
	pFenCheck = dynamic_cast<Label*>(pWidget->getChildByName("Device_Panel")->getChildByName("Fen_Check"));

	pListView->setItemModel(pLayout);


	//
	// deviceInfomation 벡터를 생성하고, 제이슨에 있는 파일들을 벡터에 저장. 리스트뷰에 뿌려줌
	//




	//
	// json file 데이터 가져오기
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

	//			CCLog("member %s %n", membersArray[i]["device_name"].GetString());
	//			printf("gogo %s", membersArray[i]["device_name"].GetString());

				const Value& c = membersArray[i];
				
				std::string name = c["device_name"].GetString();
				std::string ip = c["ip_Address"].GetString();

	//			std::string name = membersArray[i]["device_name"].GetString();
	//			std::string ip = membersArray[i]["ip_Address"].GetString();

				CCLog("haha %s \n", name);
				
				//
				// deviceInfoList vector에 객체 추가 저장
				//
				deviceInfoList.push_back(DeviceInfomation(name.c_str(), ip.c_str(), true));

				pDevice_name->setText(deviceInfoList[0].getDeviceName());
				pIpAddress->setText(deviceInfoList[0].getIpAddress());
		
				//
				// ListView에 add
				//
				pListView->pushBackDefaultItem();


			}


			/*
			assert(a.IsArray());
			for(rapidjson::SizeType i = 0; i < a.Size(); i++) {
				CCLog("%s \n", a[i]["device_name"].GetString());
			}
			*/

			/*
			std::string str_00 = document["game_environments"]["0"]["name"].GetString();
			CCLog("name = %s\n", str_00.c_str());
			int setting_control = document["game_environments"]["0"]["data"].GetInt();
			CCLog("data = %d\n", setting_control);

			std::string str_01 = document["game_environments"]["1"]["name"].GetString();
			CCLog("name = %s\n", str_01.c_str());
			bool isEffect = document["game_environments"]["1"]["data"].GetBool();
			*/
		}		
	}

	
    
    return true;
}


void HelloWorld::touchTextField(CCObject* pSender, TextFiledEventType type)		// textfield 클릭했을 때 이전 값 지우기
{
	if(type == TEXTFIELD_EVENT_ATTACH_WITH_IME)
	{
        TextField* ptr = dynamic_cast<TextField*>(pSender);
        const char* str = ptr->getStringValue();
        dynamic_cast<TextField*>(pSender)->setText("");

	}

}


void HelloWorld::touchInputBtn(CCObject* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_BEGAN)
	{

		//
		// deviceInfoList vector에 객체 추가 저장
		//
		deviceInfoList.push_back(DeviceInfomation
			(pNameTextField->getStringValue(), pIpTextField->getStringValue(), pFenCheckBox->getSelectedState()));

		pDevice_name->setText(deviceInfoList[0].getDeviceName());
		pIpAddress->setText(deviceInfoList[0].getIpAddress());
		
		//
		// ListView에 add
		//
		pListView->pushBackDefaultItem();



		
		unsigned long size = 0;
		unsigned char* pData = NULL;
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		path.append("deviceInformation.json");
		pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size );
		
		Document document;
		document.SetObject();
		Value myArray(kArrayType);
		Document::AllocatorType& allocator = document.GetAllocator();

		std::vector<DeviceInfomation>::iterator iter = deviceInfoList.begin();
		std::vector<DeviceInfomation>::iterator eiter = deviceInfoList.end();
        
		for(; iter != eiter; ++iter) {

			Value objValue;
			objValue.SetObject();
			objValue.AddMember("device_name", (iter)->getDeviceName().c_str(), allocator);
            

            CCLog("objValue.GetString() : \n %s", objValue["device_name"].GetString());
            const char* str = objValue["device_name"].GetString();
            
			objValue.AddMember("ip_Address", (iter)->getIpAddress().c_str(), allocator);

			myArray.PushBack(objValue, allocator);

			CCLog("device_name : \n %s", (iter)->getDeviceName().c_str());
			CCLog("ip_Address : \n %s", (iter)->getIpAddress().c_str());

		}

		document.AddMember("Device_Information", myArray, allocator);

//        CCLog("%s", document["Device_Information"]["device_name"].GetString());

		StringBuffer strBuffer;
		Writer<StringBuffer> writer(strBuffer);
		document.Accept(writer);

        CCLog("strBuffer.GetString() : %s", strBuffer.GetString());

		std::string json = strBuffer.GetString();
		CCLog("clean data : \n %s", json.c_str());
		
		FILE *fp = fopen(path.c_str(), "w");

		if(!fp)
		{
			CCLog("can not create file %s", path.c_str());
		}
		
			
		fputs(json.c_str(), fp);
		
		CCLog("");
		
		fclose(fp);




	}

	/*
	if(type == TOUCH_EVENT_ENDED)
	{		
		fp = fopen(path.c_str(), "r");
		char str[100];

		fgets(str, 99, fp);

		pIpTextField->setText(str);

		CCLog("%s", str);
	}
	*/
}

void HelloWorld::addListView()
{

}


//readJson()
//{
//	unsigned long bufferSize = 0;
//	unsigned char* pData = NULL;
//	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
//	path.append("deviceInfomation.json");
//	pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &bufferSize);
//
//	if(pData == NULL) {
//		CCLog("There is not json file");
//	} 
//	else {
//		std::string data((const char*)pData, bufferSize);
//		CCLog("read content %s", data.c_str());
//		CC_SAFE_DELETE_ARRAY(pData);
//
//		 파일 저장이 알 수 없는 이유로 쓰레기 값이 붙어서 자장되어 clear한 data로 가공해준다.
//		size_t pos = data.rfind("}");
//		data = data.substr(0, pos + 1);
//		CCLog("clean data : %s", data.c_str());
//
//		Document document;
//
//		if(document.Parse<0>(data.c_str()).HasParseError()) {
//			CCLog(document.GetParseError());
//		}
//		else {
//			const Value& Device_Information = document["Device_Information"];
//			assert(Device_Information.IsArray());
//			for(rapidjson::SizeType i = 0; i < Device_Information.Size(); i++) {
//				CCLog("%s \n", Device_Information[i]["device_name"].GetString());
//			}
//			/*
//			std::string str_00 = document["game_environments"]["0"]["name"].GetString();
//			CCLog("name = %s\n", str_00.c_str());
//			int setting_control = document["game_environments"]["0"]["data"].GetInt();
//			CCLog("data = %d\n", setting_control);
//
//			std::string str_01 = document["game_environments"]["1"]["name"].GetString();
//			CCLog("name = %s\n", str_01.c_str());
//			bool isEffect = document["game_environments"]["1"]["data"].GetBool();
//			*/
//		}		
//	}
//}
//

//
//writeJson()
//{
//
//	Document document;
//	document.SetObject();
//
//
//
//
//
//
//
//
//
//
//
//
//
//	unsigned long size = 0;
//	unsigned char* pData = NULL;
//	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
//	path.append("deviceInfomation.json");
//	pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
//
//	if(pData == NULL) {
//		std::string fileName = "deviceInfomation.json";
//		CCAssert(fileName != "", "Invalid texture file name");
//
//		pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
//	}
//
//	std::string data((const char*)pData, size);
//	CCLog("read content %s", data.c_str());
//	CC_SAFE_DELETE_ARRAY(pData);
//
//	// 파일 저장이 알 수 없는 이유로 쓰레기 값이 붙어서 저장되어 clear한 data로 가공해준다.
//	size_t pos = data.rfind("}");
//	data = data.substr(0, pos + 1);
//	CCLog("clean data : \n %s", data.c_str());
//
//	Document document;
//	if(document.Parse<0>(data.c_str()).HasParseError()) {
//		CCLog(document.GetParseError());
//	}
//	else {
//		/*
//		std::string str_00 = document["Device_Information"]["name"].GetString();
//		CCLog("name = %s\n", str_00.c_str());
//		document["game_environments"]["0"]["data"] = setting_control;
//		CCLog("data = %d\n", setting_control);
//		*/
//
//	//	const Value& Device_Information = document["Device_Information"];
//
//
//
//		/*
//		std::string str_00 = document["game_environments"]["0"]["name"].GetString();
//		CCLog("name = %s\n", str_00.c_str());
//		document["game_environments"]["0"]["data"] = setting_control;
//		CCLog("data = %d\n", setting_control);
//
//		std::string str_01 = document["game_environments"]["1"]["name"].GetString();
//		CCLog("name = %s\n", str_01.c_str());
//		document["game_environment"]["1"]["data"] = true;
//		*/
//
//
//	}
//	/* Document를 std::string 파일로 사용하기
//	StringBuffer buffer;
//	Writer<StringBuffer> writer(buffer);
//	document.Accept(writer);
//	std::string json = buffer.GetString();
//
//	CCLog("clean data : \n %s", json.c_str());
//	*/
//}
