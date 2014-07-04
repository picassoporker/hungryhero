#include "ObstaclePool.h"


ObstaclePool::ObstaclePool(void):	MIN_COUNT(100),
	MAX_COUNT(200),
	REPLENISH(10),
	pool()
{
}


ObstaclePool::~ObstaclePool(void)
{
}

void ObstaclePool::init()
{
	Obstacle* obstacle	=	NULL;
	for (int i = 0; i < MIN_COUNT; i++)
	{
		obstacle	=	Obstacle::create();
		pool.pushBack(obstacle);	
	}
}
void ObstaclePool::takeIn(Obstacle* obstacle)
{
	if(pool.size() < MAX_COUNT)
	{
		pool.pushBack(obstacle);
		obstacle->release();
	}
}
Obstacle* ObstaclePool::takeOut()
{
	if(pool.size() == 0)
	{
		for (int i = 0; i < REPLENISH; i++)
		{
			pool.pushBack(Obstacle::create());
		}
	}

	Obstacle* getobstacle	=	pool.at(pool.size() - 1);
	getobstacle->retain();
	pool.eraseObject(getobstacle);

	return getobstacle;
}
