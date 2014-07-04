#include "gameLayer/InGameLayer.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

InGameLayer::InGameLayer(void) :	GAP_DIST_HORIZON(30),
									GAP_DIST_VERTICAL(30),
									MOVE_MIN_SPEED(15),
									MOVE_MAX_SPEED(30),
									mBackground(NULL),
									ttfLife(NULL),
									ttfDistCount(NULL),
									mHero(NULL),
									foodMode(MODE_LINE),
									state(STATE_WAIT),
									touchPoint(),
									modeDist(300),
									createGap(30),
									heroSpeed(10),
									curCreateX(1100),
									curCreateY(200),
									foodList(),
									mFoodPool(),
									waveRadians(0),
									coffeePower(0),
									mushroomPower(0),
									curDistCount(0),
									life(3),
									obstacleList(),
									createObstacleDist(300),
									obstaclePower(3),
									mObstaclePool()

{
}


InGameLayer::~InGameLayer(void)
{
}

Scene* InGameLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = InGameLayer::create();
	sc->addChild(ly);
	return sc;
}

bool InGameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	srand(time(NULL));

	mFoodPool.init();
	mObstaclePool.init();

	initView();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgWelcome.mp3",true);

	this->schedule(SEL_SCHEDULE(&InGameLayer::gameStep),0.02f);

	return true;
}

void InGameLayer::initView()
{
	mBackground		=	BackgroundLayer::create();
	this->addChild(mBackground,0);
	mBackground->setAnchorPoint(Point::ZERO);

	auto spStartNor	=	Sprite::createWithSpriteFrameName("startButton.png");
	auto spStartSel	=	Sprite::createWithSpriteFrameName("startButton.png");
	spStartSel->setScale(0.8f);
	auto itemStart	=	MenuItemSprite::create(spStartNor,spStartSel,NULL,CC_CALLBACK_1(InGameLayer::menuCallback,this));
	itemStart->setTag(TAG_MENU_START);

	auto menuStart	=	Menu::create(itemStart,NULL);
	this->addChild(menuStart,1);

	//Ó¢ÐÛ
	mHero			=	Hero::create();
	this->addChild(mHero,2);
	mHero->setPosition(VisibleRect::left() - Point(150,0));

	ttfDistCount	=	Label::createWithBMFont("fonts/labelFont.fnt","DISTANCE 0",TextHAlignment::LEFT);
	this->addChild(ttfDistCount,3);
	ttfDistCount->setVerticalAlignment(TextVAlignment::CENTER);
	ttfDistCount->setHorizontalAlignment(TextHAlignment::LEFT);
	ttfDistCount->setAnchorPoint(Point(0,0.5f));
	ttfDistCount->setPositionX(VisibleRect::rightTop().x - 350);
	ttfDistCount->setPositionY(VisibleRect::rightTop().y - 50);

	ttfLife			=	Label::createWithBMFont("fonts/labelFont.fnt","LIVE 0",TextHAlignment::LEFT);
	this->addChild(ttfLife,3);
	ttfLife->setVerticalAlignment(TextVAlignment::CENTER);
	ttfLife->setHorizontalAlignment(TextHAlignment::LEFT);
	ttfLife->setAnchorPoint(Point(0,0.5f));
	ttfLife->setPositionX(VisibleRect::top().x);
	ttfLife->setPositionY(VisibleRect::top().y - 50);
}

void InGameLayer::gameStep(float dt)
{
	//Ó¢ÐÛ³ö³¡µã
	Point toPoint	=	Point(VisibleRect::center().x / 3 * 2,mHero->getPositionY());

	switch (state)
	{
	case STATE_WAIT:
		break;

	case STATE_READY:

		mHero->show(toPoint);

		if(mHero->getPositionX() >= toPoint.x - 5)
		{
			mHero->setPosition(toPoint);
			touchPoint	=	toPoint;
			state	=	STATE_PLAY;

			addEvent();
		}
		break;

	case STATE_PLAY:

		if(coffeePower > 0)
		{
			heroSpeed	=	MOVE_MAX_SPEED;
			coffeePower	-=	0.1;
		}else
		{
			heroSpeed	=	MOVE_MIN_SPEED;
			coffeePower	=	0;
		}

		moveAllObject();
		changeFoodMode();
		createFood();
		moveFood();
		hitFoodTest();

		createObstacle();
		moveObstacle();
		hitObstacle();

		shakeWindows();

		break;

	case STATE_OVER:
		break;

	}

}

void InGameLayer::moveAllObject()
{
	curDistCount++;
	char chDist[120];
	sprintf(chDist,"DISTANCE %d",curDistCount);
	ttfDistCount->setString(chDist);

	mBackground->setVx(heroSpeed);
	mBackground->move();

	if(obstaclePower > 0)
	{
		mHero->rotate(12.12f);
		touchPoint	=	mHero->getPosition();
	}
	else
		mHero->moveTo(touchPoint);
}

