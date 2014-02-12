#include "HelloWorldScene.h"
//#include <Const.h>
//#include <Watcher.h>
//#include <REDCore.h>

std::vector<DeviceInformation> vecDeviceList;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    //REDCore::getREDCore();
    //Watcher* watcher = new Watcher();

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();




    ////////////////////////////////////////////////////////////////////////////////////
    /////
    /////	개발자 코드.
    /////
    ////////////////////////////////////////////////////////////////////////////////////

    // listview에 있는 요소가 선택된 상태인지 알려줌. 현재 선택 안되었기 때문에 false
    isClicked = false;

    getUI();                                                                        // json에 있는 gui를 가져옴.

    pListview_devices->setItemModel(pLayout_listAddItem);                           // listview에 들어갈 아이템 pLayout_listAddItem으로 설정.

    //    std::vector<DeviceInformation> vecDeviceList;

    // device 등록 페이지에서 첫 페이지로 다시 넘어올 때, vector를 초기화 해준다.
    vecDeviceList.clear();
    // json 파일에 있는 device 정보를 읽고 vector에 넣는다.
    deviceInfoIO.readJsonFile(vecDeviceList);           

    // listview에 몇 개가 들어가는지 세기 위한 카운터
    listview_count = 0;

    // vector 정보를 listview에 저장.
    for(std::vector<DeviceInformation>::iterator iter = vecDeviceList.begin(); iter < vecDeviceList.end(); iter++) {
        // listview에 몇 개가 들어가는지 세기 위한 카운터
        listview_count++;
        
        // vector에 저장된 device 정보를 listview에 넣을 요소들에 저장        
        pLabel_name->setText(iter->getDeviceName());
        pLabel_ip->setText(iter->getIp());
                
        // int에서 string으로 변환하여 listview label에 몇 번째인지 num을 대입. 
        std::ostringstream ostr;
        ostr.str("");
        ostr << listview_count;
        pLabel_num->setText(ostr.str().c_str());

        // listview에 device 정보 추가
        pListview_devices->pushBackDefaultItem();

        // listview에 저장되는 아이템에 이벤트 붙임.
        newItem = pListview_devices->getItem(listview_count - 1);
        firstLayout = dynamic_cast<Layout*>(newItem->getChildByTag(12));
        secontLayout = dynamic_cast<Layout*>(newItem->getChildByTag(16));
        name = dynamic_cast<Label*>(newItem->getChildByTag(12)->getChildByTag(13));
        ip = dynamic_cast<Label*>(newItem->getChildByTag(12)->getChildByTag(14));
        num = dynamic_cast<Label*>(newItem->getChildByTag(12)->getChildByTag(15));

        firstLayout->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));
        name->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));
        ip->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));
        num->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));

        back = dynamic_cast<Button*>(newItem->getChildByTag(16)->getChildByTag(20));
        back->addTouchEventListener(this, toucheventselector(HelloWorld::touchBackButton));

    }


    /*                      한글 깨지는 현상 방지
    char msg[128];

    WideCharToMultiByte(CP_UTF8, 0, L"이젠괜찮아", -1, msg, 128, NULL, NULL);

    CCLog("%s", msg);
    */

    return true;
}


void HelloWorld::selectBtnAddDevice(CCObject* pSender, TouchEventType type)
{   
    if(type == TOUCH_EVENT_BEGAN) {
        CCScene* pScene = DeviceRegisterPage::scene();

        CCDirector* pDirector = CCDirector::sharedDirector();
        //CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

        //pDirector->setOpenGLView(pEGLView);
        pDirector->replaceScene(pScene);
    }
}

void HelloWorld::getUI()
{
    uLayer = UILayer::create();
    addChild(uLayer);

    pWidget = GUIReader::shareReader()->widgetFromJsonFile("DeviceListPage_1.json");
    uLayer->addWidget(pWidget);

    pBtn_setting = dynamic_cast<Button*>(pWidget->getChildByTag(2)->getChildByTag(3));                      // setting button

    pListview_devices = dynamic_cast<ListView*>(pWidget->getChildByTag(4)->getChildByTag(7));               // listview

    pLayout_listAddItem = dynamic_cast<Layout*>(pWidget->getChildByTag(11));                                // It will add listview.

    pLayout_listFirstItem = dynamic_cast<Layout*>(pWidget->getChildByTag(11)->getChildByTag(12));           // 
    pLabel_name = dynamic_cast<Label*>(pWidget->getChildByTag(11)->getChildByTag(12)->getChildByTag(13));
    pLabel_ip = dynamic_cast<Label*>(pWidget->getChildByTag(11)->getChildByTag(12)->getChildByTag(14));
    pLabel_num = dynamic_cast<Label*>(pWidget->getChildByTag(11)->getChildByTag(12)->getChildByTag(15));

    pLayout_listSelectedItem = dynamic_cast<Layout*>(pWidget->getChildByTag(11)->getChildByTag(16));
    //pBtn_whatch = dynamic_cast<Button*>(pWidget->getChildByTag(11)->getChildByTag(16)->getChildByTag(17));
    //pBtn_search = dynamic_cast<Button*>(pWidget->getChildByTag(11)->getChildByTag(16)->getChildByTag(18));
    //pBtn_changeSet = dynamic_cast<Button*>(pWidget->getChildByTag(11)->getChildByTag(16)->getChildByTag(19));
    //pBtn_back = dynamic_cast<Button*>(pWidget->getChildByTag(11)->getChildByTag(16)->getChildByTag(20));
    
    pBtn_addDevice = dynamic_cast<Button*>(pWidget->getChildByTag(8)->getChildByTag(9));                    // device information add button
    pBtn_delDevice = dynamic_cast<Button*>(pWidget->getChildByTag(8)->getChildByTag(10));                   // device information delete button

    pBtn_addDevice->addTouchEventListener(this, toucheventselector(HelloWorld::selectBtnAddDevice));        // attach event listener at add button

    //pLayout_listFirstItem->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));
    //pLabel_name->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));

    //pLayout_listFirstItem->addTouchEventListener(this, toucheventselector(HelloWorld::touchListviewItem));
}

void HelloWorld::touchListviewItem(CCObject* pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN) {
        CCLog("클릭됐음\n");

        if(isClicked == true) {
            selectLayout->runAction(CCMoveBy::create(1, ccp(-480,0)));
        }
                
        selectLayout = dynamic_cast<Layout*>(pSender);

        // 현재 위치에서 1초 동안 오른쪽으로 480 만큼 이동.
        CCActionInterval* actRight = CCMoveBy::create(1, ccp(480,0));
        selectLayout->runAction(actRight);

        //Widget* newItem = pListview_devices->getItem(listview_count - 2);
        //Layout* secondItem = dynamic_cast<Layout*>(newItem->getChildByTag(16));


        //Button* name = dynamic_cast<Button*>(newItem->getChildByTag(16)->getChildByTag(17));
        //Button* ip = dynamic_cast<Button*>(newItem->getChildByTag(16)->getChildByTag(18));
        //Button* num = dynamic_cast<Button*>(newItem->getChildByTag(16)->getChildByTag(19));

        isClicked = true;
    }
}

void HelloWorld::touchBackButton(CCObject* pSender, TouchEventType type)
{
    if(type == TOUCH_EVENT_BEGAN) {

        //selectLayout = dynamic_cast<Button*>(pSender);

        // 현재 위치에서 1초 동안 왼쪽으로 480 만큼 이동.
        CCActionInterval* actLeft = CCMoveBy::create(1, ccp(-480,0));
        selectLayout->runAction(actLeft);

        isClicked = false;
    }
}


