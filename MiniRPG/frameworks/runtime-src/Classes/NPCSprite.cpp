//
//  NPCSprite.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/14/14.
//
//

#include "NPCSprite.h"
#include "config.h"

Sprite* NPCSprite::createNPC(std::string spriteName, std::string scriptName)
{
    NPCSprite* npc = new (std::nothrow) NPCSprite();
    if (npc && npc->initWithParameters(spriteName, scriptName))
    {
        npc->autorelease();
        return npc;
    }
    CC_SAFE_DELETE(npc);
    return nullptr;
}


// on "init" you need to initialize your instance
bool NPCSprite::initWithParameters(std::string spriteName, std::string scriptName)
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::initWithSpriteFrameName(spriteName + "_s_01.png") )
    {
        return false;
    }
    
    m_fWalkSpeed = 1.0f;
    m_strSpriteName = spriteName;
    m_strScriptName = scriptName;
    
    m_currentDirection = kActionSpriteDirectionSouth;
    m_actionState = kActionStateAutoWalk;
    m_fDelayBetweenSteps = 0.0f;
    m_fTimeSinceLastStep = 0.0f;
    
    createActions();
    
    return true;
}

void NPCSprite::update(float dt)
{
    if (m_actionState == kActionStateManualWalk)
    {
        ActionSprite::update(dt);
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

void NPCSprite::walkNumTilesWithDirection(int numTilesToMove, std::string directionToMove, bool forceMovement)
{
    Vec2 destination = determineDestinationPositon(numTilesToMove, directionToMove);
    
    bool isValidDestination = m_WalkBounds.containsPoint(destination);
    
    if (isValidDestination || forceMovement)
    {
        // Animate the player
        auto moveAction = MoveTo::create(numTilesToMove * m_fWalkSpeed, destination);
        
        // Play actions
        m_actionState = kActionStateAutoWalk;
        auto doneAction = CallFuncN::create(CC_CALLBACK_1(NPCSprite::onFinishedWalkingCallback, this));
        auto animationSequence = Sequence::create((FiniteTimeAction*)m_walkAction[m_currentDirection], NULL);
        auto movementSequence = Sequence::create(moveAction, doneAction,NULL);
        runAction(animationSequence);
        runAction(movementSequence);
    }
}

Vec2 NPCSprite::determineDestinationPositon(int numTilesToMove, std::string directionToMove)
{
    Vec2 destination = Vec2::ZERO;
    
    if (directionToMove == "east")
    {
        m_currentDirection = kActionSpriteDirectionEast;
        destination = Vec2(getPosition().x + (kTileSize * numTilesToMove), getPosition().y);
    }
    else if (directionToMove == "west")
    {
        m_currentDirection = kActionSpriteDirectionWest;
        destination = Vec2(getPosition().x - (kTileSize * numTilesToMove), getPosition().y);
    }
    else if (directionToMove == "north")
    {
        m_currentDirection = kActionSpriteDirectionNorth;
        destination = Vec2(getPosition().x, getPosition().y + (kTileSize * numTilesToMove));
    }
    else if (directionToMove == "south")
    {
        m_currentDirection = kActionSpriteDirectionSouth;
        destination = Vec2(getPosition().x, getPosition().y - (kTileSize * numTilesToMove));
    }
    
    return destination;
}

//
std::string NPCSprite::getScriptName()
{
    return m_strScriptName;
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

void NPCSprite::onFinishedWalkingCallback(Ref* pSender)
{
    //printf("onFinishedWalkingCallback");
    idle();
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
    walkNumTilesWithDirection(1, directionsArray[directionIndex], false);
}