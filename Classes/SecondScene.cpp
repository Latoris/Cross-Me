#include "SecondScene.h"
#include "HelloWorldScene.h"

#include <cocostudio\CocoStudio.h>
#include "ui\CocosGUI.h"
using namespace ui;



Scene* SecondScene::createScene(){
	Scene* scene = Scene::create();
	SecondScene *layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init(){
	auto node = CSLoader::createNode("GameScene.csb");
	this->addChild(node);
	auto size = Director::getInstance()->getVisibleSize();
	Sprite* map2 =(Sprite*) node->getChildByName("Map2");
	sizeofmap.x = map2->getPositionX();
	sizeofmap.y = map2->getPositionY();
	Button * deletebutton = (Button*)node->getChildByName("Button_2");
	deletebutton->addTouchEventListener(this, toucheventselector(SecondScene::DeleteInput));
	Button * backbutton = (Button*)node->getChildByName("Button_3");
	backbutton->addTouchEventListener(this, toucheventselector(SecondScene::BackToMainScene));

	
	initmap();//���ó�ʼ������

	auto touchListener = EventListenerTouchOneByOne::create();//��Ӵ��ؼ�������
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondScene::onTouchbegan, this);//���õ����ص�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע�������



	return true;
}

void SecondScene::initmap(){
	//�ж��Ƿ����FirstExitֵ������������е�һ�εĵ�ͼ��ʼ��
	if (UserDefault::getInstance()->getBoolForKey("FirstExit")==true){
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* inputs= String::createWithFormat("input_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(inputs->getCString(), 0);//��UserDefault�´洢����Ϊ0
				input[i][j] = 0;	//��ʼ��Ϊ�հ׵�ͼ
			}
		}
		UserDefault::getInstance()->setBoolForKey("FirstExit", false);
		UserDefault::getInstance()->flush();//��FirstExitֵ��Ϊfalse
	}
	
	//�ж��Ƿ����˳���Ϸ�����½���
	if (UserDefault::getInstance()->getBoolForKey("Exit")==true){
		load();
	}
	map[3][9] = map[4][9] = map[2][8] = map[4][8] = 1;
	map[1][7] = map[2][7] = map[3][7] = map[0][6] = map[2][6] = map[3][6] = 1;
	for (int i = 0; i < 8; i++)
		map[i][5] = 1;
	for (int i = 0; i < 9; i++)
		map[i][4] = 1;
	for (int i = 1; i < 10; i++)
		map[i][3] = 1;
	for (int i = 2; i < 9; i++)
		map[i][2] = 1;
	map[1][1] = map[2][1] = map[3][1] = map[6][1] = map[7][1] = map[8][1] = 1;
	map[0][0] = map[1][0] = map[2][0] = map[4][0] = map[5][0] = map[6][0] = map[7][0] = 1;
	//�ֶ�������ͼ���λ��
}

