#ifndef __DeviceRegisterPage__H__
#define __DeviceRegisterPage__H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::gui;

class DeviceRegisterPage : public cocos2d::CCLayer
{
public:
    UILayer* pLayer;
    Widget* pWidget;

    TextField* pTextField_name;
    TextField* pTextField_ip;
    CheckBox* pCheckBox_fen;
    TextField* pTextField_port;
    TextField* pTextField_id;
    TextField* pTextField_pass;
    
	Button* pBtn_save;
    
    void getUI();
	void selectBtnSave(CCObject* pSender, TouchEventType type);






    virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(DeviceRegisterPage);
};

#endif // __DeviceRegisterPage__H__