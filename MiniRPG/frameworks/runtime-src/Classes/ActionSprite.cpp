//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "ActionSprite.h"

void ActionSprite::update(float dt)
{
    if (m_actionState == kActionStateManualWalk)
    {
        //printf("%s Current Position: %f, %f\n", m_strCharacterName.c_str(), this->getPosition().x, this->getPosition().y);
        this->setDesiredPosition(this->getPosition() + (m_vVelocity * dt));
        //printf("%s Desired Position: %f, %f\n", m_strCharacterName.c_str(), m_vDesiredPosition.x, m_vDesiredPosition.y);
    }
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
        runAction(m_walkAction[m_currentDirection]);
        m_actionState = kActionStateManualWalk;
    }
    if (m_actionState == kActionStateManualWalk)
    {
        m_vVelocity = Vec2(direction.x * m_fWalkSpeed, direction.y * m_fWalkSpeed);
        if (directionChanged)
        {
            stopAllActions();
            runAction(m_walkAction[m_currentDirection]);
        }
    }
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

void ActionSprite::setWalkPattern(ActionSpriteWalkPattern thePattern)
{
    m_walkPattern = thePattern;
}

ActionSpriteWalkPattern ActionSprite::getWalkPattern()
{
    return m_walkPattern;
}

void ActionSprite::setCharacterName(std::string theName)
{
    m_strCharacterName = theName;
}

std::string ActionSprite::getCharacterName()
{
    return m_strCharacterName;
}