bool SecondScene::onTouchbegan(Touch *t, Event *e){
	auto size1 = Director::getInstance()->getVisibleSize();
	Rect rect(0, 0, 26, 26);
	int a[10][10] = { 0 };//�����洢tag������
	auto location = t->getLocation();//��ȡ��ǰ����������
	//����ÿ�������жϵ�ǰ���ص��ǲ����ھ��η�Χ��
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
		
		//�����������������趨�ж����ε�x, y
			if (j > 4)
				rect.origin.x = sizeofmap.x+ 2 + (j - 5) * 28;
			else
				rect.origin.x = sizeofmap.x - (5 - j) * 28;
			if (i > 4)
				rect.origin.y = sizeofmap.y + 2 + (i - 5) * 28;
			else
				rect.origin.y = sizeofmap.y - (5 - i) * 28;
			if (rect.containsPoint(location)){
				if (input[i][j] == 0){
					auto black = Sprite::create("rect.png");//�жϵ�ǰ���ζ�Ӧ��״̬�����Ϊ0Ҳ���ǵ�ǰû����䣬����غ�ɫ���飬����ɾ����
					black->setPosition(rect.origin.x+13, rect.origin.y+13);//�����ڼ���ͬʱ��¼��Ӧ״̬���ж��Ƿ����ͼ��
					addChild(black,1, i*10+j);
					input[i][j] = 1;
					log("i = %d j = %d  input = %d", i, j,  input[i][j]);
					checkwinornot();
				}
				else if(input[i][j] == 1){
					this->removeChildByTag(i * 10 + j, 1);//��Ӧtagɾ����ɫ���鲢���ϱ���õ�
					auto mind = Sprite::create("flag.png");
					mind->setPosition(rect.origin.x+13, rect.origin.y+13);
					addChild(mind, 1, i * 10 + j);
					input[i][j] = 2;
					log("i = %d j = %d  input = %d", i, j, input[i][j]);
					checkwinornot();
				}
				else{
					this->removeChildByTag(i * 10 + j, 1);//��Ӧtagɾ������
					input[i][j] = 0;
					log("i = %d j = %d  input = %d", i, j, input[i][j]);
					checkwinornot();
				}
		}
	}
	return true;
}

void SecondScene::checkwinornot(){
	int flag = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			if (input[i][j] == 1 && map[i][j] != 1){
				flag = 1;
				break;//�ж��û�����ĵ�ͼ����ȷ���Ƿ�һ�£���һ��������ѭ��
			}
			else if (input[i][j] == 0 && map[i][j] == 1){
				flag = 1;
				break;
			}
			else if (input[i][j] == 2 && map[i][j] == 1){
				flag = 1;
				break;;
			}
		}
	}
	if (flag == 0)
		MessageBox("You complete this image", "Congrulation");//����һ��ѭ��û�иı�flag��ֵ��˵����һ�£�������Ϸ��ɣ������Ի���
}

void SecondScene::DeleteInput(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		Director::getInstance()->replaceScene(SecondScene::createScene());
		break;
	}
}

void SecondScene::BackToMainScene(Object* pSender, TouchEventType type){
	switch (type){
	case TOUCH_EVENT_BEGAN:
		UserDefault::getInstance()->setBoolForKey("Return", true);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* getinput = String::createWithFormat("input_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(getinput->getCString(), input[i][j]);
			}
		}
		UserDefault::getInstance()->flush();
		
		Director::getInstance()->pushScene(HelloWorld::createScene());
		//Director::getInstance()->replaceScene(HelloWorld::createScene());
		break;
	}
}

void SecondScene::load(){
	//auto size1 = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			String* getinput = String::createWithFormat("input_%d_%d", i, j);
			input[i][j] = UserDefault::getInstance()->getIntegerForKey(getinput->getCString());
		}
	}
	Rect rect(0, 0, 26, 26);
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			//�����������������趨�ж����ε�x, y
			if (j > 4)
				rect.origin.x = sizeofmap.x + 2 + (j - 5) * 28;
			else
				rect.origin.x = sizeofmap.x - (5 - j) * 28;
			if (i > 4)
				rect.origin.y = sizeofmap.y + 2 + (i - 5) * 28;
			else
				rect.origin.y = sizeofmap.y - (5 - i) * 28;
			if (input[i][j] == 1){
				auto black = Sprite::create("rect.png");
				black->setPosition(rect.origin.x + 13, rect.origin.y + 13);
				addChild(black, 1, i * 10 + j);
				log("i = %d j = %d  input = %d", i, j, input[i][j]);
			}
			else if (input[i][j] == 2){
				auto mind = Sprite::create("flag.png");
				mind->setPosition(rect.origin.x + 13, rect.origin.y + 13);
				addChild(mind, 1, i * 10 + j);
				input[i][j] = 2;
				log("i = %d j = %d  input = %d", i, j, input[i][j]);
			}
		}
	}
}