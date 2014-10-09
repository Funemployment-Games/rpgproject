//
//  NPCManager.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/3/14.
//
//

#ifndef MiniRPG_NPCManager_h
#define MiniRPG_NPCManager_h

#include "cocos2d.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

USING_NS_CC;

class GameLayer;

class NPCManager : public cocos2d::Ref
{
public:
    static NPCManager* createNPCManager(GameLayer* pGameLayer);
    static NPCManager* create();
    
    bool initWithGameLayer(GameLayer* pGameLayer);
    
    void interactWithNPCNamed(std::string npcName);
    void loadNPCsForTileMap(TMXTiledMap* map, std::string  name);
    
private:
    void runLua(std::string luaCode);
    void report_errors(lua_State *L, int status);
    
    //Vector<int> m_pNPCs;
    lua_State* m_pLuaState;
    GameLayer* m_pGameLayer;
};

#endif
