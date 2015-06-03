//
//  MenuShopIntro.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 4/21/15.
//
//

#include <stdio.h>

#include "MenuShopIntro.h"

MenuShopIntro* MenuShopIntro::createMenuShopIntro(std::string npcName, std::string npcDialogue)
{
    MenuShopIntro* menu = new (std::nothrow) MenuShopIntro();
    if (menu && menu->initWithDialogueAndResponses(npcName, npcDialogue))
    {
        menu->autorelease();
        return menu;
    }
    CC_SAFE_DELETE(menu);
    return nullptr;
}

bool MenuShopIntro::initWithDialogueAndResponses(std::string npcName, std::string npcDialogue)
{
    m_bChoiceMade = false;
    
    m_pMenu = CCMenu::create();
    CreateMenuButtons();
    this->addChild(m_pMenu, 0);
    m_pMenu->setVisible(false);
    
    return ChatBox::initWithDialogue(npcName, npcDialogue);
}

void MenuShopIntro::CreateMenuButtons()
{
    Point buttonPositions [kMenuShopIntroButtonButton_Max] =
    {
        Point(-70,-300),
        Point(70,-300),
    };
    
    const char* buttonUpImages [kMenuShopIntroButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    const char* buttonDownImages [kMenuShopIntroButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    
    ccMenuCallback buttonHandlers [kMenuShopIntroButtonButton_Max] =
    {
        CC_CALLBACK_1(MenuShopIntro::onBuyButtonCallback, this),
        CC_CALLBACK_1(MenuShopIntro::onSellButtonCallback, this),
    };
    
    MenuItemImage* tempButton;
    
    for (int i=0; i< kMenuShopIntroButtonButton_Max;++i)
    {
        tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pButtons[i] = tempButton;
    }
    
    for (int i=0;i<kMenuShopIntroButtonButton_Max;++i)
    {
        m_pMenu->addChild(m_pButtons[i]);
    }
}

void MenuShopIntro::advanceTextOrHide()
{
    if (m_pMenu->isVisible())
    {
        return;
    }
    
    if(m_textArray.size() == 0 && !m_bChoiceMade)
    {
        m_pMenu->setVisible(true);
        return;
    }
    
    if (m_bChoiceMade)
    {
        this->setVisible(false);
        return;
    }
    
    std::string text = m_textArray[0];
    m_textArray.erase(m_textArray.begin());
    
    std::string message = m_npcName + " " +  text;
    m_pLabel->setString(message);
}

void MenuShopIntro::onBuyButtonCallback(Ref* pSender)
{
    //std::string message = m_npcName + " " +  m_strYesResponse;
    //m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}

void MenuShopIntro::onSellButtonCallback(Ref* pSender)
{
    //std::string message = m_npcName + " " +  m_strNoResponse;
    //m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}