#ifndef  _FIRSTGAMESCENE_H_
#define _FIRSTGAMESCENE_H_

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class FirstGameScene:public Layer{
public:
	Vec2 sizeofmap;
	bool returncondition;
	int input[10][10];//用户输入记录状态存储的数组
	int map[10][10];//地图数据

	virtual bool init();//主函数，用于初始化Scene
	static Scene* createScene();//创建Scene的函数

	void load();
	void initmap();//初始化地图函数
	void checkwinornot();//检查是否完成图像的函数
	
	void DeleteInput(Object* pSender, TouchEventType type);
	void BackToMenuScene(Object* pSender, TouchEventType type);
	bool onTouchbegan(Touch *t, Event *e);//触控监听函数
	
	CREATE_FUNC(FirstGameScene)
};

#endif