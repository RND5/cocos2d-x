#include "HelloWorldScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
//using namespace cocos2d::extension;

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
    
    CCDirector::sharedDirector()->setRASDelegate(this);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    this->setTag(3);
    this->setColor(ccGREEN);
    this->setOpacity(255);

    
    cocos2d::gui::Widget* pWidget = GUIReader::shareReader()->widgetFromJsonFile("test01_1.json");
    this->addWidget(pWidget);
    pWidget->setSize(ccp(visibleSize.width - 50, visibleSize.height-50)); // 현재의

 //   CCSize aa = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();

    return true;
}


void HelloWorld::screenSizeChanged(float width, float height)
{
    CCSize aa = CCEGLView::sharedOpenGLView()->getDesignResolutionSize();

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(width, height, kResolutionShowAll);

    CCScene* runScene = CCDirector::sharedDirector()->getRunningScene();
    
    if (runScene != NULL) {
        TouchGroup* layer =  (TouchGroup*)runScene->getChildByTag(3);
        layer -> setContentSize(CCSize(width, height));

        cocos2d::gui::Widget* pWidget = layer->getWidgetByTag(10);
        pWidget->setSize(CCSize(width - 50, height - 50));
        pWidget->setPosition(ccp(25, 25));

        cocos2d::gui::Widget* widgetBasePanel = layer->getWidgetByTag(20);
        
        widgetBasePanel -> setSize(CCSize(pWidget->getSize().width - 20, 100));
        widgetBasePanel -> setPosition(ccp(10, pWidget->getSize().height - widgetBasePanel->getSize().height - 10));
        
        cocos2d::gui::Widget* widget1 = (cocos2d::gui::Widget*)layer->TouchGroup::getWidgetByTag(31);
        cocos2d::gui::Widget* widget2 = (cocos2d::gui::Widget*)layer->TouchGroup::getWidgetByTag(32);

        if (widget1 != NULL) {
            widget1 -> setPosition(ccp(10, 10));
        }
        if (widget2 != NULL) {
            widget2 -> setPosition(ccp(widgetBasePanel->getSize().width - 10 - widget2->getSize().width, widget1->getPositionY()));
        }
    }
}

