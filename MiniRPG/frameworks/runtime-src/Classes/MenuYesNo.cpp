//
//  MenuYesNo.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/21/14.
//
//

#include "MenuYesNo.h"

MenuYesNo* MenuYesNo::createMenuYesNo(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse)
{
    MenuYesNo* box = new (std::nothrow) MenuYesNo();
    if (box && box->initWithDialogueAndResponses(npcName, npcDialogue, yesResponse, noResponse))
    {
        box->autorelease();
        return box;
    }
    CC_SAFE_DELETE(box);
    return nullptr;
}

bool MenuYesNo::initWithDialogueAndResponses(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse)
{
    m_strYesResponse = yesResponse;
    m_strNoResponse = noResponse;
    m_bChoiceMade = false;

    m_pMenu = Menu::create();
    CreateMenuButtons();
    this->addChild(m_pMenu, 0);
    m_pMenu->setVisible(false);
    
    return ChatBox::initWithDialogue(npcName, npcDialogue);
}

void MenuYesNo::CreateMenuButtons()
{
    Point buttonPositions [kMenuYesNoButtonButton_Max] =
    {
        Point(-70,-300),
        Point(70,-300),
    };
    
    const char* buttonUpImages [kMenuYesNoButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    const char* buttonDownImages [kMenuYesNoButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    
    ccMenuCallback buttonHandlers [kMenuYesNoButtonButton_Max] =
    {
        CC_CALLBACK_1(MenuYesNo::onYesButtonCallback, this),
        CC_CALLBACK_1(MenuYesNo::onNoButtonCallback, this),
    };
    
    MenuItemImage* tempButton;
    
    for (int i=0; i< kMenuYesNoButtonButton_Max;++i)
    {
        tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pButtons[i] = tempButton;
    }
    
    for (int i=0;i<kMenuYesNoButtonButton_Max;++i)
    {
        m_pMenu->addChild(m_pButtons[i]);
    }
}

void MenuYesNo::advanceTextOrHide()
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

void MenuYesNo::onYesButtonCallback(Ref* pSender)
{
    std::string message = m_npcName + " " +  m_strYesResponse;
    m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}

void MenuYesNo::onNoButtonCallback(Ref* pSender)
{
    std::string message = m_npcName + " " +  m_strNoResponse;
    m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}