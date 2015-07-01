#include "HelloWorldScene.h"
#include "HelpScene.h"
#include "MenuScene.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "AudioEngine.h"

using namespace ui;
using namespace experimental;



Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
	scene->addChild(layer);
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
	//��ȡCocos studio����Դ�Լ��ӽڵ�
	auto nodemain = CSLoader::createNode("WelcomeScene.csb");
	this->addChild(nodemain);
	Button * playbutton = (Button*)nodemain->getChildByName("Play");
	playbutton->addTouchEventListener(this, toucheventselector(HelloWorld::play));
	Button * helpbutton = (Button*)nodemain->getChildByName("Help");
	helpbutton->addTouchEventListener(this, toucheventselector(HelloWorld::help));
	Button * exitbutton = (Button*)nodemain->getChildByName("Exit");
	exitbutton->addTouchEventListener(this, toucheventselector(HelloWorld::exit));
	//�����һ�ν�����ִ�����³�ʼ��
	if (!UserDefault::getInstance()->getBoolForKey("exit")){
		UserDefault::getInstance()->setBoolForKey("bgmset", true);
		UserDefault::getInstance()->setBoolForKey("bgmplay", false);
		UserDefault::getInstance()->setBoolForKey("exit", true);
		UserDefault::getInstance()->flush();
	}
	//������ǵ�һ�Σ��ж����������Ƿ񿪿������򲥷�����
	if (UserDefault::getInstance()->getBoolForKey("bgmplay") == false && UserDefault::getInstance()->getBoolForKey("bgmset") == true){
		UserDefault::getInstance()->setBoolForKey("bgmplay", true);
		UserDefault::getInstance()->setIntegerForKey("bgm", AudioEngine::play2d("heart melody.mp3", true, 1.0));
		UserDefault::getInstance()->flush();
	}
	//�������ð�ť��ʵ��
	soundOFF = MenuItemImage::create("Button/MusicButton.png", "Button/MusicButtonClick.png");
	soundON = MenuItemImage::create("Button/MusicButton2.png", "Button/MusicButton2Click.png");
	if (UserDefault::getInstance()->getBoolForKey("bgmset") == true)
		soundToggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::setmusic, this), soundOFF, soundON, NULL);
	else
		soundToggleMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::setmusic, this), soundON, soundOFF, NULL);
	auto musicmenu = Menu::create(soundToggleMenu, NULL);
	musicmenu->setPosition(647.8, 67.11);
	this->addChild(musicmenu);
	
	return true;
}

void HelloWorld::play(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
			Director::getInstance()->replaceScene(MenuScene::createScene());
		break;
	}
}

void HelloWorld::help(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(HelpScene::createScene());
		break;
	}
}

void HelloWorld::exit(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		UserDefault::getInstance()->setBoolForKey("bgmplay", false);
		UserDefault::getInstance()->flush();
		AudioEngine::stopAll();
		AudioEngine::end();
		Director::getInstance()->end();
		break;
	}
}

/*�������ð�ť�ĺ���*/
void HelloWorld::setmusic(Object* pSender){
	//ת����ǰ��objectΪmenuitemtoggle���󷽱��жϰ�����ʲô��ť
	MenuItemToggle *to = (MenuItemToggle*)pSender;
	if (to->selectedItem() == soundON){
		//������ԭ����ON��״̬����һ���Ժ�ر����ֲ�����������Ϊ������
		UserDefault::getInstance()->setBoolForKey("bgmset", false);
		AudioEngine::stop(UserDefault::getInstance()->getIntegerForKey("bgm"));
		UserDefault::getInstance()->setBoolForKey("bgmplay", false);
		UserDefault::getInstance()->flush();
	}
	else if(to->selectedItem() == soundOFF){
		UserDefault::getInstance()->setBoolForKey("bgmset", true);
		UserDefault::getInstance()->setIntegerForKey("bgm", AudioEngine::play2d("heart melody.mp3", true, 1.0));
		UserDefault::getInstance()->setBoolForKey("bgmplay", true);
		UserDefault::getInstance()->flush();
	}
}