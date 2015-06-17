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
    initMonsterSprites();
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
        Point(224,420),
        Point(240,360),
        Point(240,300),
        Point(240,240),
    };
    
    for (int i=0;i<4;++i)
    {
        HeroSprite* mysprite = (HeroSprite*)HeroSprite::createHero("heroine", kActionSpriteDirectionWest);
        
        mysprite->setScale(1.0f);
        mysprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
        mysprite->setPosition(characterPositions[i]);
        mysprite->noAction();
        
        this->addChild(mysprite);
        m_vHeroes.push_back(mysprite);
    }
    
    m_iCurrentHeroIndex = 0;
}

void CombatScene::initMonsterSprites()
{
    auto monsterSprite = Sprite::create("res/monsters/goblin3.png");
    monsterSprite->setScale(1.0f);
    monsterSprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    monsterSprite->setPosition(Point(100,420));
    this->addChild(monsterSprite);
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
        Point(64,-180),
    };
    
    const char* buttonUpImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
        "res/ui/btn_talk.png"
    };
    const char* buttonDownImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
        "res/ui/btn_talk.png"
    };
    
    ccMenuCallback buttonHandlers [kCombatMenuButton_Max] =
    {
        CC_CALLBACK_1(CombatScene::onFightButtonCallback, this),
        CC_CALLBACK_1(CombatScene::onUndoButtonCallback, this),
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
    if (m_iCurrentHeroIndex < 3)
    {
        m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(-1, kActionSpriteDirectionWest, true);
        
        m_iCurrentHeroIndex++;
        
        m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(1, kActionSpriteDirectionWest, true);
    }
    else if (m_iCurrentHeroIndex == 3)
    {
        m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(-1, kActionSpriteDirectionWest, true);
        
        m_pCombatMenu->setEnabled(false);
    }
    else
    {
        printf("onFightButtonCallback - m_iCurrentHeroIndex: %d\n", m_iCurrentHeroIndex);
    }
}

void CombatScene::onUndoButtonCallback(Ref* pSender)
{
    if (m_iCurrentHeroIndex > 0)
    {
        m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(-1, kActionSpriteDirectionWest, true);
        
        m_iCurrentHeroIndex--;
        
        m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(1, kActionSpriteDirectionWest, true);
    }
    else if (m_iCurrentHeroIndex == 0)
    {
        //m_vHeroes[m_iCurrentHeroIndex]->setActionState(kActionStateAutoWalkStart);
        //m_vHeroes[m_iCurrentHeroIndex]->walkNumTilesWithDirection(-1, kActionSpriteDirectionWest, true);
        printf("onUndoButtonCallback - First hero, nothing to undo!\n");
    }
    else
    {
        printf("onUndoButtonCallback - m_iCurrentHeroIndex: %d\n", m_iCurrentHeroIndex);
    }
}
