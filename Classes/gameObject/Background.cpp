#include "Background.h"

USING_NS_CC;

Background::Background(void) :	one(NULL),
								two(NULL)
{
}


Background::~Background(void)
{
}
void Background::setBackground(const std::string& key)
{
	one		=	Sprite::createWithSpriteFrameName(key);
	this->addChild(one);
	one->setAnchorPoint(Point::ZERO);

	two		=	Sprite::createWithSpriteFrameName(key);
	this->addChild(two);
	two->setAnchorPoint(Point::ZERO);
	two->setPositionX(one->getPositionX() + one->getContentSize().width);

}
void Background::move(float vx)
{
	float oneX	=	one->getPositionX() - vx;
	float twoX	=	two->getPositionX() - vx;
	one->setPositionX(oneX);
	two->setPositionX(twoX);
   
	if (oneX <= -one->getContentSize().width)
	{
		one->setPositionX(twoX + two->getContentSize().width);
	}else if(twoX <= -two->getContentSize().width)
	{
		two->setPositionX(oneX + one->getContentSize().width);
	}
}