void InGameLayer::menuCallback(cocos2d::Ref* sender)
{
	state					=	STATE_READY;
	MenuItemSprite* item	=	(MenuItemSprite*)sender;
	if(TAG_MENU_START == item->getTag())
	{
		item->setVisible(false);
	}
}

void InGameLayer::addEvent()
{
	auto touchEvent				=	EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan	=	CC_CALLBACK_2(InGameLayer::onTouchBegan,this);
	touchEvent->onTouchMoved	=	CC_CALLBACK_2(InGameLayer::onTouchMoved,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent,this);
}

bool InGameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	return true;
}
void InGameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	touchPoint	=	touch->getLocation();
}

void InGameLayer::changeFoodMode()
{
	if (modeDist >= 0)
	{
		modeDist--;
	}else
	{
		
		foodMode		=	int(CCRANDOM_0_1() * 5) + MODE_VERTICAL;
		log("change mode:%d",foodMode);
		if(MODE_VERTICAL == foodMode)
		{
			modeDist	=	CCRANDOM_0_1() * 200 + 50;	
		}else if(MODE_LINE == foodMode)
		{
			modeDist	=	CCRANDOM_0_1() * 100 + 50;	
		}else if(MODE_CICLE == foodMode)
		{
			modeDist	=	CCRANDOM_0_1() * 100 + 100;	
		}else if(MODE_WAVE == foodMode)
		{
			modeDist	=	CCRANDOM_0_1() * 200 + 20;	
		}else if(MODE_SPECIAL == foodMode)
		{
			modeDist	=	CCRANDOM_0_1() * 20 + 20;
		}
	}
}
void InGameLayer::createFood()
{
	Food* getFood	=	NULL;
	int type		=	0;
	int count		=	0;

	if (createGap > 0)
	{
		createGap--;
	}else
	{
		createGap = 30;

		if(MODE_WAVE == foodMode)
		{
			curCreateX		=	VisibleRect::right().x + 50;
			curCreateY		=	CCRANDOM_0_1() * (VisibleRect::top().y - 300) + 150;
			count		=	CCRANDOM_0_1() * 30 + 30;
			for (int i = 0; i < count; i++)
			{
				type		=	CCRANDOM_0_1() * 5 + 1;
				getFood		=	mFoodPool.takeOut();
				getFood->setType(type);
				getFood->setPositionX(curCreateX);
				getFood->setPositionY(curCreateY);
				this->addChild(getFood,4);

				waveRadians	+=	0.3f;
				curCreateX	+=	GAP_DIST_HORIZON;
				curCreateY	+=	sin(waveRadians) * GAP_DIST_VERTICAL;
				foodList.pushBack(getFood);

				type		=	CCRANDOM_0_1() * 5 + 1;
				getFood		=	mFoodPool.takeOut();
				getFood->setType(type);
				getFood->setPositionX(curCreateX);
				getFood->setPositionY(curCreateY + 150);
				this->addChild(getFood,4);
				foodList.pushBack(getFood);
			}
			
		}else if(MODE_CICLE == foodMode)
		{
			count			=	CCRANDOM_0_1() * 60 + 50;
			curCreateX		=	VisibleRect::right().x + 150;
			curCreateY		=	CCRANDOM_0_1() * (VisibleRect::top().y - 300) + 150;
			float angle		=	15;
			for (int i = 0; i < count; i++)
			{
				type		=	CCRANDOM_0_1() * 5 + 1;
				getFood		=	mFoodPool.takeOut();
				getFood->setType(type);
				
				this->addChild(getFood,4);
				foodList.pushBack(getFood);
				angle		+=	30;
				
				float x		=	cos(angle * M_PI / 180) * (GAP_DIST_HORIZON + (count - i));
				float y		=	sin(angle * M_PI / 180) * (GAP_DIST_VERTICAL + (count - i));
				getFood->setPositionX(curCreateX + x);
				getFood->setPositionY(curCreateY + y);

				/*
				ðÐðÄÂÝ
				float y		=	sin(angle * M_PI / 180) * (GAP_DIST_VERTICAL * (i / 18 + 1));
				float x		=	cos(angle * M_PI / 180) * (GAP_DIST_HORIZON * (i / 18 + 1));
 				if ( i / 18 != (i-1) / 18)
 				{
 					x += 	 cos(angle * M_PI / 180) * (GAP_DIST_HORIZON);
 
 				}
				*/
			}
		}else if (MODE_LINE == foodMode)
		{
			count			=	CCRANDOM_0_1() * 5 + 5;
			curCreateX		=	VisibleRect::right().x + 150;
			curCreateY		=	CCRANDOM_0_1() * (VisibleRect::top().y - 300) + 150;

			int row			=	CCRANDOM_0_1() * 3 + 3;
			for (int i = 0; i < row; i++)
			{
				for (int k = 0; k < count; k++)
				{
					type		=	CCRANDOM_0_1() * 5 + 1;
					getFood		=	mFoodPool.takeOut();
					getFood->setType(type);
					this->addChild(getFood,4);
					foodList.pushBack(getFood);

					float x		=	GAP_DIST_HORIZON * k + curCreateX;
					float y		=	GAP_DIST_VERTICAL * i + curCreateY;
					getFood->setPosition(x,y);
				}
			}
		}else if (MODE_SPECIAL == foodMode)
		{
			curCreateX		=	VisibleRect::right().x + 150;
			curCreateY		=	CCRANDOM_0_1() * (VisibleRect::top().y - 300) + 150;

			type		=	CCRANDOM_0_1() * 2 + 6;
			getFood		=	mFoodPool.takeOut();
			getFood->setType(type);
			this->addChild(getFood,4);
			getFood->setPosition(curCreateX,curCreateY);
			foodList.pushBack(getFood);
		}
	}
	
}

