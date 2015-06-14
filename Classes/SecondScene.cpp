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

	
	initmap();//调用初始化函数

	auto touchListener = EventListenerTouchOneByOne::create();//添加触控监听函数
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondScene::onTouchbegan, this);//设置单击回调
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册监听器



	return true;
}

void SecondScene::initmap(){
	//判断是否存在FirstExit值，不存在则进行第一次的地图初始化
	if (UserDefault::getInstance()->getBoolForKey("FirstExit")==true){
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* inputs= String::createWithFormat("input_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(inputs->getCString(), 0);//在UserDefault下存储数组为0
				input[i][j] = 0;	//初始化为空白地图
			}
		}
		UserDefault::getInstance()->setBoolForKey("FirstExit", false);
		UserDefault::getInstance()->flush();//将FirstExit值改为false
	}
	
	//判断是否在退出游戏后重新进入
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
	//手动输入有图像的位置
}

bool SecondScene::onTouchbegan(Touch *t, Event *e){
	auto size1 = Director::getInstance()->getVisibleSize();
	Rect rect(0, 0, 26, 26);
	int a[10][10] = { 0 };//声明存储tag的数组
	auto location = t->getLocation();//获取当前触摸点坐标
	//遍历每个矩形判断当前触控点是不是在矩形范围内
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
		
		//根据所在行所在列设定判定矩形的x, y
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
					auto black = Sprite::create("rect.png");//判断当前矩形对应的状态，如果为0也就是当前没有填充，则加载黑色方块，有则删除。
					black->setPosition(rect.origin.x+13, rect.origin.y+13);//并且在加载同时记录对应状态并判断是否完成图像
					addChild(black,1, i*10+j);
					input[i][j] = 1;
					log("i = %d j = %d  input = %d", i, j,  input[i][j]);
					checkwinornot();
				}
				else if(input[i][j] == 1){
					this->removeChildByTag(i * 10 + j, 1);//对应tag删除黑色方块并换上标记用的
					auto mind = Sprite::create("flag.png");
					mind->setPosition(rect.origin.x+13, rect.origin.y+13);
					addChild(mind, 1, i * 10 + j);
					input[i][j] = 2;
					log("i = %d j = %d  input = %d", i, j, input[i][j]);
					checkwinornot();
				}
				else{
					this->removeChildByTag(i * 10 + j, 1);//对应tag删除精灵
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
				break;//判断用户输入的地图和正确的是否一致，不一致则跳出循环
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
		MessageBox("You complete this image", "Congrulation");//若上一个循环没有改变flag的值则说明都一致，所以游戏完成，弹出对话框
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
			//根据所在行所在列设定判定矩形的x, y
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