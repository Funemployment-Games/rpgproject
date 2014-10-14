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
    static Sprite* createHero(std::string spriteName);
    static Sprite* create();
    
    bool initWithParameters(std::string spriteName);
    
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
private:
};

#endif
