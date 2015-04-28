//
//  MenuShopIntro.h
//  MiniRPG
//
//  Created by Matthew Barney on 4/21/15.
//
//

#ifndef MiniRPG_MenuShopIntro_h
#define MiniRPG_MenuShopIntro_h

#include "cocos2d.h"
#include "ChatBox.h"

USING_NS_CC;

enum MenuShopIntroButton
{
    kMenuShopIntroButton_Yes,
    kMenuShopIntroButton_No,
    kMenuShopIntroButtonButton_Max,
    kMenuShopIntroButton_None = -1,
};

class MenuShopIntro : public ChatBox
{
public:
    static MenuShopIntro* createMenuShopIntro(std::string npcName, std::string npcDialogue);
    static MenuShopIntro* create();
    
    bool initWithDialogueAndResponses(std::string npcName, std::string npcDialogue);
    virtual void advanceTextOrHide();
private:
    Menu* m_pMenu;
    MenuItemImage* m_pButtons[kMenuShopIntroButtonButton_Max];
    bool m_bChoiceMade;
    //MenuYesNoType m_eMenuType;
    
    void CreateMenuButtons();
    
    void onBuyButtonCallback(Ref* pSender);
    void onSellButtonCallback(Ref* pSender);
};
#endif
