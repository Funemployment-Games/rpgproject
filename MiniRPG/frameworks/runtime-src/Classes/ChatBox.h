//
//  ChatBox.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/6/14.
//
//

#ifndef MiniRPG_ChatBox_h
#define MiniRPG_ChatBox_h


#include "cocos2d.h"

USING_NS_CC;

class ChatBox : public cocos2d::Node
{
public:
    static ChatBox* createChatBox(std::string npcName, std::string npcDialogue);
    static ChatBox* create();
    
    bool initWithGameLayer(std::string npcName, std::string npcDialogue);
    
    void advanceTextOrHide();
private:
    std::string m_npcName;
    std::vector<std::string> m_textArray;
    Label* m_pLabel;
};

#endif
