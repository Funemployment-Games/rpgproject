//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "HeroSprite.h"

Sprite* HeroSprite::createHero(std::string spriteName, ActionSpriteDirection currentDirection)
{
    HeroSprite* hero = new (std::nothrow) HeroSprite();
    if (hero && hero->initWithParameters(spriteName, currentDirection))
    {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}


// on "init" you need to initialize your instance
bool HeroSprite::initWithParameters(std::string spriteName, ActionSpriteDirection currentDirection)
{
    std::string initialSpriteName = "";
    switch (currentDirection)
    {
        case kActionSpriteDirectionEast:
        {
            initialSpriteName = spriteName + "_e_01.png";
        }
            break;
        case kActionSpriteDirectionWest:
        {
            initialSpriteName = spriteName + "_w_01.png";
        }
            break;
        case kActionSpriteDirectionSouth:
        {
            initialSpriteName = spriteName + "_s_01.png";
        }
            break;
        case kActionSpriteDirectionNorth:
        {
            initialSpriteName = spriteName + "_n_01.png";
        }
            break;
            
        default:
            break;
    }
    
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::initWithSpriteFrameName(initialSpriteName) )
    {
        return false;
    }
    
    m_fWalkSpeed = .4f;
    m_strSpriteName = spriteName;
    m_currentDirection = currentDirection;
    m_actionState = kActionStateAutoWalkDone;
    m_bIsHoldingDirection = false;
    m_bDidChangeDirection = false;
    m_vNextDirection = Vec2::ZERO;
    
    createActions();
    
    return true;
}

void HeroSprite::update(float dt)
{
    ActionSprite::update(dt);
    
    if (m_actionState == kActionStateAutoWalkDone)
    {
        if (!m_bIsHoldingDirection)
        {
            idle();
        }
    }
}

// Creation
void HeroSprite::createActions()
{
    //idle animation
    createIdleAction();
    
    // Walk Action
    createWalkAction();
}

void HeroSprite::createWalkAction()
{
    int i; // This is goofy as shit, but for some reason its the only way to not make i go from 1 to maxint after 1 loop.
    for (int j=kActionSpriteDirectionNorth;j<kActionSpriteDirectionMax;++j)
    {
        Vector<SpriteFrame*> walkFrames;
        for (i=1; i < 3; ++i)
        {
            char fileName[20];
            switch (j) {
                case kActionSpriteDirectionNorth:
                    sprintf(fileName, "_n_%02d.png", i);
                    break;
                case kActionSpriteDirectionEast:
                    sprintf(fileName, "_e_%02d.png", i);
                    break;
                case kActionSpriteDirectionWest:
                    sprintf(fileName, "_w_%02d.png", i);
                    break;
                case kActionSpriteDirectionSouth:
                    sprintf(fileName, "_s_%02d.png", i);
                    break;
                    
                default:
                    break;
            }
            
            std::string fullSpriteName = m_strSpriteName + fileName;
            
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fullSpriteName);
            walkFrames.pushBack(frame);
        }
        
        Animation *walkAnimation = Animation::createWithSpriteFrames(walkFrames, 1.0/4.0);
        m_walkAction[j] = RepeatForever::create((Animate::create(walkAnimation)));
        m_walkAction[j]->retain();
    }
}

void HeroSprite::createIdleAction()
{
    int i;
    for (int j=kActionSpriteDirectionNorth;j<kActionSpriteDirectionMax;++j)
    {
        Vector<SpriteFrame*> idleFrames;
        for (i = 1; i < 3; ++i)
        {
            char fileName[20];
            switch (j) {
                case kActionSpriteDirectionNorth:
                    sprintf(fileName, "_n_%02d.png", i);
                    break;
                case kActionSpriteDirectionEast:
                    sprintf(fileName, "_e_%02d.png", i);
                    break;
                case kActionSpriteDirectionWest:
                    sprintf(fileName, "_w_%02d.png", i);
                    break;
                case kActionSpriteDirectionSouth:
                    sprintf(fileName, "_s_%02d.png", i);
                    break;
                    
                default:
                    break;
            }
            
            std::string fullSpriteName = m_strSpriteName + fileName;
            
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fullSpriteName);
            idleFrames.pushBack(frame);
        }
        
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, 1.0/2.0);
        m_idleAction[j] = RepeatForever::create((Animate::create(idleAnimation)));
        m_idleAction[j]->retain();
    }
}

