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
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    m_pKeyboardEventListener = EventListenerKeyboard::create();
    m_pKeyboardEventListener->onKeyPressed = CC_CALLBACK_2(SimpleDPad::onKeyPressed, this);
    m_pKeyboardEventListener->onKeyReleased = CC_CALLBACK_2(SimpleDPad::onKeyReleased, this);

    /*
    m_pControllerEventListener = EventListenerController::create();
    m_pControllerEventListener->onConnected = CC_CALLBACK_2(SimpleDPad::onConnectController,this);
    m_pControllerEventListener->onDisconnected = CC_CALLBACK_2(SimpleDPad::onDisconnectedController,this);
    m_pControllerEventListener->onKeyDown = CC_CALLBACK_3(SimpleDPad::onKeyDown, this);
    m_pControllerEventListener->onKeyUp = CC_CALLBACK_3(SimpleDPad::onKeyUp, this);
    m_pControllerEventListener->onAxisEvent = CC_CALLBACK_3(SimpleDPad::onAxisEvent, this);
     */
     
#endif
    m_pEventListener->onTouchBegan = CC_CALLBACK_2(SimpleDPad::onTouchBegan, this);
    m_pEventListener->onTouchMoved = CC_CALLBACK_2(SimpleDPad::onTouchMoved, this);
    m_pEventListener->onTouchEnded = CC_CALLBACK_2(SimpleDPad::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority(m_pEventListener, this);
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    dispatcher->addEventListenerWithSceneGraphPriority(m_pKeyboardEventListener, this);
    //dispatcher->addEventListenerWithSceneGraphPriority(m_pControllerEventListener, this);
     
#endif
    
    //This function should be called for iOS platform
    //Controller::startDiscoveryController();
    
    m_pEventListener->retain();
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    m_pKeyboardEventListener->retain();
    //m_pControllerEventListener->retain();
#endif
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

void SimpleDPad::updateDirectionForTouchLocation(Vec2 location)
{
    float radians = (location - this->getPosition()).getAngle();
    float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);
    
    if ((degrees > -45 && degrees < 45))
    {
        //right
        m_vDirection = Vec2(1.0, 0.0);
    }
    else if (degrees >= 45 && degrees <= 135)
    {
        //bottom
        m_vDirection = Vec2(0.0, -1.0);
    }
    else if ((degrees > 135 && degrees <= 180) || (degrees <-135 && degrees >= -180))
    {
        //left
        m_vDirection = Vec2(-1.0, 0.0);
    }
    else if (degrees <= -45 && degrees >= -135)
    {
        //top
        m_vDirection = Vec2(0.0, 1.0);
    }
    m_pThePlayer->didChangeDirectionTo(m_vDirection);
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
//Keyboard
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
    m_lastKeyPressed = (int)keycode;
    m_pThePlayer->didChangeDirectionTo(m_vDirection);
}

void SimpleDPad::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
    //printf("onKeyReleased %d\n", keycode);
    if (m_lastKeyPressed == (int)keycode)
    {
        m_vDirection = Vec2::ZERO;
        m_bIsHeld = false;
        m_pThePlayer->simpleDPadTouchEnded();
    }
}

//Controller
void SimpleDPad::onKeyDown(Controller* controller, int keycode, Event* event)
{
    CCLOG("KeyDown:%d", keycode);
    m_lastKeyPressed = keycode;
    
    m_bIsHeld = true;
    if (keycode == cocos2d::Controller::Key::BUTTON_DPAD_RIGHT)
    {
        CCLOG("RIGHT");
        m_vDirection = Vec2(1.0, 0.0);
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_DPAD_DOWN)
    {
        CCLOG("DOWN");
        m_vDirection = Vec2(0.0, -1.0);
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_DPAD_LEFT)
    {
        CCLOG("LEFT");
        m_vDirection = Vec2(-1.0, 0.0);
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_DPAD_UP)
    {
        CCLOG("UP");
        m_vDirection = Vec2(0.0, 1.0);
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_A)
    {
        CCLOG("A");
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_B)
    {
        CCLOG("B");
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_X)
    {
        CCLOG("X");
    }
    else if (keycode == cocos2d::Controller::Key::BUTTON_Y)
    {
        CCLOG("Y");
    }
}

void SimpleDPad::onKeyUp(Controller* controller, int keycode, Event* event)
{
    //You can get the controller by tag, deviceId or devicename if there are multiple controllers
    CCLOG("tag:%d DeviceId:%d DeviceName:%s", controller->getTag(), controller->getDeviceId(), controller->getDeviceName().c_str());
    CCLOG("KeyUp:%d", keycode);
    
    if (m_lastKeyPressed == (int)keycode)
    {
        m_vDirection = Vec2::ZERO;
        m_bIsHeld = false;
        m_pThePlayer->simpleDPadTouchEnded();
    }
}

/*
void SimpleDPad::onButtonEvent(int keyCode, bool isPressed, float value, bool isAnalog)
{
    CCLOG("onButtonEvent:%d isPressed:%d value:%f isAnalog:%d", keyCode, isPressed, value, isAnalog);
}
 */

//The axis includes X-axis and Y-axis and its range is from -1 to 1. X-axis is start from left to right and Y-axis is bottom to top.
void SimpleDPad::onAxisEvent(cocos2d::Controller* controller, int keycode, cocos2d::Event* event)
{
    //const auto& keyStatus = controller->getKeyStatus(keycode);
    //CCLOG("Axis KeyCode:%d Axis Value:%f", keycode, keyStatus.value);
}

void SimpleDPad::onConnectController(Controller* controller, Event* event)
{
    CCLOG("Game controller connected");
}

void SimpleDPad::onDisconnectedController(Controller* controller, Event* event)
{
    CCLOG("Game controller disconnected");
}
#endif

void SimpleDPad::setTheHero(HeroSprite *thePlayer)
{
    m_pThePlayer = thePlayer;
}