#ifndef _IN_GAME_LAYER_H_
#define _IN_GAME_LAYER_H_

#include "cocos2d.h"
#include "gameLayer/BackgroundLayer.h"
#include "gameObject/Hero.h"

#include "pools/FoodPool.h"
#include "pools/ObstaclePool.h"
#include "gameObject/Obstacle.h"

enum GAME_STATE
{
	STATE_WAIT	=	1000,
	STATE_READY,
	STATE_PLAY,
	STATE_OVER
};
enum MENU_TAG
{
   TAG_MENU_START	=	2000
};

enum FOOD_MODE
{
	MODE_VERTICAL = 3000,
	MODE_LINE,
	MODE_CICLE,
	MODE_WAVE,
	MODE_SPECIAL
};


class InGameLayer : public cocos2d::Layer
{
public:
	InGameLayer(void);
	~InGameLayer(void);

public:
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	CREATE_FUNC(InGameLayer);
public:
	static cocos2d::Scene* createScene();

private:
	
	void initView();
	void moveAllObject();
	void gameStep(float dt);
	void menuCallback(cocos2d::Ref* sender);
	void addEvent();

	void changeFoodMode();
	void createFood();
	void moveFood();
	void hitFoodTest();

	void createObstacle();
	void moveObstacle();
	void hitObstacle();

	void shakeWindows();
	

private:

	/* 游戏状态 */
	int state;
	/* 创建食物距离计数 */
	int modeDist;
	/* 创建食物当前模式 */
	int foodMode;
	/* 创建食物间隔计数 */
	int createGap;
	/* 英雄水平移动速度*/
	float heroSpeed;
	/*当前创建食物的布局坐标*/
	float curCreateX;
	float curCreateY;
	/*波浪型的弧度*/
	float waveRadians;
	/*特殊食物能量*/
	float coffeePower;
	float mushroomPower;
	/*分数*/
	int curDistCount;
	/*生命*/
	int life;
	/*障碍物创建距离*/
	float createObstacleDist;
	/*障碍物能量*/
	float obstaclePower;
	

	/** 水平创建指定间隙*/
	const int GAP_DIST_HORIZON;

	/** 垂直创建指定间隙*/
	const int GAP_DIST_VERTICAL;

	/** 1秒钟最小移动距离*/
	const int MOVE_MIN_SPEED;

	/** 1秒钟最大移动距离*/
	const int MOVE_MAX_SPEED;

	BackgroundLayer* mBackground;
	Hero* mHero;
	FoodPool  mFoodPool;
	ObstaclePool mObstaclePool;
	 
	cocos2d::Point touchPoint;
	cocos2d::Label* ttfLife;
	cocos2d::Label* ttfDistCount;
	cocos2d::Vector<Food*> foodList;
	cocos2d::Vector<Obstacle*> obstacleList;


};

#endif // !_IN_GAME_LAYER_H_