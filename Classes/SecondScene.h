#ifndef  _MYCPPGAME_SECONDSECNE_H_
#define _MYCPPGAME_SECONDSECNE_H_

#include <cocostudio\CocoStudio.h>
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class SecondScene:public Layer{
public:
	Vec2 sizeofmap;
	bool returncondition;
	int input[10][10];//�û������¼״̬�洢������
	int map[10][10];//��ͼ����

	virtual bool init();//�����������ڳ�ʼ��Scene
	static Scene* createScene();//����Scene�ĺ���

	void load();
	void initmap();//��ʼ����ͼ����
	void checkwinornot();//����Ƿ����ͼ��ĺ���
	
	void DeleteInput(Object* pSender, TouchEventType type);
	void BackToMainScene(Object* pSender, TouchEventType type);
	bool onTouchbegan(Touch *t, Event *e);//���ؼ�������
	
	CREATE_FUNC(SecondScene)
};

#endif