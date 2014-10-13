//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "HeroSprite.h"

Sprite* HeroSprite::createSprite()
{
    // 'sprite' is an autorelease object
    auto sprite = HeroSprite::create();
    
    // return the layer
    return sprite;
}

// on "init" you need to initialize your instance
bool HeroSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::initWithSpriteFrameName("heroine_e_01.png") )
    {
        return false;
    }
    
    m_fHitPoints = 100.0;
    m_fDamage = 20.0;
    m_fWalkSpeed = 50;
    
    createActions();
    
    return true;
}

void HeroSprite::update(float dt)
{
    ActionSprite::update(dt);
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
                    sprintf(fileName, "heroine_n_%02d.png", i);
                    break;
                case kActionSpriteDirectionEast:
                    sprintf(fileName, "heroine_e_%02d.png", i);
                    break;
                case kActionSpriteDirectionWest:
                    sprintf(fileName, "heroine_w_%02d.png", i);
                    break;
                case kActionSpriteDirectionSouth:
                    sprintf(fileName, "heroine_s_%02d.png", i);
                    break;
                    
                default:
                    break;
            }

            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
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
                    sprintf(fileName, "heroine_n_%02d.png", i);
                    break;
                case kActionSpriteDirectionEast:
                    sprintf(fileName, "heroine_e_%02d.png", i);
                    break;
                case kActionSpriteDirectionWest:
                    sprintf(fileName, "heroine_w_%02d.png", i);
                    break;
                case kActionSpriteDirectionSouth:
                    sprintf(fileName, "heroine_s_%02d.png", i);
                    break;
                    
                default:
                    break;
            }
            
            SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
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
    bool directionChanged = false;
    if (direction.x == 1.0 && m_currentDirection != kActionSpriteDirectionEast)
    {
        m_currentDirection = kActionSpriteDirectionEast;
        directionChanged = true;
    }
    else if (direction.x == -1.0 && m_currentDirection != kActionSpriteDirectionWest)
    {
        m_currentDirection = kActionSpriteDirectionWest;
        directionChanged = true;
    }
    else if (direction.y == 1.0 && m_currentDirection != kActionSpriteDirectionNorth)
    {
        m_currentDirection = kActionSpriteDirectionNorth;
        directionChanged = true;
    }
    else if (direction.y == -1.0 && m_currentDirection != kActionSpriteDirectionSouth)
    {
        m_currentDirection = kActionSpriteDirectionSouth;
        directionChanged = true;
    }
    
    walkWithDirection(direction, directionChanged);
}

void HeroSprite::simpleDPadTouchEnded()
{
    if (m_actionState == kActionStateWalk)
    {
        idle();
    }
}

void HeroSprite::isHoldingDirection(Vec2 direction)
{
    walkWithDirection(direction, false);
}

