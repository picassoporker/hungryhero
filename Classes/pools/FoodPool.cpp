#include "FoodPool.h"


FoodPool::FoodPool(void):	MIN_COUNT(100),
							MAX_COUNT(200),
							REPLENISH(10),
							pool()
{
}


FoodPool::~FoodPool(void)
{
}

void FoodPool::init()
{
	Food* food	=	NULL;
	for (int i = 0; i < MIN_COUNT; i++)
	{
		food	=	Food::create();
		pool.pushBack(food);	
	}
}
void FoodPool::takeIn(Food* food)
{
	if(pool.size() < MAX_COUNT)
	{
		pool.pushBack(food);
		food->release();
	}
}
Food* FoodPool::takeOut()
{
	if(pool.size() == 0)
	{
		for (int i = 0; i < REPLENISH; i++)
		{
		   pool.pushBack(Food::create());
		}
	}

	Food* getFood	=	pool.at(pool.size() - 1);
	getFood->retain();
	pool.eraseObject(getFood);

	return getFood;
}
