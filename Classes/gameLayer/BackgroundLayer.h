#ifndef _BACKGROUND_LAYER_H_
#define _BACKGROUND_LAYER_H_

#include "cocos2d.h"
#include "gameObject/Background.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);
public:

	virtual bool init();
	CREATE_FUNC(BackgroundLayer);

public:

	void move();
	void setVx(float vx);

private:

	float vx;
	Background* one;
	Background* two;
	Background* three;
	Background* four;
};

#endif	//_BACKGROUND_LAYER_H_


