//
//  YesNoBox.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/21/14.
//
//

#ifndef __MiniRPG__YesNoBox__
#define __MiniRPG__YesNoBox__

#include "cocos2d.h"
#include "ChatBox.h"

USING_NS_CC;

enum YesNoMenuButton
{
    kYesNoMenuButton_Yes,
    kYesNoMenuButton_No,
    kYesNoMenuButtonButton_Max,
    kYesNoMenuButton_None = -1,
};

enum YesNoMenuType
{
    kYesNoMenuType_Save,
    kYesNoMenuType_Purchase,
    KYesNoMenuType_Max,
    kYesNoMenuType_None = -1,
};

class YesNoBox : public ChatBox
{
public:
    static YesNoBox* createYesNoBox(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse);
    static YesNoBox* create();
    
    bool initWithDialogueAndResponses(std::string npcName, std::string npcDialogue, std::string yesResponse, std::string noResponse);
    virtual void advanceTextOrHide();
private:
    std::string m_strYesResponse;
    std::string m_strNoResponse;
    Menu* m_pMenu;
    MenuItemImage* m_pButtons[kYesNoMenuButtonButton_Max];
    bool m_bChoiceMade;
    YesNoMenuType m_eMenuType;
    
    void CreateMenuButtons();
    
    void onYesButtonCallback(Ref* pSender);
    void onNoButtonCallback(Ref* pSender);
};
#endif /* defined(__MiniRPG__YesNoBox__) */
