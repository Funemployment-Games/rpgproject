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
    
    //
    auto treesSprite = Sprite::create("res/trees.png");
    treesSprite->setScale(.5f);
    treesSprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    treesSprite->setPosition(Point(0,200));
    this->addChild(treesSprite);
    
    //
    auto botSprite = Sprite::create("res/bot.png");
    botSprite->setScale(.5f);
    botSprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    botSprite->setPosition(Point(0,0));
    this->addChild(botSprite);
    
    initHeroSprites();
    initMonsterSprites();
    //initCombatMenu();
    
    m_pSpriteCursor = Sprite::create("res/ui/cursor.png");
    m_pSpriteCursor->setScale(.5f);
    m_pSpriteCursor->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
    m_pSpriteCursor->setPosition(Point(16,56));
    this->addChild(m_pSpriteCursor);
    
    m_pKeyboardEventListener = EventListenerKeyboard::create();
    m_pKeyboardEventListener->onKeyPressed = CC_CALLBACK_2(CombatScene::onKeyPressed, this);
    m_pKeyboardEventListener->onKeyReleased = CC_CALLBACK_2(CombatScene::onKeyReleased, this);
    m_pKeyboardEventListener->retain();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(m_pKeyboardEventListener, this);
    
    m_eCurrentInputMode = kCombatMenuInputMode_MainMenu;
    
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
        Point(192,173),
        Point(224,146),
        Point(192,119),
        Point(192,92),
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
    Point monsterPositions [6] =
    {
        Point(32,144),
        Point(32,96),
        Point(64,144),
        Point(64,96),
        
        Point(96,144),
        Point(96,96),
        /*
        Point(82,163),
        Point(82,130),
        Point(82,97),
         */
    };
    
    for (int i=0;i<6;++i)
    {
        auto monsterSprite = Sprite::create("res/monsters/eyefang.png");
        monsterSprite->setScale(1.f);
        monsterSprite->setAnchorPoint(Vec2(0.0,0.0)); //bottom left
        monsterSprite->setPosition(Point(monsterPositions[i]));
        this->addChild(monsterSprite);
         m_vMonsters.push_back(monsterSprite);
    }
}

void CombatScene::initCombatMenu()
{
    m_pCombatMenu = CCMenu::create();
    
    Point buttonPositions [kCombatMenuButton_Max] =
    {
        Point(-71,-47),
        Point(-71,-64),
        Point(-71, -81),
        Point(-71,-98),
    };
    
    const char* buttonUpImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_fight.png",
        "res/ui/btn_run.png",
        "res/ui/btn_magic.png",
        "res/ui/btn_item.png"
    };
    const char* buttonDownImages [kCombatMenuButton_Max] =
    {
        "res/ui/btn_fight.png",
        "res/ui/btn_run.png",
        "res/ui/btn_magic.png",
        "res/ui/btn_item.png"
    };
    
    ccMenuCallback buttonHandlers [kCombatMenuButton_Max] =
    {
        CC_CALLBACK_1(CombatScene::onFightButtonCallback, this),
        CC_CALLBACK_1(CombatScene::onRunButtonCallback, this),
        CC_CALLBACK_1(CombatScene::onMagicButtonCallback, this),
        CC_CALLBACK_1(CombatScene::onItemButtonCallback, this),
    };
    
    for (int i=0; i< kCombatMenuButton_Max;++i)
    {
        auto tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        tempButton->setScale(1.0f);
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

void CombatScene::onRunButtonCallback(Ref* pSender)
{
}

void CombatScene::onMagicButtonCallback(Ref* pSender)
{
}

void CombatScene::onItemButtonCallback(Ref* pSender)
{
    
}

//Keyboard
void CombatScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, Event* event)
{
    switch (m_eCurrentInputMode) {
        case kCombatMenuInputMode_MainMenu:
        {
            HandleMainMenuInput(keycode);
        }
            break;
        case kCombatMenuInputMode_SubMenu:
        {
            HandleSubMenuInput(keycode);
        }
            break;
        case kCombatMenuInputMode_TargetSelect:
        {
            HandleTargetSelectInput(keycode);
        }
            break;
            
        default:
            break;
    }

}

void CombatScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, Event* event)
{
    
}

//
void CombatScene::HandleMainMenuInput(cocos2d::EventKeyboard::KeyCode keycode)
{
    Vec2 currentCursorPos = m_pSpriteCursor->getPosition();
    
    if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        if (currentCursorPos.y < 56.0f)
        {
            m_pSpriteCursor->setPosition(currentCursorPos.x, currentCursorPos.y + 16.0f);
        }
        else
        {
            m_pSpriteCursor->setPosition(currentCursorPos.x, 8.0f);
        }
    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        if (currentCursorPos.y > 8.0f)
        {
            m_pSpriteCursor->setPosition(currentCursorPos.x, currentCursorPos.y - 16.0f);
        }
        else
        {
            m_pSpriteCursor->setPosition(currentCursorPos.x, 56.0f);
        }
    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_X)
    {
        Rect monsterRect = m_vMonsters[0]->getBoundingBox();
        Vec2 cursorPos = Vec2(monsterRect.origin.x - (monsterRect.size.width/2.0f), monsterRect.origin.y + (monsterRect.size.height/2.0f));
        
        m_pSpriteCursor->setPosition(cursorPos);
        m_eCurrentInputMode = kCombatMenuInputMode_TargetSelect;
    }
}

void CombatScene::HandleSubMenuInput(cocos2d::EventKeyboard::KeyCode keycode)
{
    
}

void CombatScene::HandleTargetSelectInput(cocos2d::EventKeyboard::KeyCode keycode)
{
    Vec2 currentCursorPos = m_pSpriteCursor->getPosition();
    
    if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {

    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {

    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {

    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {

    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_X)
    {

    }
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_Z)
    {
        m_pSpriteCursor->setPosition(16.f,56.f);
        m_eCurrentInputMode = kCombatMenuInputMode_MainMenu;
    }
}
