//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "ActionSprite.h"
#include "config.h"

void ActionSprite::update(float dt)
{
    /*
    if (m_actionState == kActionStateManualWalk)
    {
        //printf("%s Current Position: %f, %f\n", m_strCharacterName.c_str(), this->getPosition().x, this->getPosition().y);
        this->setDesiredPosition(this->getPosition() + (m_vVelocity * dt));
        //printf("%s Desired Position: %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
    }
     */
}

//
void ActionSprite::idle()
{
    if (m_actionState != kActionStateIdle)
    {
        stopAllActions();
        runAction(m_idleAction[m_currentDirection]);
        m_actionState = kActionStateIdle;
        m_vVelocity = Vec2::ZERO;
    }
}

void ActionSprite::walkWithDirection(Vec2 direction, bool directionChanged)
{
    if (m_actionState == kActionStateIdle)
    {
        stopAllActions();
        //runAction(m_walkAction[m_currentDirection]);
        //m_actionState = kActionStateManualWalk;
        m_actionState = kActionStateAutoWalkStart;
    }
    /*
    if (m_actionState == kActionStateManualWalk)
    {
        m_vVelocity = Vec2(direction.x * m_fWalkSpeed, direction.y * m_fWalkSpeed);
        if (directionChanged)
        {
            stopAllActions();
            runAction(m_walkAction[m_currentDirection]);
        }
    }
     */
    if (!directionChanged && m_actionState == kActionStateAutoWalkStart)
    {
        //walkNumTilesWithDirection(1, m_currentDirection, true);
        //printf("\nwalkWithDirection\n");
        m_vDesiredPosition = determineDestinationPositon(1, m_currentDirection);
        //printf("%s determineDestinationPosition - %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
    }
    
    if (directionChanged && m_actionState != kActionStateAutoWalking)
    {
        //printf("\ndirectionChanged!\n");
        //printf("%s determineDestinationPosition - %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
        m_vDesiredPosition = determineDestinationPositon(1, m_currentDirection);
        //printf("%s determineDestinationPosition - %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
    }
}

void ActionSprite::walkNumTilesWithDirection(int numTilesToMove, ActionSpriteDirection directionToMove, bool forceMovement)
{
    printf("%s walkNumTilesWithDirection\n", m_strCharacterName.c_str());
    m_vDesiredPosition = determineDestinationPositon(numTilesToMove, directionToMove);
    
    bool isValidDestination = m_WalkBounds.containsPoint(m_vDesiredPosition);
    
    if ((isValidDestination || forceMovement) && (m_actionState == kActionStateAutoWalkStart))
    {
        stopAllActions();
        // Animate the player
        auto moveAction = MoveTo::create(numTilesToMove * m_fWalkSpeed, m_vDesiredPosition);
        
        // Play actions
        auto doneAction = CallFuncN::create(CC_CALLBACK_1(ActionSprite::onFinishedWalkingCallback, this));
        //auto animationSequence = Sequence::create((FiniteTimeAction*)m_walkAction[m_currentDirection], NULL);
        auto movementSequence = Sequence::create(moveAction, doneAction,NULL);
        runAction(m_walkAction[m_currentDirection]);
        runAction(movementSequence);
        
        m_actionState = kActionStateAutoWalking;
    }
}

void ActionSprite::walkOneTileInCurrentDirection()
{
    if (this->getPosition() == m_vDesiredPosition)
    {
        return;
    }
    
    if (m_actionState == kActionStateAutoWalkStart)
    {
        stopAllActions();
        // Animate the player
        auto moveAction = MoveTo::create(1 * m_fWalkSpeed, m_vDesiredPosition);
        
        //printf("Moving %s from %f %f to %f %f\n", m_strCharacterName.c_str(),
        //      this->getPosition().x/16.f,
        //       ((640.0f) - this->getPosition().y) / (kTileSize) -1,
        //       m_vDesiredPosition.x/16.f,
        //       ((640.0f) - m_vDesiredPosition.y) / (kTileSize) -1);
        
        // Play actions
        auto doneAction = CallFuncN::create(CC_CALLBACK_1(ActionSprite::onFinishedWalkingCallback, this));
        //auto animationSequence = Sequence::create((FiniteTimeAction*)m_walkAction[m_currentDirection], NULL);
        auto movementSequence = Sequence::create(moveAction, doneAction,NULL);
        runAction(m_walkAction[m_currentDirection]);
        runAction(movementSequence);
        
        m_actionState = kActionStateAutoWalking;
    }
}

Vec2 ActionSprite::determineDestinationPositon(int numTilesToMove, ActionSpriteDirection directionToMove)
{
    Vec2 destination = Vec2::ZERO;
    
    switch (directionToMove) {
        case kActionSpriteDirectionEast:
        {
            m_currentDirection = kActionSpriteDirectionEast;
            destination = Vec2(getPosition().x + (kTileSize * numTilesToMove), getPosition().y);
        }
            break;
        case kActionSpriteDirectionWest:
        {
            m_currentDirection = kActionSpriteDirectionWest;
            destination = Vec2(getPosition().x - (kTileSize * numTilesToMove), getPosition().y);
        }
            break;
        case kActionSpriteDirectionNorth:
        {
            m_currentDirection = kActionSpriteDirectionNorth;
            destination = Vec2(getPosition().x, getPosition().y + (kTileSize * numTilesToMove));
        }
            break;
        case kActionSpriteDirectionSouth:
        {
            m_currentDirection = kActionSpriteDirectionSouth;
            destination = Vec2(getPosition().x, getPosition().y - (kTileSize * numTilesToMove));
        }
            break;
            
        default:
            break;
    }
    
    //printf("\ndetermineDestinationPositon x: %f, y: %f\n", destination.x, destination.y);
    //printf("determineDestination TileCoord x: %f, y: %f\n", destination.x/16.f, (640.0f-destination.y)/16.0f - 1);

    return destination;
}

// Accessors
void ActionSprite::setPosition(const Vec2& pos)
{
    Sprite::setPosition(pos);
}

void ActionSprite::setDesiredPosition(const Vec2& pos)
{
    m_vDesiredPosition = pos;
}

Vec2 ActionSprite::getDesiredPosition()
{
    return m_vDesiredPosition;
}

void ActionSprite::setVelocity(const Vec2& velocity)
{
    m_vVelocity = velocity;
}

Vec2 ActionSprite::getVelocity()
{
    return m_vVelocity;
}

void ActionSprite::setActionState(ActionState theState)
{
    m_actionState = theState;
}

ActionState ActionSprite::getActionState()
{
    return m_actionState;
}

void ActionSprite::setCharacterName(std::string theName)
{
    m_strCharacterName = theName;
}

std::string ActionSprite::getCharacterName()
{
    return m_strCharacterName;
}

//Conversion
ActionSpriteDirection ActionSprite::directionStringToEnum(std::string directionToMove)
{
    ActionSpriteDirection theDirection = kActionSpriteDirectionMax;
    if (directionToMove == "east")
    {
        theDirection = kActionSpriteDirectionEast;
    }
    else if (directionToMove == "west")
    {
        theDirection = kActionSpriteDirectionWest;
    }
    else if (directionToMove == "north")
    {
        theDirection = kActionSpriteDirectionNorth;
    }
    else if (directionToMove == "south")
    {
        theDirection = kActionSpriteDirectionSouth;
    }
    
    return theDirection;
}
