#ifndef  _MENUSCENE_H_
#define _MENUSCENE_H_


#include "cocos2d.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;


class MenuScene: public Layer{
public:
	virtual bool init();
	static Scene* createScene();
	void playmap1(Object* pSender, TouchEventType type);
	void playmap2(Object* pSender, TouchEventType type);
	void BackToWelcomeScene(Object* pSender, TouchEventType type);
	CREATE_FUNC(MenuScene);

};

#endif

