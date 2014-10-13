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
    void setClosestNPCName(std::string closestNPC);
    
    //Interaction
    void interactWithNPCNamed(std::string npcName);
    void interactWithClosestNPC();
    
    //Load
    void loadNPCsForTileMap(TMXTiledMap* map, std::string  name);
    void loadLuaFilesForMap(TMXTiledMap* map, std::string layerName, std::string name);
    
private:
    void runLua(const char* luaCode);
    void report_errors(lua_State *L, int status);
    
    //Vector<int> m_pNPCs;
    LuaEngine* m_pLuaEngine;
    LuaStack* m_pLuaStack;
    lua_State* m_pLuaState;
    GameLayer* m_pGameLayer;
    std::string m_closestNPC;
};

#endif
