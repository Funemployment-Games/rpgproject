//
//  NPCSprite.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/14/14.
//
//

#include "NPCSprite.h"

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
    m_walkPattern = kActionSpriteWalkPatternNone;
    m_fDelayBetweenSteps = 0.0f;
    m_fTimeSinceLastStep = 0.0f;
    
    createActions();
    
    return true;
}

void NPCSprite::update(float dt)
{
    ActionSprite::update(dt);
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

void NPCSprite::walkNumTilesWithDirection(int numTilesToMove, std::string directionToMove)
{
    Vec2 destination = Vec2::ZERO;
    if (directionToMove == "east")
    {
        m_currentDirection = kActionSpriteDirectionEast;
        destination = Vec2(getPosition().x + (16.0f * numTilesToMove), getPosition().y);
    }
    else if (directionToMove == "west")
    {
        m_currentDirection = kActionSpriteDirectionWest;
        destination = Vec2(getPosition().x - (16.0f * numTilesToMove), getPosition().y);
    }
    else if (directionToMove == "north")
    {
        m_currentDirection = kActionSpriteDirectionNorth;
        destination = Vec2(getPosition().x, getPosition().y + (16.0f * numTilesToMove));
    }
    else if (directionToMove == "south")
    {
        m_currentDirection = kActionSpriteDirectionSouth;
        destination = Vec2(getPosition().x, getPosition().y - (16.0f * numTilesToMove));
    }
    
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

void NPCSprite::onFinishedWalkingCallback(Ref* pSender)
{
    printf("onFinishedWalkingCallback");
    idle();
}