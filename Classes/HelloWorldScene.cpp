#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "HelpScene.h"

#include <cocostudio\CocoStudio.h>
#include "ui\CocosGUI.h"
using namespace ui;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto nodemain = CSLoader::createNode("MainScene.csb");
	this->addChild(nodemain);
	Button * playbutton = (Button*)nodemain->getChildByName("Button_1");
	playbutton->addTouchEventListener(this, toucheventselector(HelloWorld::play));
	Button * helpbutton = (Button*)nodemain->getChildByName("Help");
	helpbutton->addTouchEventListener(this, toucheventselector(HelloWorld::help));

	return true;
}

void HelloWorld::play(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		if (UserDefault::getInstance()->getBoolForKey("Return")){
			UserDefault::getInstance()->setBoolForKey("Return", false);//更改return为false表示返回界面完成
			UserDefault::getInstance()->flush();
			Director::getInstance()->popScene();
		}
		else
			Director::getInstance()->replaceScene(SecondScene::createScene());
		break;
	}
}

void HelloWorld::help(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(HelpScene::creatScene());
		break;
	}
}

void HelloWorld::exit(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		
		break;
	}
}