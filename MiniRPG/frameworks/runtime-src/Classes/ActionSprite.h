//
//  ActionSprite.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_ActionSprite_h
#define PompaDroid_ActionSprite_h

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

typedef enum _ActionState {
    kActionStateNone = 0,
    kActionStateIdle,
    kActionStateManualWalk,
    kActionStateAutoWalkStart,
    kActionStateAutoWalking,
    kActionStateAutoWalkDone,
    kActionStateTalking,
} ActionState;

typedef enum  _ActionSpriteDirection
{
    kActionSpriteDirectionNorth = 0,
    kActionSpriteDirectionSouth,
    kActionSpriteDirectionEast,
    kActionSpriteDirectionWest,
    kActionSpriteDirectionMax,
    
} ActionSpriteDirection;

class ActionSprite: public cocos2d::Sprite
{
public:
    //scheduled methods
    virtual void update(float dt) = 0;
    
    // creation
    virtual void createActions() = 0;
    virtual void createWalkAction() = 0;
    virtual void createIdleAction() = 0;
    
    //action methods
    virtual void idle();
    virtual void noAction();
    virtual void walkWithDirection(Vec2 direction, bool directionChanged);
    void walkNumTilesWithDirection(int numTilesToMove, ActionSpriteDirection directionToMove, bool forceMovement);
    void walkOneTileInCurrentDirection();
    
    //accessor methods
    virtual void setPosition(const Vec2& pos);
    void setDesiredPosition(const Vec2& pos);
    Vec2 getDesiredPosition();
    void setVelocity(const Vec2& velocity);
    Vec2 getVelocity();
    void setCharacterName(std::string theName);
    std::string getCharacterName();
    ActionSpriteDirection directionStringToEnum(std::string directionToMove);
    
    void setActionState(ActionState theState);
    ActionState getActionState();
    
    //Callbacks
    virtual void onFinishedWalkingCallback(Ref* pSender) = 0;
    
private:

    
protected:
    Vec2 determineDestinationPositon(int numTilesToMove, ActionSpriteDirection directionToMove);
    
    //actions
    Action* m_idleAction[kActionSpriteDirectionMax];
    Action* m_walkAction[kActionSpriteDirectionMax];
    
    //states
    ActionState m_actionState;
    ActionSpriteDirection m_currentDirection;
    
    //attributes
    float m_fWalkSpeed;
    
    //movement
    Vec2 m_vVelocity;
    Vec2 m_vDesiredPosition;
    Rect m_WalkBounds;
    
    std::string m_strSpriteName;
    std::string m_strCharacterName;
};

#endif
