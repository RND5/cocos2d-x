#ifndef __DeviceDeletePage__H__
#define __DeviceDeletePage__H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::gui;

class DeviceDeletePage : public cocos2d::CCLayer
{
public:
    UILayer* pLayer;
    Widget* pWidget;

    ListView* pListview_devices;

    Layout* pLayout_item;
    CheckBox* pCheckbox;
    Label* pLabel_name;
    Label* pLabel_ip;

    Button* pBtn_delete;
    Button* pBtn_cancel;

    void getUI();
    void showListview();
    void selectBtnDelete(CCObject* pSender, TouchEventType type);
	void selectBtnCancel(CCObject* pSender, TouchEventType type);




    virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(DeviceDeletePage);
};

#endif // __DeviceDeletePage__H__