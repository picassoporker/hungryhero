#ifndef _FOOD_H_
#define _FOOD_H_

#include "cocos2d.h"

class Food	: public cocos2d::Sprite
{
public:
	Food(void);
	~Food(void);
	
	CREATE_FUNC(Food);
public:

	void move();
	void reset();
	bool hitTest(const cocos2d::Point& hitPoint);
	void setSpeed(float vx,float vy);
	int getType()const;
	void setType(int type);

private:

	int type;
	float vx;
	float vy;

};

#endif	//_FOOD_H_


