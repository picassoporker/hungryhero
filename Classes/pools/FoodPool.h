#ifndef _FOOD_POOL_H_
#define _FOOD_POOL_H_

#include "gameObject/Food.h"

class FoodPool
{
public:
	FoodPool(void);
	~FoodPool(void);

public:

	void init();
	void takeIn(Food* food);
	Food* takeOut();

private:

	const int MIN_COUNT;
	const int MAX_COUNT;
	const int REPLENISH;

	cocos2d::Vector<Food*> pool;

};

#endif	//_FOOD_POOL_H_


