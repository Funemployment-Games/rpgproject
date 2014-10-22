//
//  HudLayer.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#include "HudLayer.h"
#include "NPCManager.h"

Layer* HudLayer::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = HudLayer::create();
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool HudLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_pTheDPad = (SimpleDPad*)SimpleDPad::createSprite();
    this->addChild(m_pTheDPad);
    
    m_pContextMenu = CCMenu::create();
    CreateContextMenuButtons();
    
    this->addChild(m_pContextMenu, 0);
    
    this->scheduleUpdate();
    
    return true;
}

void HudLayer::CreateContextMenuButtons()
{
    Point buttonPositions [kContextMenuButton_Max] =
    {
        Point(64,-160),
        //PointPoint(180,64),
    };
    
    const char* buttonUpImages [kContextMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
        //"ui/btn_search.png",
    };
    const char* buttonDownImages [kContextMenuButton_Max] =
    {
        "res/ui/btn_talk.png",
        //"ui/btn_search.png",
    };
    
    ccMenuCallback buttonHandlers [kContextMenuButton_Max] =
    {
        CC_CALLBACK_1(HudLayer::onTalkButtonCallback, this),
        //CC_CALLBACK_1(HudLayer::onSearchButtonCallback, this),
    };
    
    MenuItemImage* tempButton;
    
    for (int i=0; i< kContextMenuButton_Max;++i)
    {
        tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pContextButtons[i] = tempButton;
    }
    
    for (int i=0;i<kContextMenuButton_Max;++i)
    {
        m_pContextMenu->addChild(m_pContextButtons[i]);
    }
}

void HudLayer::update(float delta)
{
}

//Accessors
SimpleDPad* HudLayer::getTheDPad()
{
    return m_pTheDPad;
}

void HudLayer::setContextButtonVisibility(ContextMenuButton theButton, bool isVisible)
{
    m_pContextButtons[theButton]->setVisible(isVisible);
}

bool HudLayer::getContextButtonVisibility(ContextMenuButton theButton)
{
    return m_pContextButtons[theButton]->isVisible();
}

//Callbacks
void HudLayer::onTalkButtonCallback(Ref* pSender)
{
    printf("Talk!\n");
    NPCManager* pTheManager = NPCManager::getInstance();
    pTheManager->interactWithClosestNPC();
}

void HudLayer::onSearchButtonCallback(Ref* pSender)
{
    printf("Search!\n");
}