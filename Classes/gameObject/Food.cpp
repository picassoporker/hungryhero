#include "Food.h"
#include "VisibleRect.h"

USING_NS_CC;

Food::Food(void):	vx(0),
					vy(0),
					type(0)
{
}


Food::~Food(void)
{
}

void Food::setType(int type)
{
   this->type	=	type;
   char chType[10];
   sprintf(chType,"item%d.png",type);

   initWithSpriteFrameName(chType);
}

void Food::setSpeed(float vx,float vy)
{
	 this->vx	=	vx;
	 this->vy	=	vy;
}

void Food::move()
{
   this->setPosition(this->getPosition() - Point(vx,vy));
}

void Food::reset()
{
	this->removeFromParent();
	this->setPositionX(VisibleRect::right().x + 100);
}

bool Food::hitTest(const Point& hitPoint)
{
	float dx	=	hitPoint.x - this->getPositionX();
	float dy	=	hitPoint.y - this->getPositionY();

	float dist	=	sqrt(dx * dx + dy * dy);
	if(dist < 65 + this->getContentSize().width / 2)
	{
		return true;
	}
	
	return false;
}

int Food::getType()const
{
   return type;
}

