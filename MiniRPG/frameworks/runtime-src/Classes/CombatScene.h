//
//  CombatScene.h
//  MiniRPG
//
//  Created by Matthew Barney on 4/28/15.
//
//

#ifndef __MiniRPG__CombatScene__
#define __MiniRPG__CombatScene__

#include "cocos2d.h"
#include "HeroSprite.h"
#include <iostream>

USING_NS_CC;

enum CombatMenuButton
{
    kCombatMenuButton_Fight,
    kCombatMenuButton_Run,
    kCombatMenuButton_Magic,
    kCombatMenuButton_Item,
    kCombatMenuButton_Max,
    kCombatMenuButton_None = -1,
};

enum CombatMenuInputMode
{
    kCombatMenuInputMode_MainMenu,
    kCombatMenuInputMode_SubMenu,
    kCombatMenuInputMode_TargetSelect,
    kCombatMenuInputMode_Max,
    kCombatMenuInputMode_None = -1,
    
};

class CombatScene: public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CombatScene);
    
private:
    void initHeroSprites();
    void initMonsterSprites();
    void initCombatMenu();
    void onFightButtonCallback(Ref* pSender);
    void onMagicButtonCallback(Ref* pSender);
    void onItemButtonCallback(Ref* pSender);
    void onRunButtonCallback(Ref* pSender);
    void onUndoButtonCallback(Ref* pSender);
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, Event* event);
    
    void HandleMainMenuInput(cocos2d::EventKeyboard::KeyCode keycode);
    void HandleSubMenuInput(cocos2d::EventKeyboard::KeyCode keycode);
    void HandleTargetSelectInput(cocos2d::EventKeyboard::KeyCode keycode);
    
    Menu* m_pCombatMenu;
    MenuItemImage* m_pCombatMenuButtons[kCombatMenuButton_Max];
    //SpriteBatchNode *m_pActors;
    std::vector<HeroSprite*> m_vHeroes;
    std::vector<Sprite*> m_vMonsters;
    Sprite* m_pSpriteCursor;
    int m_iCurrentHeroIndex;
    CombatMenuInputMode m_eCurrentInputMode;
    
    EventListenerKeyboard* m_pKeyboardEventListener;
};

#endif
