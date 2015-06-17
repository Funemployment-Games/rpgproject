//
//  StatusMenuScene.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 6/6/15.
//
//

#include <stdio.h>
#include "MenuStatusScene.h"

Scene* MenuStatusScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = MenuStatusScene::create();
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuStatusScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    m_pStatusScreenMenu = CCMenu::create();
    
    Point buttonPositions [kMenuStatusSceneButton_Max] =
    {
        Point(-60,-160)
    };
    
    const char* buttonUpImages [kMenuStatusSceneButton_Max] =
    {
        "res/ui/btn_exit.png"
    };
    const char* buttonDownImages [kMenuStatusSceneButton_Max] =
    {
        "res/ui/btn_exit.png"
    };
    
    ccMenuCallback buttonHandlers [kMenuStatusSceneButton_Max] =
    {
        CC_CALLBACK_1(MenuStatusScene::onExitButtonCallback, this),
    };
    
    for (int i=0; i< kMenuStatusSceneButton_Max;++i)
    {
        auto tempButton = MenuItemImage::create(buttonUpImages[i],
                                                buttonDownImages[i],
                                                buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pStatusScreenMenuButtons[i] = tempButton;
    }
    
    for (int i=0;i<kMenuStatusSceneButton_Max;++i)
    {
        m_pStatusScreenMenu->addChild(m_pStatusScreenMenuButtons[i]);
    }
    
    this->addChild(m_pStatusScreenMenu, 0);
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Point origin = Director::getInstance()->getVisibleOrigin();
    
    const int labelCount = 39;
    
    const Size labelDimensions [labelCount] = {
        Size(100,12),
        Size(100,12),
        Size(100,12),
        
        Size(80,12),
        Size(60,12),
        Size(60,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(20,12),
        Size(80,12),
        Size(80,12),
        Size(20,12),
        Size(80,12),
        
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        Size(80,12),
        
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12),
        Size(20,12)
    };
    
    const Point labelPositions [labelCount] =
    {
        Point(60,460),
        Point(160,460),
        Point(270,460),
        
        Point(60,340),
        Point(220,340),
        Point(220,320),
        Point(140,340),
        Point(270,340),
        Point(270,320),
        
        Point(60,320),
        Point(60,300),
        Point(60,320),
        Point(120,320),
        Point(110,320),
        Point(60,300),
        Point(120,300),
        Point(110,300),
        
        Point(60,220),
        Point(60,200),
        Point(60,180),
        Point(60,160),
        Point(60,140),
        Point(220,220),
        Point(220,200),
        Point(220,180),
        Point(220,160),
        Point(220,140),
        Point(220,120),
        
        Point(140,220),
        Point(140,200),
        Point(140,180),
        Point(140,160),
        Point(140,140),
        Point(300,220),
        Point(300,200),
        Point(300,180),
        Point(300,160),
        Point(300,140),
        Point(300,120)
    };
    
    const char* labelText [labelCount] =
    {
        "Status",
        "Boudicca",
        "Royal Princess",
        
        "Level",
        "EXP",
        "To Next",
        "1",
        "0",
        "999999999",
        
        "HP",
        "MP",
        "1",
        "/",
        "9999",
        "9999",
        "/",
        "9999",
        
        "Strength",
        "Agility",
        "Vitality",
        "Intellect",
        "Spirit",
        "Attack",
        "Hit \%",
        "Defense",
        "Evade \%",
        "Magic Def.",
        "Magic Eva. \%",
        
        "99",
        "99",
        "99",
        "99",
        "99",
        "99",
        "99",
        "99",
        "99",
        "99",
        "99"
    };
    
    const TextHAlignment labelHAlignment [labelCount] = {
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::CENTER,
        TextHAlignment::RIGHT,
        TextHAlignment::RIGHT,
        
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::RIGHT,
        TextHAlignment::LEFT,
        TextHAlignment::RIGHT,
        TextHAlignment::RIGHT,
        TextHAlignment::LEFT,
        TextHAlignment::RIGHT,
        
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT,
        TextHAlignment::LEFT
    };

    //int value = 99;
    //char buffer[2];
    //sprintf (buffer, "%d",value);
    
    for (int i=0; i< labelCount;++i)
    {
        auto label = LabelTTF::create(labelText[i], "Arial", 12, labelDimensions[i], labelHAlignment[i], TextVAlignment::CENTER);
        
        label->setPosition(labelPositions[i]);
        
        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    
    auto spritecache = SpriteFrameCache::getInstance();
    
    spritecache->addSpriteFramesWithFile("res/characters/heroine/heroine.plist");
    HeroSprite* mysprite = (HeroSprite*)HeroSprite::createHero("heroine", kActionSpriteDirectionWest);
    mysprite->setScale(1.0f);
    mysprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    mysprite->setPosition(Point(80,450));
    mysprite->noAction();
    
    this->addChild(mysprite);
    
    this->scheduleUpdate();
    
    return true;
}

void MenuStatusScene::update(float delta)
{

}

void MenuStatusScene::onExitButtonCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}