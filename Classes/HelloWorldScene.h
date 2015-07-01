#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;

class HelloWorld : public cocos2d::Layer
{
public:
	int bgm;
	MenuItemImage * soundOFF;
	MenuItemImage * soundON;
	MenuItemToggle* soundToggleMenu;
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	void play(Object* pSender, TouchEventType type);
	void help(Object* pSender, TouchEventType type);
	void exit(Object* pSender, TouchEventType type);
	void setmusic(Object* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
