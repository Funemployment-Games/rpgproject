//
//  ActionSprite.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_HeroSprite_h
#define PompaDroid_HeroSprite_h

#include "ActionSprite.h"

USING_NS_CC;

class HeroSprite: public ActionSprite
{
public:
    static Sprite* createHero(std::string spriteName, ActionSpriteDirection currentDirection = kActionSpriteDirectionSouth );
    static Sprite* create();
    
    bool initWithParameters(std::string spriteName, ActionSpriteDirection currentDirection);
    
    //scheduled methods
    virtual void update(float dt);
    
    //creation
    virtual void createActions();
    virtual void createWalkAction();
    virtual void createIdleAction();
    
    //D-Pad
    void didChangeDirectionTo(Vec2 direction);
    void simpleDPadTouchEnded();
    void isHoldingDirection(Vec2 direction);
    
    //Callbacks
    virtual void onFinishedWalkingCallback(Ref* pSender);
private:
    bool m_bIsHoldingDirection;
    bool m_bDidChangeDirection;
    Vec2 m_vNextDirection;
};

#endif
