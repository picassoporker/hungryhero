#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

class Hero : public cocos2d::Sprite
{
public:
	Hero(void);
	~Hero(void);

public:

	virtual bool init();
	CREATE_FUNC(Hero);

public:

	void moveTo(cocos2d::Point& toPoint);
	void show(cocos2d::Point& toPoint);
	void playParticle();
	void rotate(float dt);
	
private:

	void initView();
	void stopParticle(float dt );
private:
	cocos2d::ParticleSystemQuad* eatParticle;
	bool eatParticlePlaying;
	
};


#endif	//_HERO_H_

