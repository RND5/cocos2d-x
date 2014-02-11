#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DeviceInfoIO.h"

using namespace cocos2d::gui;

class HelloWorld : public cocos2d::gui::TouchGroup
{
public:

  	TextField* pNameTextField;
	TextField* pIpTextField;

	CheckBox* pFenCheckBox;

	Button* pInputBtn;

	ListView* pListView;

	//
	// ����Ʈ�信 ����� �г�
	//
	Layout* pLayout;												// listView �� ����� �г�
	Label* pDevice_name;
	Label* pIpAddress;
	Label* pFenCheck;


//	std::string path;												// ���� ���� �н�
//	FILE *fp;
	
	std::vector<DeviceInfomation> deviceInfoList;
    
	void addListView();
    
	void touchInputBtn(CCObject* pSender, TouchEventType type);		// Input button Ŭ������ �� �Ͼ�� �̺�Ʈ �Լ�
    	
	void touchTextField(CCObject* pSender, TextFiledEventType type);		// textfield Ŭ������ �� ���� �� �����

    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
        
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
