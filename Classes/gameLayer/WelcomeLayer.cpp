#include "gameLayer/WelcomeLayer.h"
#include "gameLayer/InGameLayer.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

WelcomeLayer::WelcomeLayer(void) :	hero(NULL)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

Scene* WelcomeLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = WelcomeLayer::create();
	sc->addChild(ly);
	return sc;
}

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//¼ÓÔØÎÆÀí»º´æ
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hungryHero.plist");
	//±³¾°
	auto bg = Sprite::create("bgWelcome.jpg");
	this->addChild(bg);
	bg->setPosition(VisibleRect::center());
	//logo
	auto logo = Sprite::createWithSpriteFrameName("welcome_title.png");
	this->addChild(logo);
	logo->setPosition( VisibleRect::right() - Point( VisibleRect::getVisibleRect().getMaxX() / 6, -VisibleRect::getVisibleRect().getMaxY() / 5 ) );
	//Ó¢ÐÛ
	hero = Sprite::createWithSpriteFrameName("welcome_hero.png");
	this->addChild(hero);
	hero->setPosition(VisibleRect::left() - Point(-100, 0));
	auto moveTo = MoveTo::create(1.5f, Point(VisibleRect::getVisibleRect().getMaxX() / 4, VisibleRect::getVisibleRect().getMaxY() / 2));
	auto easeTo = EaseSineOut::create(moveTo);
	auto actionCall = CallFuncN::create(CC_CALLBACK_1(WelcomeLayer::actionCallBack, this));
	auto seq = Sequence::create(easeTo, actionCall, NULL);
	hero->runAction(seq);
	//menu
	auto spPlayNor = Sprite::createWithSpriteFrameName("welcome_playButton.png");
	auto spPlaySel = Sprite::createWithSpriteFrameName("welcome_playButton.png");
	spPlaySel->setScale(0.9f);
	auto itemPlay = MenuItemSprite::create(spPlayNor, spPlaySel, NULL, CC_CALLBACK_1(WelcomeLayer::playCallBack, this));
	auto btnPlay = Menu::create(itemPlay, NULL);
	this->addChild(btnPlay);
	btnPlay->setPosition(VisibleRect::right() - Point( VisibleRect::getVisibleRect().getMaxX() / 6, VisibleRect::getVisibleRect().getMaxY() / 7 ) );
	btnPlay->runAction(RepeatForever::create(moveUpAndDown(0.8f, 50.0f)));

	auto spAboutNor = Sprite::createWithSpriteFrameName("welcome_aboutButton.png");
	auto spAboutSel = Sprite::createWithSpriteFrameName("welcome_aboutButton.png");
	spAboutSel->setScale(0.9f);
	auto itemAbout = MenuItemSprite::create(spAboutNor, spAboutSel, NULL, CC_CALLBACK_1(WelcomeLayer::aboutCallBack, this));
	auto btnAbout = Menu::create(itemAbout, NULL);
	this->addChild(btnAbout);
	btnAbout->setPosition(VisibleRect::right() - Point( VisibleRect::getVisibleRect().getMaxX() / 6, VisibleRect::getVisibleRect().getMaxY() / 3 ) );
	btnAbout->runAction(RepeatForever::create(moveUpAndDown(0.8f, 50.0f)));
	//sound
	auto spSoundOn = Sprite::createWithSpriteFrameName("soundOn0000.png");
	auto spSoundOff = Sprite::createWithSpriteFrameName("soundOff.png");

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;
	char chSound[266];
	for (int i = 0; i < 3; i++)
	{
		sprintf(chSound, "soundOn000%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(chSound);
		frameList.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(frameList, 0.2f);
	auto animate = Animate::create(animation);
	spSoundOn->runAction(RepeatForever::create(animate));

	auto itemSoundOn = MenuItemSprite::create(spSoundOn, spSoundOn, NULL);
	auto itemSoundOff = MenuItemSprite::create(spSoundOff, spSoundOff, NULL);
	auto itemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(WelcomeLayer::soundToggleCallBack,this), itemSoundOn, itemSoundOff, NULL);
	auto btnSoundToggle = Menu::create(itemToggle, NULL);
	this->addChild(btnSoundToggle);
	btnSoundToggle->setPosition(VisibleRect::leftTop() + Point( 40, -40 ));
	itemToggle->setSelectedIndex(0);
	//±³¾°ÒôÀÖ
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgWelcome.mp3");

	return true;
}

void WelcomeLayer::actionCallBack( Ref* sender )
{
	hero->runAction(RepeatForever::create(moveUpAndDown(1.0f, 80)));
}

void WelcomeLayer::playCallBack( Ref* sender )
{
	log("Play Call Back");
	SimpleAudioEngine::getInstance()->playEffect("sounds/eat.mp3");
	Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5f,InGameLayer::createScene()));
}

void WelcomeLayer::aboutCallBack( Ref* sender )
{
	log("About Call Back");
	SimpleAudioEngine::getInstance()->playEffect("sounds/eat.mp3");
}

void WelcomeLayer::soundToggleCallBack( Ref* sender )
{
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	} else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bgWelcome.mp3",true);
	}
}
