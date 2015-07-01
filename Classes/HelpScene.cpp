#include "HelpScene.h"
#include "HelloWorldScene.h"

Scene* HelpScene::createScene(){
	Scene* scene = Scene::create();
	HelpScene *layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init(){
	auto size = Director::getInstance()->getVisibleSize();
	auto helpscene = Sprite::create("HelpScene.png");
	helpscene->setPosition(size.width / 2.,size.height / 2);
	addChild(helpscene);
	auto touchListener = EventListenerTouchOneByOne::create();//Ìí¼Ó´¥¿Ø¼àÌýº¯Êý
	touchListener->onTouchBegan = CC_CALLBACK_2(HelpScene::onTouchbegan, this);//ÉèÖÃµ¥»÷»Øµ÷
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//×¢²á¼àÌýÆ÷
	return true;
}

bool HelpScene::onTouchbegan(Touch  *t, Event*e){
	Director::getInstance()->replaceScene(HelloWorld::createScene());
	return true;
}