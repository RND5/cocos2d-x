#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DeviceInfomation.h"

using namespace cocos2d::gui;

////#define TESTTEST
//#ifdef TESTTEST
//
//class MyTextField : public TextField {
//public:
//public:
//	MyTextField() : TextField() {}
//	virtual ~MyTextField() {}
//
//    void setText(const std::string& text)
//	{
//        __super::setText(text);
//	}
//
//    void setFontSize(int size)
//	{
//        __super::setFontSize(size);
//	}
//
//    virtual void didNotSelectSelf()
//	{
//        __super::didNotSelectSelf();
//	}
//
//    const char* getStringValue()
//	{
//        return __super::getStringValue();
//	}
//
//    virtual bool onTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *unused_event)
//	{
//        __super::onTouchBegan(touch, unused_event);
//	}
//
//    void setMaxLengthEnabled(bool enable)
//	{
//        __super::setMaxLengthEnabled(enable);
//	}
//    bool isMaxLengthEnabled()
//	{
//        return __super::isMaxLengthEnabled();
//	}
//
//    void setMaxLength(int length)
//	{
//        __super::setMaxLength(length);
//	}
//
//    int getMaxLength()
//	{
//        return __super::getMaxLength();
//	}
//
//    void setPasswordEnabled(bool enable)
//	{
//        __super::setPasswordEnabled(enable);
//	}
//
//    bool isPasswordEnabled()
//	{
//        return __super::isPasswordEnabled();
//	}
//    void setPasswordStyleText(const char* styleText)
//	{
//        __super::setPasswordStyleText(styleText);
//	}
//    virtual void update(float dt)
//	{
//        __super::update(dt);
//	}
//    bool getAttachWithIME()
//	{
//        return __super::getAttachWithIME();
//	}
//    void setAttachWithIME(bool attach)
//	{
//        __super::setAttachWithIME(attach);
//	}
//    bool getDetachWithIME()
//	{
//        return __super::getDetachWithIME();
//	}
//    void setDetachWithIME(bool detach)
//	{
//        __super::setDetachWithIME(detach);
//	}
//    bool getInsertText()
//	{
//        return __super::getInsertText();
//	}
//    void setInsertText(bool insertText)
//	{
//        __super::setInsertText(insertText);
//	}
//    bool getDeleteBackward()
//	{
//        return __super::getDeleteBackward();
//	}
//    void setDeleteBackward(bool deleteBackward)
//	{
//        __super::setDeleteBackward(deleteBackward);
//	}
//    void addEventListenerTextField(CCObject* target, SEL_TextFieldEvent selecor)
//	{
//        __super::addEventListenerTextField(target, selecor);
//	}
//
//    virtual void setAnchorPoint(const cocos2d::CCPoint &pt)
//	{
//                    __super::setAnchorPoint(pt);
//	}
//    
//    /**
//     * Returns the "class name" of widget.
//     */
//    virtual std::string getDescription() const
//	{
//        return __super::getDescription();
//	}
//
//    virtual const cocos2d::CCSize& getContentSize() const
//	{
//        return __super::getContentSize();
//	}
//
//    virtual cocos2d::CCNode* getVirtualRenderer()
//	{
//        return __super::getVirtualRenderer();
//	}
//
//    void attachWithIME()
//	{
//        __super::attachWithIME();
//	}
//
//protected:
//    // event
//    void attachWithIMEEvent()
//    {
//        __super::attachWithIMEEvent();
//    }
//
//    void detachWithIMEEvent()
//    {
//        __super::detachWithIMEEvent();
//    }
//
//    void insertTextEvent()
//    {
//        __super::insertTextEvent();
//    }
//    void deleteBackwardEvent()
//    {
//        __super::deleteBackwardEvent();
//    }
//    virtual void onSizeChanged()
//    {
//        __super::onSizeChanged();
//    }
//    void textfieldRendererScaleChangedWithSize()
//    {
//        __super::textfieldRendererScaleChangedWithSize();
//    }
//    virtual Widget* createCloneInstance()
//    {
//        return __super::createCloneInstance();
//    }
//    virtual void copySpecialProperties(Widget* model)
//    {
//        __super::copySpecialProperties(model);
//    }
//};
//
//#endif

class HelloWorld : public cocos2d::gui::TouchGroup
{
public:
	
//#ifdef TESTTEST
//   	MyTextField* pNameTextField;
//	MyTextField* pIpTextField;
//
//#else
//  	TextField* pNameTextField;
//	TextField* pIpTextField;
//
//#endif

  	TextField* pNameTextField;
	TextField* pIpTextField;

	CheckBox* pFenCheckBox;

	Button* pInputBtn;

	ListView* pListView;

	//
	// 리스트뷰에 저장될 패널
	//
	Layout* pLayout;												// listView 에 저장될 패널
	Label* pDevice_name;
	Label* pIpAddress;
	Label* pFenCheck;


//	std::string path;												// 파일 저장 패스
//	FILE *fp;
	




	std::vector<DeviceInfomation> deviceInfoList;



	void addListView();


	void touchInputBtn(CCObject* pSender, TouchEventType type);		// Input button 클릭했을 때 일어나는 이벤트 함수

	
	void touchTextField(CCObject* pSender, TextFiledEventType type);		// textfield 클릭했을 때 이전 값 지우기






    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
        
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
