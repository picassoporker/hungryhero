#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "cocos2d.h"

class Background : public cocos2d::Sprite
{
public:
	Background(void);
	~Background(void);
	
	CREATE_FUNC(Background);
	
public:

	void setBackground(const std::string& key);
	void move(float vx);

private:

	cocos2d::Sprite* one;
	cocos2d::Sprite* two;
};

#endif	//_BACKGROUND_H_


