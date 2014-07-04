#include "Obstacle.h"
#include "VisibleRect.h"

USING_NS_CC;

Obstacle::Obstacle(void) :	vx(0),
							isDestory(false)
{
}


Obstacle::~Obstacle(void)
{
}

void Obstacle::setType(int type)
{
	this->type	=	type;
	char chType[100];
	if(type != 4)
	{
		sprintf(chType,"obstacle%d.png",type);
		initWithSpriteFrameName(chType);
	}else
	{
		Vector<SpriteFrame*> list;
		auto frame	=	SpriteFrameCache::getInstance()->getSpriteFrameByName("obstacle4_0001.png");
		list.pushBack(frame);
			frame	=	SpriteFrameCache::getInstance()->getSpriteFrameByName("obstacle4_0002.png");
		list.pushBack(frame);
		initWithSpriteFrame(frame);
		auto anim	=	Animation::createWithSpriteFrames(list,0.02f);
		auto anima	=	Animate::create(anim);
		this->runAction(RepeatForever::create(anima));
	}
	this->setPositionX(VisibleRect::getVisibleRect().getMaxX() + 200);
	this->setPositionY(CCRANDOM_0_1() * (VisibleRect::getVisibleRect().getMaxY() -
						this->getContentSize().height) + this->getContentSize().height / 2);
}
void Obstacle::move()
{
	this->setPositionX(this->getPositionX() - vx);
}
void Obstacle::setVx(float vx)
{
	this->vx	=	vx;
}
bool Obstacle::hitTest(const cocos2d::Rect& hitRect)
{
	bool bl		=	this->getBoundingBox().intersectsRect(hitRect);
	if(bl)
	{
		destory();
	}
	return bl;
}
void Obstacle::destory()
{
	isDestory	=	true;
	this->stopAllActions();
	char chCrash[100];
	sprintf(chCrash,"obstacle%d_crash.png",type);
	initWithSpriteFrameName(chCrash);
}

bool Obstacle::getIsDestory()const
{
	return isDestory;
}

void Obstacle::setIsDestory(bool bl)
{
	isDestory	=	bl;
}
