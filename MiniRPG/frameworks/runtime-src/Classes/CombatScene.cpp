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
    
    initHeroSprites();
    initCombatMenu();
    
    this->scheduleUpdate();
    
    return true;
}

void CombatScene::update(float delta)
{
    if (m_vHeroes.size() > 0)
    {
        //Vec2 tileCoord = tileCoordForPosition(m_pHero->getDesiredPosition());
        //printf("Update - Current TileCoordinates: %f, %f\n", tileCoord.x, tileCoord.y);
        
        for (int i=0; i<m_vHeroes.size(); ++i)
        {
            m_vHeroes[i]->update(delta);
        }
    }
}

void CombatScene::initHeroSprites()
{
    auto spritecache = SpriteFrameCache::getInstance();
    
    spritecache->addSpriteFramesWithFile("res/characters/heroine/heroine.plist");
    
    Point characterPositions [4] =
    {
        Point(240,420),
        Point(240,360),
        Point(240,300),
        Point(240,240),
    };
    
    for (int i=0;i<4;++i)
    {
        HeroSprite* mysprite = (HeroSprite*)HeroSprite::createHero("heroine");
        
        mysprite->setScale(1.0f);
        mysprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
        mysprite->setPosition(characterPositions[i]);
        mysprite->noAction();
        
        this->addChild(mysprite);
        m_vHeroes.push_back(mysprite);
    }
}

void CombatScene::initCombatMenu()
{
    auto upperLeft = Sprite::create("res/maps/1.png");
    upperLeft->setScale(1.0f);
    upperLeft->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    upperLeft->setPosition(Vec2(0, 240));
    
    this->addChild(upperLeft, -1);
    
    auto upperRight = Sprite::create("res/maps/2.png");
    upperRight->setScale(1.0f);
    upperRight->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    upperRight->setPosition(Vec2(160, 240));
    
    this->addChild(upperRight, -1);
    
    auto lowerLeft = Sprite::create("res/maps/3.png");
    lowerLeft->setScale(1.0f);
    lowerLeft->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    lowerLeft->setPosition(Vec2(0, 0));
    
    this->addChild(lowerLeft, -1);
    
    auto lowerRight = Sprite::create("res/maps/4.png");
    lowerRight->setScale(1.0f);
    lowerRight->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    lowerRight->setPosition(Vec2(160, 0));
    
    this->addChild(lowerRight, -1);
    
    
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
    printf("Doink!\n");
    m_vHeroes[0]->setActionState(kActionStateAutoWalkStart);
    //m_vHeroes[0]->walkOneTileInCurrentDirection();
    m_vHeroes[0]->walkNumTilesWithDirection(1, kActionSpriteDirectionWest, true);
}