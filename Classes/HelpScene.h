#ifndef  _MYCPPGAME_HELPSCENE_H_
#define _MYCPPGAME_HELPSCENE_H_

#include <cocos2d.h>
#include <iostream>
USING_NS_CC;


class HelpScene: public Layer{
public:
	virtual bool init();
	static Scene* creatScene();
	bool onTouchbegan(Touch *t, Event *e);
	CREATE_FUNC(HelpScene);

};

#endif

