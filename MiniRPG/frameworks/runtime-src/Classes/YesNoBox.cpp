//
//  YesNoBox.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/21/14.
//
//

#include "YesNoBox.h"

YesNoBox* YesNoBox::createYesNoBox(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse)
{
    YesNoBox* box = new (std::nothrow) YesNoBox();
    if (box && box->initWithDialogueAndResponses(npcName, npcDialogue, yesResponse, noResponse))
    {
        box->autorelease();
        return box;
    }
    CC_SAFE_DELETE(box);
    return nullptr;
}

bool YesNoBox::initWithDialogueAndResponses(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse)
{
    m_strYesResponse = yesResponse;
    m_strNoResponse = noResponse;
    m_bChoiceMade = false;

    m_pMenu = CCMenu::create();
    CreateMenuButtons();
    this->addChild(m_pMenu, 0);
    m_pMenu->setVisible(false);
    
    return ChatBox::initWithDialogue(npcName, npcDialogue);
}

void YesNoBox::CreateMenuButtons()
{
    Point buttonPositions [kYesNoMenuButtonButton_Max] =
    {
        Point(-70,-300),
        Point(70,-300),
    };
    
    const char* buttonUpImages [kYesNoMenuButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    const char* buttonDownImages [kYesNoMenuButtonButton_Max] =
    {
        "res/ui/btn_yes.png",
        "res/ui/btn_no.png",
    };
    
    ccMenuCallback buttonHandlers [kYesNoMenuButtonButton_Max] =
    {
        CC_CALLBACK_1(YesNoBox::onYesButtonCallback, this),
        CC_CALLBACK_1(YesNoBox::onNoButtonCallback, this),
    };
    
    MenuItemImage* tempButton;
    
    for (int i=0; i< kYesNoMenuButtonButton_Max;++i)
    {
        tempButton = MenuItemImage::create(buttonUpImages[i],
                                           buttonDownImages[i],
                                           buttonHandlers[i]);
        tempButton->setPosition(buttonPositions[i]);
        m_pButtons[i] = tempButton;
    }
    
    for (int i=0;i<kYesNoMenuButtonButton_Max;++i)
    {
        m_pMenu->addChild(m_pButtons[i]);
    }
}

void YesNoBox::advanceTextOrHide()
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

void YesNoBox::onYesButtonCallback(Ref* pSender)
{
    printf("Yes!\n");
    std::string message = m_npcName + ": " +  m_strYesResponse;
    m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}

void YesNoBox::onNoButtonCallback(Ref* pSender)
{
    printf("NO!\n");
    std::string message = m_npcName + ": " +  m_strNoResponse;
    m_pLabel->setString(message);
    m_bChoiceMade = true;
    m_pMenu->setVisible(false);
}