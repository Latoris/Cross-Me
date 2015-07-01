#ifndef  _HELPSCENE_H_
#define _HELPSCENE_H_

#include <cocos2d.h>
#include <iostream>
USING_NS_CC;


class HelpScene: public Layer{
public:
	virtual bool init();
	static Scene* createScene();
	bool onTouchbegan(Touch *t, Event *e);
	CREATE_FUNC(HelpScene);

};

#endif

