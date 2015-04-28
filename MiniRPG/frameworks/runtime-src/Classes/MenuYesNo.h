//
//  MenuYesNo.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/21/14.
//
//

#ifndef __MiniRPG__MenuYesNo__
#define __MiniRPG__MenuYesNo__

#include "cocos2d.h"
#include "ChatBox.h"

USING_NS_CC;

enum MenuYesNoButton
{
    kMenuYesNoButton_Yes,
    kMenuYesNoButton_No,
    kMenuYesNoButtonButton_Max,
    kMenuYesNoButton_None = -1,
};

enum MenuYesNoType
{
    kMenuYesNoType_Save,
    kMenuYesNoType_Purchase,
    KMenuYesNoType_Max,
    kMenuYesNoType_None = -1,
};

class MenuYesNo : public ChatBox
{
public:
    static MenuYesNo* createMenuYesNo(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse);
    static MenuYesNo* create();
    
    bool initWithDialogueAndResponses(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse);
    virtual void advanceTextOrHide();
private:
    std::string m_strYesResponse;
    std::string m_strNoResponse;
    Menu* m_pMenu;
    MenuItemImage* m_pButtons[kMenuYesNoButtonButton_Max];
    bool m_bChoiceMade;
    MenuYesNoType m_eMenuType;
    
    void CreateMenuButtons();
    
    void onYesButtonCallback(Ref* pSender);
    void onNoButtonCallback(Ref* pSender);
};
#endif /* defined(__MiniRPG__MenuYesNo__) */
