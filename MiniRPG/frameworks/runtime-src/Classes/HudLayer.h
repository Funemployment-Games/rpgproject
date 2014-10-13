//
//  HudLayer.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#ifndef PompaDroid_HudLayer_h
#define PompaDroid_HudLayer_h


#include "cocos2d.h"
#include "SimpleDPad.h"

USING_NS_CC;

enum ContextMenuButton
{
    eContextMenuButton_Talk,
    //eContextMenuButton_Search,
    eContextMenuButton_Max,
    eContextMenuButton_None = -1,
};

class HudLayer: public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Layer* createLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HudLayer);
    
    //Accessors
    SimpleDPad* getTheDPad();
    void setContextButtonVisibility(ContextMenuButton theButton, bool isVisible);
    bool getContextButtonVisibility(ContextMenuButton theButton);
    
private:
    SimpleDPad* m_pTheDPad;
    Menu* m_pContextMenu;
    MenuItemImage* m_pContextButtons[eContextMenuButton_Max];
    
    void onTalkButtonCallback(Ref* pSender);
    void onSearchButtonCallback(Ref* pSender);
    void CreateContextMenuButtons();
};


#endif
