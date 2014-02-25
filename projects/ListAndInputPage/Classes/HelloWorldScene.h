#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "DeviceRegisterPage.h"
#include "DeviceDeletePage.h"
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

    // listview
    ListView* pListview_devices;

    // listview에 추가 될 아이템
    Layout* pLayout_listAddItem;

    // listview에 추가되는 아이템 중 첫 번째 레이아웃.
    Layout* pLayout_listFirstItem;
    Label* pLabel_name;
    Label* pLabel_ip;
    Label* pLabel_num;

    // listview에 추가되는 아이템 중 두 번째 레이아웃. listview에 있는 첫 번째 item이 선택되었을 때 불리어짐.
    Layout* pLayout_listSelectedItem;
    //Button* pBtn_whatch;
    //Button* pBtn_search;
    //Button* pBtn_changeSet;
    //Button* pBtn_back;
    
    // ADD, DEL 버튼
    Button* pBtn_addDevice;
    Button* pBtn_delDevice;
        
    // listview에 저장되는 아이템에 이벤트 붙임.
    Widget* newItem;

    Layout* firstLayout;
    Layout* secontLayout;

    Label* name;
    Label* ip;
    Label* num;

    Button* back;

    Layout* selectLayout;
    Label* selectLabel;

    // listview 에 있는 요소가 클릭된 상태인가를 나타내주는 멤버 변수
    bool isClicked;

    DeviceInfoIO deviceInfoIO;              // json file에 있는 deviceinformation 정보를 저장하고 가져옴.
//    std::vector<DeviceInformation> vecDeviceList;

    int listview_count;

    void selectBtnAddDevice(CCObject* pSender, TouchEventType type);
        
    void selectBtnDelDevice(CCObject* pSender, TouchEventType type);

    void getUI();

    void touchListviewItem(CCObject* pSender, TouchEventType type);

    void touchBackButton(CCObject* pSender, TouchEventType type);











    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
