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

    // listview�� �߰� �� ������
    Layout* pLayout_listAddItem;

    // listview�� �߰��Ǵ� ������ �� ù ��° ���̾ƿ�.
    Layout* pLayout_listFirstItem;
    Label* pLabel_name;
    Label* pLabel_ip;
    Label* pLabel_num;

    // listview�� �߰��Ǵ� ������ �� �� ��° ���̾ƿ�. listview�� �ִ� ù ��° item�� ���õǾ��� �� �Ҹ�����.
    Layout* pLayout_listSelectedItem;
    //Button* pBtn_whatch;
    //Button* pBtn_search;
    //Button* pBtn_changeSet;
    //Button* pBtn_back;
    
    // ADD, DEL ��ư
    Button* pBtn_addDevice;
    Button* pBtn_delDevice;
        
    // listview�� ����Ǵ� �����ۿ� �̺�Ʈ ����.
    Widget* newItem;

    Layout* firstLayout;
    Layout* secontLayout;

    Label* name;
    Label* ip;
    Label* num;

    Button* back;

    Layout* selectLayout;
    Label* selectLabel;

    // listview �� �ִ� ��Ұ� Ŭ���� �����ΰ��� ��Ÿ���ִ� ��� ����
    bool isClicked;

    DeviceInfoIO deviceInfoIO;              // json file�� �ִ� deviceinformation ������ �����ϰ� ������.
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
