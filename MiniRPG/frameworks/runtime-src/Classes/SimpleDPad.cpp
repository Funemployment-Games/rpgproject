//
//  SimpleDPad.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "SimpleDPad.h"

Sprite* SimpleDPad::createSprite()
{
    // 'sprite' is an autorelease object
    auto sprite = SimpleDPad::create();
    
    // return the layer
    return sprite;
}

// on "init" you need to initialize your instance
bool SimpleDPad::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::initWithFile("res/ui/pd_dpad.png") )
    {
        return false;
    }
    
    m_fRadius = 64;
    m_bIsHeld = false;
    
    this->setPosition(Vec2(80, 80));
    this->setOpacity(100);
    
    this->scheduleUpdate();
    
    return true;
}

void SimpleDPad::update(float dt)
{
    if (m_bIsHeld)
    {
        m_pThePlayer->isHoldingDirection(m_vDirection);
    }
}

void SimpleDPad::onEnterTransitionDidFinish()
{    
    m_pEventListener = EventListenerTouchOneByOne::create();
    m_pEventListener->setSwallowTouches(true);
    
    m_pKeyboardEventListener = EventListenerKeyboard::create();
    m_pKeyboardEventListener->onKeyPressed = CC_CALLBACK_2(SimpleDPad::onKeyPressed, this);
    m_pKeyboardEventListener->onKeyReleased = CC_CALLBACK_2(SimpleDPad::onKeyReleased, this);
    
    m_pEventListener->onTouchBegan = CC_CALLBACK_2(SimpleDPad::onTouchBegan, this);
    m_pEventListener->onTouchMoved = CC_CALLBACK_2(SimpleDPad::onTouchMoved, this);
    m_pEventListener->onTouchEnded = CC_CALLBACK_2(SimpleDPad::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority(m_pEventListener, this);
    dispatcher->addEventListenerWithSceneGraphPriority(m_pKeyboardEventListener, this);

    
    m_pEventListener->retain();
    m_pKeyboardEventListener->retain();
}

void SimpleDPad::onExit()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->removeEventListener(m_pEventListener);
    m_pEventListener->release();
}

bool SimpleDPad::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 location = Director::getInstance()->convertToGL(touch->getLocationInView());
    
    float distanceSQ = (location - this->getPosition()).getLengthSq();
    
    if (distanceSQ <= m_fRadius * m_fRadius)
    {
        //get angle 8 directions
        updateDirectionForTouchLocation(location);
        m_bIsHeld = true;
        return true;
    }
    
    return false;
}

void SimpleDPad::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 location = Director::getInstance()->convertToGL(touch->getLocationInView());
    updateDirectionForTouchLocation(location);
}

void SimpleDPad::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    m_vDirection = Vec2::ZERO;
    m_bIsHeld = false;
    m_pThePlayer->simpleDPadTouchEnded();
}

void SimpleDPad::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    m_bIsHeld = true;
    if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        //right
        m_vDirection = Vec2(1.0, 0.0);
    }
    /*
    else if (degrees > 22.5 && degrees < 67.5)
    {
        //bottomright
        m_vDirection = Vec2(1.0, -1.0);
    }
     */
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        //bottom
        m_vDirection = Vec2(0.0, -1.0);
    }
    /*
    else if (degrees > 112.5 && degrees < 157.5)
    {
        //bottomleft
        m_vDirection = Vec2(-1.0, -1.0);
    }
     */
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        //left
        m_vDirection = Vec2(-1.0, 0.0);
    }
    /*
    else if (degrees < -22.5 && degrees > -67.5)
    {
        //topright
        m_vDirection = Vec2(1.0, 1.0);
    }
     */
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        //top
        m_vDirection = Vec2(0.0, 1.0);
    }
    /*
    else if (degrees < -112.5 && degrees > -157.5)
    {
        //topleft
        m_vDirection = Vec2(-1.0, 1.0);
    }
     */
    else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_Z)
    {

    }
    
    //printf("onKeyPressed %d\n", keycode);
    m_lastKeyPressed = keycode;
    m_pThePlayer->didChangeDirectionTo(m_vDirection);
}

void SimpleDPad::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    //printf("onKeyReleased %d\n", keycode);
    if (m_lastKeyPressed == keycode)
    {
        m_vDirection = Vec2::ZERO;
        m_bIsHeld = false;
        m_pThePlayer->simpleDPadTouchEnded();
    }
}

void SimpleDPad::updateDirectionForTouchLocation(Vec2 location)
{
    float radians = (location - this->getPosition()).getAngle();
    float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
    
    if (degrees <= 22.5 && degrees >= -22.5)
    {
        //right
        m_vDirection = Vec2(1.0, 0.0);
    }
    /*
     else if (degrees > 22.5 && degrees < 67.5)
    {
        //bottomright
        m_vDirection = Vec2(1.0, -1.0);
    }
     */
    else if (degrees >= 67.5 && degrees <= 112.5)
    {
        //bottom
        m_vDirection = Vec2(0.0, -1.0);
    }
    /*
    else if (degrees > 112.5 && degrees < 157.5)
    {
        //bottomleft
        m_vDirection = Vec2(-1.0, -1.0);
    }
     */
    else if (degrees >= 157.5 || degrees <= -157.5)
    {
        //left
        m_vDirection = Vec2(-1.0, 0.0);
    }
    /*
    else if (degrees < -22.5 && degrees > -67.5)
    {
        //topright
        m_vDirection = Vec2(1.0, 1.0);
    }
     */
    else if (degrees <= -67.5 && degrees >= -112.5)
    {
        //top
        m_vDirection = Vec2(0.0, 1.0);
    }
    /*
    else if (degrees < -112.5 && degrees > -157.5)
    {
        //topleft
        m_vDirection = Vec2(-1.0, 1.0);
    }
     */
    m_pThePlayer->didChangeDirectionTo(m_vDirection);
}

void SimpleDPad::setTheHero(HeroSprite *thePlayer)
{
    m_pThePlayer = thePlayer;
}