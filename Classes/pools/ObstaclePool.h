#ifndef _Obstacle_POOL_H_
#define _Obstacle_POOL_H_

#include "gameObject/Obstacle.h"

class ObstaclePool
{
public:
	ObstaclePool(void);
	~ObstaclePool(void);

public:

	void init();
	void takeIn(Obstacle* obstacle);
	Obstacle* takeOut();

private:

	const int MIN_COUNT;
	const int MAX_COUNT;
	const int REPLENISH;

	cocos2d::Vector<Obstacle*> pool;

};

#endif	//_Obstacle_POOL_H_


