#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer(void) :	vx(0),
											one(NULL),
											two(NULL),
											three(NULL),
											four(NULL)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}
 bool BackgroundLayer::init()
 {
	 Layer::init();
 
	 one	=	Background::create();
	 one->setBackground("bgLayer1.jpg");
	 this->addChild(one);
	 one->setAnchorPoint(Point::ZERO);

	 two	=	Background::create();
	 two->setBackground("bgLayer2.png");
	 this->addChild(two);
	 two->setAnchorPoint(Point::ZERO);

	 three	=	Background::create();
	 three->setBackground("bgLayer3.png");
	 this->addChild(three);
	 three->setAnchorPoint(Point::ZERO);

	 four	=	Background::create();
	 four->setBackground("bgLayer4.png");
	 this->addChild(four);
	 four->setAnchorPoint(Point::ZERO);

	 return true;
 }

 void BackgroundLayer::move()
 {
 	one->move(vx * 0.2f);
	two->move(vx * 0.4f);
	three->move(vx * 0.6f);
	four->move(vx * 0.8f);
 }

 void BackgroundLayer::setVx(float vx)
 {
 	this->vx	=	vx;
 }