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

	
	initmap();//调用初始化函数
	
	auto touchListener = EventListenerTouchOneByOne::create();//添加触控监听函数
	touchListener->onTouchBegan = CC_CALLBACK_2(SecondGameScene::onTouchbegan, this);//设置单击回调
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册监听器



	return true;
}

void SecondGameScene::initmap(){
	if (!UserDefault::getInstance()->getBoolForKey("FirstExitMap2")){
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
				String* input2s= String::createWithFormat("input2_%d_%d", i, j);
				UserDefault::getInstance()->setIntegerForKey(input2s->getCString(), 0);//在UserDefault下存储数组为0
				input2[i][j] = 0;	//初始化为空白地图
			}
		}
		UserDefault::getInstance()->setBoolForKey("FirstExitMap2", true);
		UserDefault::getInstance()->flush();//将FirstExit值改为false
	}
	
	//判断是否在退出游戏后重新进入
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
	//手动输入有图像的位置
}

bool SecondGameScene::onTouchbegan(Touch *t, Event *e){
	auto size1 = Director::getInstance()->getVisibleSize();
	Rect rect(0, 0, 26, 26);
	int a[10][10] = { 0 };//声明存储tag的数组
	auto location = t->getLocation();//获取当前触摸点坐标
	//遍历每个矩形判断当前触控点是不是在矩形范围内
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++){
		
		//根据所在行所在列设定判定矩形的x, y
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
					auto black = Sprite::create("rect.png");//判断当前矩形对应的状态，如果为0也就是当前没有填充，则加载黑色方块，有则删除。
					black->setPosition(rect.origin.x+13, rect.origin.y+13);//并且在加载同时记录对应状态并判断是否完成图像
					addChild(black,1, i*10+j);
					input2[i][j] = 1;
					log("input2[%d][%d] =%d map2[%d][%d] = %d", i, j, input2[i][j], i, j, map2[i][j]);
					checkwinornot();
				}
				else if(input2[i][j] == 1){
					this->removeChildByTag(i * 10 + j, 1);//对应tag删除黑色方块并换上标记用的
					auto mind = Sprite::create("flag.png");
					mind->setPosition(rect.origin.x+13, rect.origin.y+13);
					addChild(mind, 1, i * 10 + j);
					input2[i][j] = 2;
					log("input2[%d][%d] =%d map2[%d][%d] = %d", i, j, input2[i][j], i, j, map2[i][j]);
					checkwinornot();
				}
				else{
					this->removeChildByTag(i * 10 + j, 1);//对应tag删除精灵
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
				break;//判断用户输入的地图和正确的是否一致，不一致则跳出循环
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
		MessageBox("You complete this image", "Congrulation");//若上一个循环没有改变flag的值则说明都一致，所以游戏完成，弹出对话框
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
				UserDefault::getInstance()->setIntegerForKey(getinput2->getCString(), input2[i][j]);//将当前数据存储在xml文件中
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
			//根据所在行所在列设定判定矩形的x, y
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