#include "HelloWorldScene.h"

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
	/////	개발자 코드.
	/////
	////////////////////////////////////////////////////////////////////////////////////

	// json 파일 가져오기.
	Widget* pWidget = GUIReader::shareReader()->widgetFromJsonFile("inputProject_1.json");
	this->addWidget(pWidget);
	pWidget->setSize(ccp(visibleSize.width, visibleSize.height));
	   
    pNameTextField = dynamic_cast<TextField*>(pWidget->getChildByName("Name_TextField"));
	pNameTextField->addEventListenerTextField(this, textfieldeventselector(HelloWorld::touchTextField));
	

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

    DeviceInfoIO deviceInfoIO;
    deviceInfoIO.readJsonFile(deviceInfoList);
    
    for(std::vector<DeviceInfomation>::iterator iter = deviceInfoList.begin(); iter < deviceInfoList.end(); iter++) {
	    pDevice_name->setText(iter->getDeviceName());
	    pIpAddress->setText(iter->getIpAddress());
	    pListView->pushBackDefaultItem();
    }

    return true;
}


void HelloWorld::touchTextField(CCObject* pSender, TextFiledEventType type)		// textfield 클릭했을 때 이전 값 지우기.
{
	if(type == TEXTFIELD_EVENT_ATTACH_WITH_IME)	{
        TextField* ptr = dynamic_cast<TextField*>(pSender);
        const char* str = ptr->getStringValue();
        ptr->setText("");

	}
    else if (type == TEXTFIELD_EVENT_DETACH_WITH_IME) {

    }
}


void HelloWorld::touchInputBtn(CCObject* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_BEGAN)
	{
		//
		// deviceInfoList vector에 객체 추가 저장.
		//

		deviceInfoList.push_back(DeviceInfomation
			(pNameTextField->getStringValue(), pIpTextField->getStringValue(), pFenCheckBox->getSelectedState()));
        
        if(deviceInfoList.size() != 0) {
            pListView->removeAllItems();

            for(int i = 0; i < deviceInfoList.size(); i++) {
		        pDevice_name->setText(deviceInfoList[i].getDeviceName());
		        pIpAddress->setText(deviceInfoList[i].getIpAddress());
        
                pListView->pushBackDefaultItem();
            }
        }

        DeviceInfoIO deviceInfoIO;
        deviceInfoIO.writeJsonFile(deviceInfoList);
	}
}

void HelloWorld::addListView()
{

}


