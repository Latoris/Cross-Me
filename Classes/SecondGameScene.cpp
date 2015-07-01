#include "SecondGameScene.h"
#include "HelloWorldScene.h"
#include "MenuScene.h"

#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
using namespace ui;



Scene* SecondGameScene::createScene(){
	Scene* scene = Scene::create();
	SecondGameScene *layer = SecondGameScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondGameScene::init(){
	auto node = CSLoader::createNode("SecondGameScene.csb");
	this->addChild(node);
	node->setTag(160);
	Sprite* Map2 =(Sprite*) node->getChildByName("Map2");
	Button * deletebutton = (Button*)node->getChildByName("Button_2");
	deletebutton->addTouchEventListener(this, toucheventselector(SecondGameScene::Deleteinput2));
	Button * backbutton = (Button*)node->getChildByName("Button_3");
	backbutton->addTouchEventListener(this, toucheventselector(SecondGameScene::BackToMenuScene));

	auto size = Director::getInstance()->getVisibleSize();
	sizeofmap2.x = Map2->getPositionX();
	sizeofmap2.y = Map2->getPositionY();

	
	initmap();//���ó�ʼ������
	
	auto touchListener = EventListenerTouchOneByOne::create();//��Ӵ��ؼ�������
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondGameScene::onTouchbegan, this);//���õ����ص�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע�������



	return true;
}

void SecondGameScene::initmap(){
	if (!UserDefault::getInstance()->getBoolForKey("FirstExitMap2")){
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* input2s= String::createWithFormat("input2_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(input2s->getCString(), 0);//��UserDefault�´洢����Ϊ0
				input2[i][j] = 0;	//��ʼ��Ϊ�հ׵�ͼ
			}
		}
		UserDefault::getInstance()->setBoolForKey("FirstExitMap2", true);
		UserDefault::getInstance()->flush();//��FirstExitֵ��Ϊfalse
	}
	
	//�ж��Ƿ����˳���Ϸ�����½���
	if (UserDefault::getInstance()->getBoolForKey("ExitMap2")==true){
		load();
	}
	map2[9][5] = map2[9][6] = map2[9][7] = map2[9][8] = map2[8][4] = map2[8][5] = map2[8][6] = 1;
	for (int i = 2; i < 7; i++)
		map2[7][i] = 1;
	for (int i = 1; i < 8; i++)
		map2[6][i] = 1;
	map2[6][9] = 1;
	map2[5][1] = 1;
	for (int i = 3; i < 10; i++)
		map2[5][i] = 1;
	map2[4][0] = map2[4][1] = map2[4][3] = map2[4][5] = map2[4][6] = map2[4][7] = map2[4][8] = map2[4][9] = 1;
	map2[3][0] = map2[3][1] = map2[3][2] = map2[3][3] = map2[3][6] = map2[3][7] = map2[3][8] = map2[3][9] = map2[3][5] = 1;
	map2[2][1] = map2[2][2] = map2[2][4] = map2[2][5] = map2[2][6] = map2[2][7] = map2[2][9] = 1;
	map2[1][4] = map2[1][2] = map2[1][3] = map2[1][5] = map2[1][9] = 1;
	map2[0][4] = map2[0][5] = map2[0][6] = map2[0][7] = 1;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (map2[i][j] != 1)
				map2[i][j] = 0;
		}
	}
	//�ֶ�������ͼ���λ��
}