//D-Pad
void HeroSprite::didChangeDirectionTo(Vec2 direction)
{
    //m_vDesiredPosition = this->getPosition();
    bool directionChanged = false;
    if (direction.x == 1.0 && m_currentDirection != kActionSpriteDirectionEast)
    {
        m_currentDirection = kActionSpriteDirectionEast;
        //printf("didChangeDirectionTo east\n");
        directionChanged = true;
    }
    else if (direction.x == -1.0 && m_currentDirection != kActionSpriteDirectionWest)
    {
        m_currentDirection = kActionSpriteDirectionWest;
        //printf("didChangeDirectionTo west\n");
        directionChanged = true;
    }
    else if (direction.y == 1.0 && m_currentDirection != kActionSpriteDirectionNorth)
    {
        m_currentDirection = kActionSpriteDirectionNorth;
        //printf("didChangeDirectionTo north\n");
        directionChanged = true;
    }
    else if (direction.y == -1.0 && m_currentDirection != kActionSpriteDirectionSouth)
    {
        m_currentDirection = kActionSpriteDirectionSouth;
        //printf("didChangeDirectionTo south\n");
        directionChanged = true;
    }
    
    //walkNumTilesWithDirection(1, m_currentDirection, true);
    m_bDidChangeDirection = directionChanged;
    m_vNextDirection = direction;
    walkWithDirection(m_vNextDirection, directionChanged);
}

void HeroSprite::simpleDPadTouchEnded()
{
    //printf("simpleDPadTouchEnded\n");
    /*
    if (m_actionState == kActionStateManualWalk)
    {
        //m_vDesiredPosition = this->getPosition();
        idle();
    }
     */
    
    //if (!m_bDidChangeDirection)
    {
        m_bIsHoldingDirection = false;
    }
}

void HeroSprite::isHoldingDirection(Vec2 direction)
{
    m_bIsHoldingDirection = true;
    
    walkWithDirection(direction, false);
}

//Callbacks
void HeroSprite::onFinishedWalkingCallback(Ref* pSender)
{
    /*
    printf("onFinishedWalkingCallback %s in TileCoords from %f %f to %f %f\n", m_strCharacterName.c_str(),
           this->getPosition().x/16.f,
           ((640.0f) - this->getPosition().y) / (16.f)-1,
           m_vDesiredPosition.x/16,
           ((640.0f) - m_vDesiredPosition.y) / (16.f)-1);
    
    printf("onFinishedWalkingCallback %s from %f %f to %f %f\n", m_strCharacterName.c_str(),
           this->getPosition().x,
           this->getPosition().y,
           m_vDesiredPosition.x,
           m_vDesiredPosition.y);
     */

    
    if (m_bIsHoldingDirection)
    {
        m_actionState = kActionStateAutoWalkStart;
        /*
        printf("\nonFinishedWalkingCallback - m_bIsHoldingDirection\n");
        printf("%s onFinishedWalkingCallback currentpos - %f, %f\n", m_strCharacterName.c_str(), this->getPosition().x, this->getPosition().y);
        printf("%s onFinishedWalkingCallback destpos - %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
        */
        if (m_bDidChangeDirection)
        {
            walkWithDirection(m_vNextDirection, m_bDidChangeDirection);
            m_bDidChangeDirection = false;
        }
    }
    else
    {
        m_actionState = kActionStateAutoWalkDone;
    }
}

