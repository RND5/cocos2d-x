#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "DeviceRegisterPage.h"
#include "DeviceInfoIO.h"

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::gui;

extern std::vector<DeviceInformation> vecDeviceList;

class HelloWorld : public cocos2d::CCLayer
{
public:
    UILayer* uLayer;
    Widget* pWidget;

    Button* pBtn_setting;

    ListView* pListview_devices;       // listview

    Layout* pLayout_listAddItem;

    Layout* pLayout_listFirstItem;        // listview에 추가 될 아이템
    Label* pLabel_name;
    Label* pLabel_ip;
    Label* pLabel_num;

    Layout* pLayout_listSelectedItem;       // listview에 있는 item이 선택되었을 때 불리어짐.
    Button* pBtn_whatch;
    Button* pBtn_search;
    Button* pBtn_changeSet;
    Button* pBtn_back;
    
    Button* pBtn_addDevice;
    Button* pBtn_delDevice;
        
    Layout* firstLayout;

    DeviceInfoIO deviceInfoIO;              // json file에 있는 deviceinformation 정보를 저장하고 가져옴.
//    std::vector<DeviceInformation> vecDeviceList;

    int listview_count;

    void selectBtnAddDevice(CCObject* pSender, TouchEventType type);

    void getUI();

    void touchListviewItem(CCObject* pSender, TouchEventType type);













    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
