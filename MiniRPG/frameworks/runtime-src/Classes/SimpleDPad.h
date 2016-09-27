//
//  SimpleDPad.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_SimpleDPad_h
#define PompaDroid_SimpleDPad_h

#include "cocos2d.h"
#include "HeroSprite.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#include "base/ControllerDesktop.h"
#endif

USING_NS_CC;

class SimpleDPad : public cocos2d::Sprite/*, public cocos2d::TargetedTouchDelegate*/
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Sprite* createSprite();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SimpleDPad);
    
    //scheduled methods
    virtual void update(float dt);
    
    //Event handlers
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    //Touches
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    virtual void onTouchEnded(Touch *touch, Event *event);
    
    //Keys
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, Event* event);
    
    //Controller
    virtual void onKeyDown(cocos2d::Controller* controller, int keycode, Event* event);
    virtual void onKeyUp(cocos2d::Controller* controller, int keycode, Event* event);
    virtual void onButtonEvent(int keyCode, bool isPressed, float value, bool isAnalog);
    virtual void onAxisEvent(cocos2d::Controller* controller, int keyCode, cocos2d::Event* event);
    virtual void onConnectController(cocos2d::Controller* controller, Event* event);
    virtual void onDisconnectedController(Controller* controller, Event* event);
#endif
    void updateDirectionForTouchLocation(Vec2 location);
    
    //Accessors
    void setTheHero(HeroSprite* thePlayer);
    
private:
    Vec2 m_vDirection;
    float m_fRadius;
    bool m_bIsHeld;
    HeroSprite* m_pThePlayer;
    int m_lastKeyPressed;
    
    EventListenerTouchOneByOne* m_pEventListener;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    EventListenerKeyboard* m_pKeyboardEventListener;
    EventListenerController* m_pControllerEventListener;
#endif
};

#endif
