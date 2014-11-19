//
//  NPCSprite.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/14/14.
//
//

#include "NPCSprite.h"
#include "config.h"
#include "LuaGlobalManager.h"

Sprite* NPCSprite::createNPC(std::string spriteName, std::string dialogueId, std::string dialogueYesId, std::string dialogueNoId)
{
    NPCSprite* npc = new (std::nothrow) NPCSprite();
    if (npc && npc->initWithParameters(spriteName, dialogueId, dialogueYesId, dialogueNoId))
    {
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;
}


// on "init" you need to initialize your instance
bool NPCSprite::initWithParameters(std::string spriteName, std::string dialogueId, std::string dialogueYesId, std::string dialogueNoId)
{
    //////////////////////////////
    // 1. super init first
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/characters/" + spriteName + "/" + spriteName + ".plist");
    
    if ( !Sprite::initWithSpriteFrameName(spriteName + "_s_01.png") )
    {
        return false;
    }
    
    m_fWalkSpeed = 1.0f;
    m_strSpriteName = spriteName;
    m_strDialogueId = dialogueId;
    
    m_currentDirection = kActionSpriteDirectionSouth;
    m_actionState = kActionStateAutoWalkDone;
    m_fDelayBetweenSteps = 0.0f;
    m_fTimeSinceLastStep = 0.0f;
    
    createActions();
    
    return true;
}

void NPCSprite::update(float dt)
{
    /*
    if (m_actionState == kActionStateManualWalk)
    {
        ActionSprite::update(dt);
    }
    else
     */
    if (m_actionState == kActionStateTalking)
    {
        
    }
    else
    {
        if (m_fDelayBetweenSteps != 0.0f)
        {
            if (m_fTimeSinceLastStep > m_fDelayBetweenSteps)
            {
                m_fTimeSinceLastStep = 0;
                determineNextTileToWalkTo();
            }
            else
            {
                m_fTimeSinceLastStep += dt;
            }
        }
    }
}

// Creation
void NPCSprite::createActions()
{
    //idle animation
    createIdleAction();
    
    // Walk Action
    createWalkAction();
}

void NPCSprite::createWalkAction()
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
        
        Animation *walkAnimation = Animation::createWithSpriteFrames(walkFrames, 1.0f/4.0f);
        m_walkAction[j] = /*Animate::create(walkAnimation);*/RepeatForever::create((Animate::create(walkAnimation)));
        m_walkAction[j]->retain();
    }
}

void NPCSprite::createIdleAction()
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

//
std::string NPCSprite::getDialogueId()
{
    return m_strDialogueId;
}

void NPCSprite::setDelayBetweenSteps(float theDelay)
{
    m_fDelayBetweenSteps = theDelay;
}

float NPCSprite::getDelayBetweenSteps()
{
    return m_fDelayBetweenSteps;
}

void NPCSprite::setWalkBounds(Rect bounds)
{
    m_WalkBounds = bounds;
}

Rect NPCSprite::getWalkBounds()
{
    return m_WalkBounds;
}

void NPCSprite::determineNextTileToWalkTo()
{
    int directionIndex = 0;
    
    if (m_WalkBounds.size.width < 1 && m_WalkBounds.size.height > 0)
    {
        directionIndex = rand() % 1;     // v2 in the range 0 to 1
    }
    else if (m_WalkBounds.size.width > 0 && m_WalkBounds.size.height < 1)
    {
        directionIndex = rand() % 1 + 2;     //in the range 2-3
    }
    else
    {
        directionIndex = rand() % kActionSpriteDirectionMax;     // v2 in the range 0 to 3
    }

    std::string directionsArray[kActionSpriteDirectionMax] = {"north","south","east","west"};
    ActionSpriteDirection theDirection = directionStringToEnum(directionsArray[directionIndex]);
    m_actionState = kActionStateAutoWalkStart;
    walkNumTilesWithDirection(1, theDirection, false);
}

void NPCSprite::onFinishedWalkingCallback(Ref* pSender)
{
    idle();
}