bool SecondGameScene::onTouchbegan(Touch *t, Event *e){
	auto size1 = Director::getInstance()->getVisibleSize();
	Rect rect(0, 0, 26, 26);
	int a[10][10] = { 0 };//�����洢tag������
	auto location = t->getLocation();//��ȡ��ǰ����������
	//����ÿ�������жϵ�ǰ���ص��ǲ����ھ��η�Χ��
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
		
		//�����������������趨�ж����ε�x, y
			if (j > 4)
				rect.origin.x = sizeofmap2.x+ 2 + (j - 5) * 28;
			else
				rect.origin.x = sizeofmap2.x - (5 - j) * 28;
			if (i > 4)
				rect.origin.y = sizeofmap2.y + 2 + (i - 5) * 28;
			else
				rect.origin.y = sizeofmap2.y - (5 - i) * 28;
			if (rect.containsPoint(location)){
				if (input2[i][j] == 0){
					auto black = Sprite::create("rect.png");//�жϵ�ǰ���ζ�Ӧ��״̬�����Ϊ0Ҳ���ǵ�ǰû����䣬����غ�ɫ���飬����ɾ����
					black->setPosition(rect.origin.x+13, rect.origin.y+13);//�����ڼ���ͬʱ��¼��Ӧ״̬���ж��Ƿ����ͼ��
					addChild(black,1, i*10+j);
					input2[i][j] = 1;
					log("input2[%d][%d] =%d map2[%d][%d] = %d", i, j, input2[i][j], i, j, map2[i][j]);
					checkwinornot();
				}
				else if(input2[i][j] == 1){
					this->removeChildByTag(i * 10 + j, 1);//��Ӧtagɾ����ɫ���鲢���ϱ���õ�
					auto mind = Sprite::create("flag.png");
					mind->setPosition(rect.origin.x+13, rect.origin.y+13);
					addChild(mind, 1, i * 10 + j);
					input2[i][j] = 2;
					log("input2[%d][%d] =%d map2[%d][%d] = %d", i, j, input2[i][j], i, j, map2[i][j]);
					checkwinornot();
				}
				else{
					this->removeChildByTag(i * 10 + j, 1);//��Ӧtagɾ������
					input2[i][j] = 0;
					log("input2[%d][%d] =%d map2[%d][%d] = %d", i, j, input2[i][j], i, j, map2[i][j]);
					checkwinornot();
				}
		}
	}
	return true;
}

void SecondGameScene::checkwinornot(){
	int flag = 0;
	for (int i = 0; i < 10; i++){
		if (flag == 1)
			break;
		for (int j = 0; j < 10; j++){
			if (input2[i][j] == 1 && map2[i][j] != 1){
				flag = 1;
				log("input2[%d][%d] = %d,  map2[%d][%d] = %d, failed", i, j, input2[i][j], i, j, map2[i][j]);
				break;//�ж��û�����ĵ�ͼ����ȷ���Ƿ�һ�£���һ��������ѭ��
			}
			else if (input2[i][j] == 0 && map2[i][j] == 1){
				flag = 1;
				log("input2[%d][%d] = %d,  map2[%d][%d] = %d, failed", i, j, input2[i][j], i, j, map2[i][j]);
				break;
			}
			else if (input2[i][j] == 2 && map2[i][j] == 1){
				flag = 1;
				log("input2[%d][%d] = %d,  map2[%d][%d] = %d, failed", i, j, input2[i][j], i, j, map2[i][j]);
				break;
			}
		}
	}
	if (flag == 0){
		MessageBox("You complete this image", "Congrulation");//����һ��ѭ��û�иı�flag��ֵ��˵����һ�£�������Ϸ��ɣ������Ի���
	}
}

void SecondGameScene::Deleteinput2(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++){
				if (input2[i][j] != 0){
					input2[i][j] = 0;
					this->removeChildByTag(i * 10 + j, 1);
				}
			}
		break;
	}
}

void SecondGameScene::BackToMenuScene(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* getinput2 = String::createWithFormat("input2_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(getinput2->getCString(), input2[i][j]);//����ǰ���ݴ洢��xml�ļ���
			}
		}
		UserDefault::getInstance()->setBoolForKey("ExitMap2", true);
		UserDefault::getInstance()->flush();
		
		Director::getInstance()->replaceScene(MenuScene::createScene());
		break;
	}
}

void SecondGameScene::load(){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			String* getinput2 = String::createWithFormat("input2_%d_%d", i, j);
			input2[i][j] = UserDefault::getInstance()->getIntegerForKey(getinput2->getCString());
		}
	}
	Rect rect(0, 0, 26, 26);
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			//�����������������趨�ж����ε�x, y
			if (j > 4)
				rect.origin.x = sizeofmap2.x + 2 + (j - 5) * 28;
			else
				rect.origin.x = sizeofmap2.x - (5 - j) * 28;
			if (i > 4)
				rect.origin.y = sizeofmap2.y + 2 + (i - 5) * 28;
			else
				rect.origin.y = sizeofmap2.y - (5 - i) * 28;
			if (input2[i][j] == 1){
				auto black = Sprite::create("rect.png");
				black->setPosition(rect.origin.x + 13, rect.origin.y + 13);
				addChild(black, 1, i * 10 + j);
			}
			else if (input2[i][j] == 2){
				auto mind = Sprite::create("flag.png");
				mind->setPosition(rect.origin.x + 13, rect.origin.y + 13);
				addChild(mind, 1, i * 10 + j);
				input2[i][j] = 2;
			}
		}
	}
}