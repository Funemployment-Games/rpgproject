//
//  NPCManager.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/3/14.
//
//

#ifndef MiniRPG_NPCManager_h
#define MiniRPG_NPCManager_h

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "NPCSprite.h"

USING_NS_CC;

class GameLayer;

class NPCManager : public cocos2d::Ref
{
public:
    static NPCManager* create();
    static NPCManager* getInstance();
    
    bool init();
    
    //Accessors
    void setGameLayer(GameLayer* pGameLayer);
    GameLayer* getGameLayer();
    void addNPC(NPCSprite* theNPC);
    
    //Interaction
    void interactWithNPCNamed(std::string npcName);
    void interactWithClosestNPC();
    void moveNPCWithDirection(std::string npcName, Vec2 theDirection, bool directionDidChange);
    void walkNumTilesWithDirection( std::string npcName, int numTilesToMove, std::string directionToMove);
    void setWalkBounds(std::string npcName, Rect bounds);
    void setDelayBetweenSteps(std::string npcName, float theDelay);
    
    NPCSprite* willHeroCollideWithAnyNPC(Vec2 herosDesiredPosition);
    
    //Load
    void intializeNPCLua();
    
    void update(float delta);
    
private:
    void runLua(const char* luaCode);
    void report_errors(lua_State *L, int status);
    
    //Vector<int> m_pNPCs;
    LuaEngine* m_pLuaEngine;
    LuaStack* m_pLuaStack;
    lua_State* m_pLuaState;
    GameLayer* m_pGameLayer;
    NPCSprite* m_pClosestNPC;
    Vector<NPCSprite*> m_vCurrentNPCs;
};

#endif
