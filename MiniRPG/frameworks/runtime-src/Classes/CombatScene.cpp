//
//  CombatScene.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 4/28/15.
//
//

#include "CombatScene.h"

Scene* CombatScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = CombatScene::create();
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CombatScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    m_pHero = nullptr;
    initHeroSprites();
    initCombatMenu();
    
    this->scheduleUpdate();
    
    return true;
}

void CombatScene::update(float delta)
{
    
}

void CombatScene::initHeroSprites()
{
    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();
    
    // the .plist file can be generated with any of the tools mentioned below
    spritecache->addSpriteFramesWithFile("res/characters/heroine/heroine.plist");
    
    // Our .plist file has names for each of the sprites in it.  We'll grab
    // the sprite named, "Blue_Front1" from the sprite sheet:
    auto mysprite = Sprite::createWithSpriteFrameName("heroine_w_01.png");
    
    mysprite->setScale(1.0f);
    mysprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    mysprite->setPosition(Vec2(160, 448));
    
    this->addChild(mysprite);
}

void CombatScene::initCombatMenu()
{
    m_pCombatMenu = CCMenu::create();
    
    Point buttonPositions [kCombatMenuButton_Max] =
    {
        Point(64,-160),
    };
    
    const char* buttonUpImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
    };
    const char* buttonDownImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
    };
    
    ccMenuCallback buttonHandlers [kCombatMenuButton_Max] =
    {
        CC_CALLBACK_1(CombatScene::onFightButtonCallback, this),
    };
    
    for (int i=0; i< kCombatMenuButton_Max;++i)
    {
        auto tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pCombatMenuButtons[i] = tempButton;
    }
    
    for (int i=0;i<kCombatMenuButton_Max;++i)
    {
        m_pCombatMenu->addChild(m_pCombatMenuButtons[i]);
    }
    
    this->addChild(m_pCombatMenu, 0);
}

void CombatScene::onFightButtonCallback(Ref* pSender)
{
    printf("Doink!");
}