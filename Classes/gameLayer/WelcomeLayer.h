#ifndef _WELCOME_LAYER_H_
#define _WELCOME_LAYER_H_

#include "cocos2d.h"

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

public:
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

public:
	static cocos2d::Scene* createScene();

private:
	//ÄÚÁªº¯Êý
	cocos2d::Sequence* moveUpAndDown(float dt, float dist);

	void actionCallBack(cocos2d::Ref* sender);

	void playCallBack(cocos2d::Ref* sender);

	void aboutCallBack(cocos2d::Ref* sender);

	void soundToggleCallBack(cocos2d::Ref* sender);

private:
	//Ó¢ÐÛ
	cocos2d::Sprite* hero;

};

inline cocos2d::Sequence* WelcomeLayer::moveUpAndDown(float dt, float dist)
{
	auto upBy = cocos2d::MoveBy::create(dt, cocos2d::Point(0, dist));
	auto upEase = cocos2d::EaseSineOut::create(upBy);
	
	auto downBy = cocos2d::MoveBy::create(dt, cocos2d::Point(0, -dist));
	auto downEase = cocos2d::EaseSineOut::create(downBy);

	return cocos2d::Sequence::create(upEase, downEase, NULL);
}

#endif // !_WELCOME_LAYER_H_