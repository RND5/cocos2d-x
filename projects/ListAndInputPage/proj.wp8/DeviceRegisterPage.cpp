#include "DeviceRegisterPage.h"
#include "HelloWorldScene.h"
//#include <Const.h>
//#include <REDCore.h>
//#include <Watcher.h>

CCScene* DeviceRegisterPage::scene()
{
    CCScene* scene = CCScene::create();

    DeviceRegisterPage* layer = DeviceRegisterPage::create();

    scene->addChild(layer);
    //REDCore::getREDCore();
    //new Watcher();
    return scene;
}

bool DeviceRegisterPage::init()
{
    if(!CCLayer::init()) {
        return false;
    }

    pLayer = UILayer::create();
    addChild(pLayer);

    pWidget =  GUIReader::shareReader()->widgetFromJsonFile("DeviceInputPage_1.json");
    pLayer->addWidget(pWidget);
        
    // 위젯 사이즈를 핸드폰 해상도와 같게 설정
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    pWidget->setSize(ccp(visibleSize.width, visibleSize.height));

    getUI();



    return true;
}

void DeviceRegisterPage::selectBtnSave(CCObject* pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN) {
        //
		// deviceInfoList vector에 객체 추가 저장.
		//
        
		vecDeviceList.push_back(DeviceInformation
			(pTextField_name->getStringValue(), pTextField_ip->getStringValue(), pCheckBox_fen->getSelectedState(), 
std::stoi(pTextField_port->getStringValue()), pTextField_id->getStringValue(), pTextField_pass->getStringValue()));
        
        /*if(vecDeviceList.size() != 0) {
            pListView->removeAllItems();

            for(int i = 0; i < vecDeviceList.size(); i++) {
                pDevice_name->setText(vecDeviceList[i].getDeviceName());
                pIpAddress->setText(vecDeviceList[i].getIp());

                pListView->pushBackDefaultItem();
            }
        }*/

        DeviceInfoIO dio;
        dio.writeJsonFile(vecDeviceList);

        CCScene* pScene = HelloWorld::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void DeviceRegisterPage::getUI()
{
    pTextField_name = dynamic_cast<TextField*>(pWidget->getChildByTag(4)->getChildByTag(7)->getChildByTag(9));
    pTextField_ip = dynamic_cast<TextField*>(pWidget->getChildByTag(10)->getChildByTag(13)->getChildByTag(15));
    pCheckBox_fen = dynamic_cast<CheckBox*>(pWidget->getChildByTag(10)->getChildByTag(16)->getChildByTag(18));
    pTextField_port = dynamic_cast<TextField*>(pWidget->getChildByTag(10)->getChildByTag(19)->getChildByTag(21));
    pTextField_id = dynamic_cast<TextField*>(pWidget->getChildByTag(22)->getChildByTag(25)->getChildByTag(27));
    pTextField_pass = dynamic_cast<TextField*>(pWidget->getChildByTag(22)->getChildByTag(28)->getChildByTag(30));
    
    pBtn_save = dynamic_cast<Button*>(pWidget->getChildByTag(31)->getChildByTag(32));
    pBtn_save->setTitleText("SAVE");
    
    pBtn_save->addTouchEventListener(this, toucheventselector(DeviceRegisterPage::selectBtnSave));
}