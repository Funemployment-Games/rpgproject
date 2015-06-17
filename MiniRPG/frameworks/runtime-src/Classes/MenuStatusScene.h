//
//  StatusMenuScene.h
//  MiniRPG
//
//  Created by Matthew Barney on 6/6/15.
//
//

#ifndef MiniRPG_MenuStatusScene_h
#define MiniRPG_MenuStatusScene_h

#include "cocos2d.h"
#include "HeroSprite.h"

USING_NS_CC;

enum MenuStatusSceneButton
{
    kMenuStatusSceneButton_Exit,
    kMenuStatusSceneButton_Max,
    kMenuStatusSceneButton_None = -1,
};

class MenuStatusScene: public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuStatusScene);
    
private:
    void onExitButtonCallback(Ref* pSender);
    
    Menu* m_pStatusScreenMenu;
    MenuItemImage* m_pStatusScreenMenuButtons[kMenuStatusSceneButton_Max];
};

#endif
