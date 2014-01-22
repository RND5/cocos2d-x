#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::gui;

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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();





	

	////////////////////////////////////////////////////////////////////////////////////
	/////
	/////	개발자 코드
	/////
	////////////////////////////////////////////////////////////////////////////////////

	// json 파일 가져오기
	Widget* pWidget = GUIReader::shareReader()->widgetFromJsonFile("inputProject_1.json");
	this->addWidget(pWidget);
	pWidget->setSize(ccp(visibleSize.width, visibleSize.height));
	













    
    return true;
}

