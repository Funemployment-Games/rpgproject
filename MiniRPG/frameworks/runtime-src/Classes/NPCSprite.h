//
//  NPCSprite.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/14/14.
//
//

#ifndef MiniRPG_NPCSprite_h
#define MiniRPG_NPCSprite_h

#include "ActionSprite.h"

USING_NS_CC;

class NPCSprite: public ActionSprite
{
public:
    static Sprite* createNPC(std::string spriteName, std::string dialogueId, std::string dialogueYesId, std::string dialogueNoId);
    static Sprite* create();
    
    bool initWithParameters(std::string spriteName, std::string dialogueId, std::string dialogueYesId, std::string dialogueNoId);
    
    //scheduled methods
    virtual void update(float dt);
        
    //creation
    virtual void createActions();
    virtual void createWalkAction();
    virtual void createIdleAction();
    
    //Accessors
    std::string getDialogueId();
    std::string getYesDialogueId();
    std::string getNoDialogueId();
    void setDelayBetweenSteps(float theDelay);
    float getDelayBetweenSteps();
    void setWalkBounds(Rect bounds);
    Rect getWalkBounds();
    
    //Callbacks
    virtual void onFinishedWalkingCallback(Ref* pSender);

private:
    void determineNextTileToWalkTo();
    
    std::string m_strDialogueId;
    std::string m_strYesDialogueId;
    std::string m_strNoDialogueId;
    float m_fDelayBetweenSteps;
    float m_fTimeSinceLastStep;
};

#endif
