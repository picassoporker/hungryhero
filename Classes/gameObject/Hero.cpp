#include "Hero.h"
#include "VisibleRect.h"

USING_NS_CC;

Hero::Hero(void) :	eatParticle(NULL),
					eatParticlePlaying(false)
{
}


Hero::~Hero(void)
{
}

bool Hero::init()
{
	Sprite::init();

	initView();

	return true;
}

void Hero::initView()
{
   Vector<SpriteFrame*> list;
   SpriteFrame* frame	=	NULL;
   char chKey[266];
   for (int i = 1; i <= 20; i++)
   {
	   if(i < 10)
			sprintf(chKey,"fly_000%d.png",i);
	   else
			sprintf(chKey,"fly_00%d.png",i);
	   frame	=	SpriteFrameCache::getInstance()->getSpriteFrameByName(chKey);
	   list.pushBack(frame);
   }

   auto animation	=	Animation::createWithSpriteFrames(list,0.05f);
   auto animate		=	Animate::create(animation);

   this->runAction(RepeatForever::create(animate));
}


void Hero::moveTo(cocos2d::Point& toPoint)
{
	float vy	=	(toPoint.y - this->getPositionY()) / 10;
	this->setPositionY(this->getPositionY() + vy);

	float dx	=	toPoint.x - this->getPositionX();
	float dy	=	toPoint.y - this->getPositionY();
	float deg	=	-atan2(dy,dx) * 180 / M_PI;
	
	if(deg > 30)
	{
	   deg		=	30;
	}else if (deg < -30)
	{
		deg		=	-30;
	}
	this->setRotation(deg);
	
}

void Hero::show(cocos2d::Point& toPoint) 
{
	float dx	=	(toPoint.x - this->getPositionX()) / 10;
	this->setPositionX(dx + this->getPositionX());
}

void Hero::playParticle()
{
	if(!eatParticle)
	{
		eatParticle	=	ParticleSystemQuad::create("eatParticle.plist");
		this->addChild(eatParticle);
		eatParticle->setAnchorPoint(Point::ANCHOR_MIDDLE);
		eatParticle->setPosition(Point(130,37));
	}
	if(!eatParticlePlaying)
	{
		eatParticle->setVisible(true);
		eatParticlePlaying	=	true;
		this->scheduleOnce(SEL_SCHEDULE(&Hero::stopParticle),0.5f);
	}
}

void Hero::stopParticle(float dt )
{
	eatParticle->setVisible(false);
	eatParticlePlaying	=	false;
}

void  Hero::rotate(float dt)
{
	float vy	=	(VisibleRect::center().y - this->getPositionY()) / 5;
	this->setRotation(this->getRotation() + 30);
	this->setPositionY(this->getPositionY() + vy);
}