#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "cocos2d.h"

class Obstacle : public cocos2d::Sprite
{
public:
	Obstacle(void);
	~Obstacle(void);

	CREATE_FUNC(Obstacle);
public:

	void setType(int type);
	void move();
	void setVx(float vx);
	bool hitTest(const cocos2d::Rect& hitRect);
	bool getIsDestory()const;
	void setIsDestory(bool bl);
private:
	void destory();
private:

	float vx;
	int type;
	bool isDestory;
};

#endif	//_OBSTACLE_H_