void InGameLayer::moveFood()
{
	Food* getFood	=	NULL;
	for (int i = 0; i < foodList.size(); i++)
	{
		getFood		=	foodList.at(i);
		getFood->setSpeed(heroSpeed,0);
		if(mushroomPower > 0)
		{
			Point dPoint	=	getFood->getPosition() - mHero->getPosition();
			float dist		=	sqrt(dPoint.x * dPoint.x + dPoint.y * dPoint.y);
			float radian	=	atan2(dPoint.y,dPoint.x);
			float vx		=	cos(radian) * dist / 5;
			float vy		=	sin(radian) * dist / 5;
			if(dist < 800)
				getFood->setSpeed(vx,vy);
			mushroomPower	-=	0.005;
		}
		getFood->move();
		if(getFood->getPositionX() <= -50)
		{
			mFoodPool.takeIn(getFood);
			this->removeChild(getFood);
			foodList.eraseObject(getFood);
		}
	}
}

void InGameLayer::hitFoodTest()
{
	Food* getFood	=	NULL;
	for (int i = foodList.size() - 1; i >= 0; i--)
	{
		getFood		=	foodList.at(i);
		bool bl		=	getFood->hitTest(mHero->getPosition());
		if(bl)
		{
			//SimpleAudioEngine::getInstance()->playEffect("sounds/eat.mp3");
			if(getFood->getType() == 6)
			{
				coffeePower		+=	6;
			}else if(getFood->getType() == 7)
			{
				mushroomPower	+=	20;
			}
			mFoodPool.takeIn(getFood);
			this->removeChild(getFood);
			foodList.eraseObject(getFood);

			mHero->playParticle();
		}
	}
}

void InGameLayer::createObstacle()
{
   if(createObstacleDist > 0)
   {
		createObstacleDist -= heroSpeed;
   }else
   {
		int type		=	CCRANDOM_0_1() * 4 + 1;
		auto obstacle	=	mObstaclePool.takeOut();
		obstacle->setType(type);
		this->addChild(obstacle,4);
		obstacleList.pushBack(obstacle);

		createObstacleDist	=	CCRANDOM_0_1() * 500 + 200;
   }
}
void InGameLayer::moveObstacle()
{
	Obstacle* mObstacle	=	NULL;
	for (int i = 0; i < obstacleList.size(); i++)
	{
		mObstacle		=	obstacleList.at(i);
		float w			=	mObstacle->getContentSize().width;
		float h			=	mObstacle->getContentSize().height;
		mObstacle->setVx(heroSpeed * CCRANDOM_0_1() + heroSpeed);
		mObstacle->move();
		if(mObstacle->getPositionX() <= -150)
		{
		   mObstaclePool.takeIn(mObstacle);
		   mObstacle->setIsDestory(false);
		   this->removeChild(mObstacle);
		   obstacleList.eraseObject(mObstacle);
		}
	}
}
void InGameLayer::hitObstacle()
{
	Obstacle* mObstacle	=	NULL;
	for (int i = 0; i < obstacleList.size(); i++)
	{
	   mObstacle		=	obstacleList.at(i);
	   if(	!mObstacle->getIsDestory() && 
			mObstacle->hitTest(mHero->getBoundingBox()))
	   {
			life		-=	1;
			char chLife[24];
			sprintf(chLife,"LIVE%d",life);
			ttfLife->setString(chLife);

			obstaclePower	+=	2;

			SimpleAudioEngine::getInstance()->playEffect("sounds/hurt.mp3");

			if(life <= 0)
			{
				log("game over!!");
				SimpleAudioEngine::getInstance()->playEffect("sounds/lose.mp3");

			}
	   }
	}
}

void InGameLayer::shakeWindows()
{
   if(obstaclePower > 0)
   {
	   this->setPositionX(CCRANDOM_0_1() * 10);
	   this->setPositionY(CCRANDOM_0_1() * 10);
	   this->setRotation((CCRANDOM_0_1() - 0.5) * 2);
	   obstaclePower	-=	0.1;
   }else
   {
		obstaclePower	=	0;
		this->setPositionX(0);
		this->setPositionY(0);
		this->setRotation(0);
   }
}