#include "DeviceDeletePage.h"
#include "HelloWorldScene.h"
//#include <Const.h>
//#include <REDCore.h>
//#include <Watcher.h>

CCScene* DeviceDeletePage::scene()
{
    CCScene* scene = CCScene::create();

    DeviceDeletePage* layer = DeviceDeletePage::create();

    scene->addChild(layer);
    //REDCore::getREDCore();
    //new Watcher();
    return scene;
}

bool DeviceDeletePage::init()
{
    if(!CCLayer::init()) {
        return false;
    }
    
    getUI();

    showListview();

    return true;
}

void DeviceDeletePage::getUI()
{
    pLayer = UILayer::create();
    addChild(pLayer);

    pWidget =  GUIReader::shareReader()->widgetFromJsonFile("DeviceDeletePage_1.json");
    pLayer->addWidget(pWidget);
        
    // 위젯 사이즈를 핸드폰 해상도와 같게 설정
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    pWidget->setSize(ccp(visibleSize.width, visibleSize.height));

    pListview_devices = dynamic_cast<ListView*>(pWidget->getChildByTag(8));
    pLayout_item = dynamic_cast<Layout*>(pWidget->getChildByTag(2));
    pCheckbox = dynamic_cast<CheckBox*>(pWidget->getChildByTag(2)->getChildByTag(3));
    pLabel_name = dynamic_cast<Label*>(pWidget->getChildByTag(2)->getChildByTag(4));
    pLabel_ip = dynamic_cast<Label*>(pWidget->getChildByTag(2)->getChildByTag(5));

    pBtn_delete = dynamic_cast<Button*>(pWidget->getChildByTag(9)->getChildByTag(10));
    pBtn_cancel = dynamic_cast<Button*>(pWidget->getChildByTag(9)->getChildByTag(11));

    pBtn_delete->addTouchEventListener(this, toucheventselector(DeviceDeletePage::selectBtnDelete));
    pBtn_cancel->addTouchEventListener(this, toucheventselector(DeviceDeletePage::selectBtnCancel));

    pListview_devices->setItemModel(pLayout_item);
}

void DeviceDeletePage::showListview()
{
    for(std::vector<DeviceInformation>::iterator iter = vecDeviceList.begin(); iter < vecDeviceList.end(); iter++) {
        pLabel_name->setText(iter->getDeviceName());
        pLabel_ip->setText(iter->getIp());
        // listview에 device 정보 추가
        pListview_devices->pushBackDefaultItem();
    }
}

void DeviceDeletePage::selectBtnCancel(CCObject* pSender, TouchEventType type)
{
    CCScene* pScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);    
}

void DeviceDeletePage::selectBtnDelete(CCObject* pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN) {

        int i = 0;
        int size = vecDeviceList.size();
        for(std::vector<DeviceInformation>::iterator iter = vecDeviceList.begin(); iter < vecDeviceList.end(); /*iter++*/) {

            CheckBox* pCheck = dynamic_cast<CheckBox*>(pListview_devices->getItem(i)->getChildByTag(3));
            if(pCheck->getSelectedState() == true) {
                CCLog("\n%d\n", i + 1);
                iter = vecDeviceList.erase(iter);
            } else
                ++iter;

            i++;
        }

        CCLog("\nsize: %d\n", vecDeviceList.size());


        DeviceInfoIO dio;
        dio.delJsonFile(vecDeviceList);




        CCScene* pScene = HelloWorld::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);    
    }
}