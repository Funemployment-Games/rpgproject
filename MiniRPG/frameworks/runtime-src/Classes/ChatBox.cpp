//
//  ChatBox.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/6/14.
//
//

#include "ChatBox.h"

ChatBox* ChatBox::createChatBox(std::string npcName, std::string npcDialogue)
{
    ChatBox* box = new (std::nothrow) ChatBox();
    if (box && box->initWithGameLayer(npcName, npcDialogue))
    {
        box->autorelease();
        return box;
    }
    CC_SAFE_DELETE(box);
    return nullptr;
}
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool ChatBox::initWithGameLayer(std::string npcName, std::string npcDialogue)
{
    m_npcName = npcName;
    
    m_textArray = split(npcDialogue, '\n');
    
    Sprite* backroundSprite = Sprite::create("res/ui/chat-box.png");
    backroundSprite->getTexture()->setAliasTexParameters();
    backroundSprite->setScale(4);
    backroundSprite->setPosition(Vec2(0,0));
    backroundSprite->setAnchorPoint(Vec2(0,0));
    this->addChild(backroundSprite, 0);

    m_pLabel = Label::createWithSystemFont("", "Helvetica", 16, Size(300,60), TextHAlignment::LEFT, TextVAlignment::TOP);
    m_pLabel->setColor(Color3B::WHITE);
    m_pLabel->setAnchorPoint(Vec2(0, 0));
    m_pLabel->setPosition(Vec2(6,15));
    
    this->addChild(m_pLabel, 1);
    
    return true;
}

void ChatBox::advanceTextOrHide()
{
    if(m_textArray.size() == 0)
    {
        this->setVisible(false);
        return;
    }
    
    std::string text = m_textArray[0];
    m_textArray.erase(m_textArray.begin());
    
    std::string message = m_npcName + ": " +  text;
    m_pLabel->setString(message);
}