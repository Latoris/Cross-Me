#include "FirstGameScene.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "cocostudio\CocoStudio.h"
#include "SecondGameScene.h"
using namespace ui;

Scene* MenuScene::createScene(){
	Scene* scene = Scene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init(){
	auto nodemain = CSLoader::createNode("MenuScene.csb");
	this->addChild(nodemain);
	Button * map1button = (Button*)nodemain->getChildByName("Map1");
	map1button->addTouchEventListener(this, toucheventselector(MenuScene::playmap1));
	Button * map2button = (Button*)nodemain->getChildByName("Map2");
	map2button->addTouchEventListener(this, toucheventselector(MenuScene::playmap2));
	Button * backbutton = (Button*)nodemain->getChildByName("Back");
	backbutton->addTouchEventListener(this, toucheventselector(MenuScene::BackToWelcomeScene));
	return true;
}

void MenuScene::playmap1(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(FirstGameScene::createScene());
		break;
	}
}

void MenuScene::playmap2(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(SecondGameScene::createScene());
		break;
	}
}

void MenuScene::BackToWelcomeScene(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}