#ifndef  _SECONDGAMESECNE_H_
#define _SECONDGAMESECNE_H_

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class SecondGameScene:public Layer{
public:
	Vec2 sizeofmap2;
	int input2[10][10];//�û������¼״̬�洢������
	int map2[10][10];//��ͼ����

	virtual bool init();//�����������ڳ�ʼ��Scene
	static Scene* createScene();//����Scene�ĺ���

	void load();
	void initmap();//��ʼ����ͼ����
	void checkwinornot();//����Ƿ����ͼ��ĺ���
	
	void Deleteinput2(Object* pSender, TouchEventType type);
	void BackToMenuScene(Object* pSender, TouchEventType type);
	bool onTouchbegan(Touch *t, Event *e);//���ؼ�������
	
	CREATE_FUNC(SecondGameScene)
};

#endif