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
    kCombatMenuButton_Undo,
    kCombatMenuButton_Max,
    kCombatMenuButton_None = -1,
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
    void onDefendButtonCallback(Ref* pSender);
    void onUndoButtonCallback(Ref* pSender);
    
    Menu* m_pCombatMenu;
    MenuItemImage* m_pCombatMenuButtons[kCombatMenuButton_Max];
    SpriteBatchNode *m_pActors;
    std::vector<HeroSprite*> m_vHeroes;
    int m_iCurrentHeroIndex;
};

#endif
