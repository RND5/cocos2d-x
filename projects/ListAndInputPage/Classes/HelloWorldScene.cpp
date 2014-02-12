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
    /////	������ �ڵ�.
    /////
    ////////////////////////////////////////////////////////////////////////////////////

    // listview�� �ִ� ��Ұ� ���õ� �������� �˷���. ���� ���� �ȵǾ��� ������ false
    isClicked = false;

    getUI();                                                                        // json�� �ִ� gui�� ������.

    pListview_devices->setItemModel(pLayout_listAddItem);                           // listview�� �� ������ pLayout_listAddItem���� ����.

    //    std::vector<DeviceInformation> vecDeviceList;

    // device ��� ���������� ù �������� �ٽ� �Ѿ�� ��, vector�� �ʱ�ȭ ���ش�.
    vecDeviceList.clear();
    // json ���Ͽ� �ִ� device ������ �а� vector�� �ִ´�.
    deviceInfoIO.readJsonFile(vecDeviceList);           

    // listview�� �� ���� ������ ���� ���� ī����
    listview_count = 0;

    // vector ������ listview�� ����.
    for(std::vector<DeviceInformation>::iterator iter = vecDeviceList.begin(); iter < vecDeviceList.end(); iter++) {
        // listview�� �� ���� ������ ���� ���� ī����
        listview_count++;
        
        // vector�� ����� device ������ listview�� ���� ��ҵ鿡 ����        
        pLabel_name->setText(iter->getDeviceName());
        pLabel_ip->setText(iter->getIp());
                
        // int���� string���� ��ȯ�Ͽ� listview label�� �� ��°���� num�� ����. 
        std::ostringstream ostr;
        ostr.str("");
        ostr << listview_count;
        pLabel_num->setText(ostr.str().c_str());

        // listview�� device ���� �߰�
        pListview_devices->pushBackDefaultItem();

        // listview�� ����Ǵ� �����ۿ� �̺�Ʈ ����.
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


    /*                      �ѱ� ������ ���� ����
    char msg[128];

    WideCharToMultiByte(CP_UTF8, 0, L"����������", -1, msg, 128, NULL, NULL);

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
        CCLog("Ŭ������\n");

        if(isClicked == true) {
            selectLayout->runAction(CCMoveBy::create(1, ccp(-480,0)));
        }
                
        selectLayout = dynamic_cast<Layout*>(pSender);

        // ���� ��ġ���� 1�� ���� ���������� 480 ��ŭ �̵�.
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

        // ���� ��ġ���� 1�� ���� �������� 480 ��ŭ �̵�.
        CCActionInterval* actLeft = CCMoveBy::create(1, ccp(-480,0));
        selectLayout->runAction(actLeft);

        isClicked = false;
    }
}


