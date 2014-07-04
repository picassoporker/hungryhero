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

	/* ��Ϸ״̬ */
	int state;
	/* ����ʳ�������� */
	int modeDist;
	/* ����ʳ�ﵱǰģʽ */
	int foodMode;
	/* ����ʳ�������� */
	int createGap;
	/* Ӣ��ˮƽ�ƶ��ٶ�*/
	float heroSpeed;
	/*��ǰ����ʳ��Ĳ�������*/
	float curCreateX;
	float curCreateY;
	/*�����͵Ļ���*/
	float waveRadians;
	/*����ʳ������*/
	float coffeePower;
	float mushroomPower;
	/*����*/
	int curDistCount;
	/*����*/
	int life;
	/*�ϰ��ﴴ������*/
	float createObstacleDist;
	/*�ϰ�������*/
	float obstaclePower;
	

	/** ˮƽ����ָ����϶*/
	const int GAP_DIST_HORIZON;

	/** ��ֱ����ָ����϶*/
	const int GAP_DIST_VERTICAL;

	/** 1������С�ƶ�����*/
	const int MOVE_MIN_SPEED;

	/** 1��������ƶ�����*/
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