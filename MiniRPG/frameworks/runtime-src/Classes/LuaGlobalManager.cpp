//
//  LuaGlobalManager.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/7/14.
//
//

#include "LuaGlobalManager.h"
#include "LuaBasicConversions.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
//#include "extensions/cocos-ext.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

USING_NS_CC;
//USING_NS_CC_EXT;

static int lua_npc_walk_with_direction(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    tolua_Error tolua_err;
    Vec2 direction;
    
    argc = lua_gettop(L);
    
    if (argc != 3)
    {
        tolua_error(L,"#ferror in function 'lua_npc_walk_with_direction', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    
    ok &= luaval_to_vec2(L, 2, &direction);
    if(!ok)
    {
        return 0;
    }
    
    if (!tolua_isboolean(L, 3, 0, &tolua_err))
    {
        tolua_error(L,"#ferror in function 'lua_npc_walk_with_direction'.",&tolua_err);
        return 0;
    }
    
    bool changedDirection = (bool)tolua_toboolean(L, 2, 0);
    NPCManager* pManager = NPCManager::getInstance();
    pManager->moveNPCWithDirection(npcName, direction, changedDirection);
    
    tolua_pushboolean(L, true);
	lua_setglobal(L, "gNPCIsMoving");
    
    return 0;
}

static int lua_npc_walk_numtiles_with_direction(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    //bool ok  = true;
    tolua_Error tolua_err;

    argc = lua_gettop(L);
    
    if (argc != 3)
    {
        tolua_error(L,"#ferror in function 'lua_npc_walk_numtiles_with_direction', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    int numTiles = (int)tolua_tonumber(L, 2, 0);
    std::string direction = tolua_tostring(L, 3, "");
    
    NPCManager* pManager = NPCManager::getInstance();
    pManager->walkNumTilesWithDirection(npcName, numTiles, direction);
    
    tolua_pushboolean(L, true);
	lua_setglobal(L, "gNPCIsMoving");
    
    return 0;
}

static int lua_npc_talk(lua_State* L)
{
    int argc = lua_gettop(L);
    tolua_Error tolua_err;
    
    if (argc != 2)
    {
        tolua_error(L,"#ferror in function 'lua_npc_walk_numtiles_with_direction', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    std::string dialogue = tolua_tostring(L, 2, "");
    
    NPCManager* pManager = NPCManager::getInstance();
    GameLayer* pGameLayer = pManager->getGameLayer();
    
    pManager->setNPCState(npcName, kActionStateTalking);
    pGameLayer->showNPCDialogue(npcName, dialogue, "", "");
    
    tolua_pushboolean(L, true);
	lua_setglobal(L, "gDialogueIsPresent");
    
    return 0;
}

static int lua_npc_yes_no_talk(lua_State* L)
{
    int argc = lua_gettop(L);
    tolua_Error tolua_err;
    
    if (argc != 4)
    {
        tolua_error(L,"#ferror in function 'lua_npc_walk_numtiles_with_direction', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    std::string dialogue = tolua_tostring(L, 2, "");
    std::string yes = tolua_tostring(L, 3, "");
    std::string no = tolua_tostring(L, 4, "");
    
    NPCManager* pManager = NPCManager::getInstance();
    GameLayer* pGameLayer = pManager->getGameLayer();
    
    pManager->setNPCState(npcName, kActionStateTalking);
    pGameLayer->showNPCDialogue(npcName, dialogue, yes, no);
    
    tolua_pushboolean(L, true);
	lua_setglobal(L, "gDialogueIsPresent");
    
    return 0;
}

static int lua_npc_set_walk_bounds(lua_State* L)
{
    int argc = lua_gettop(L);
    bool ok;
    Rect boundsRect;
    tolua_Error tolua_err;
    
    if (argc != 2)
    {
        tolua_error(L,"#ferror in function 'lua_npc_set_walk_bounds', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    
    ok &= luaval_to_rect(L, 2, &boundsRect);
    /*
    if(!ok)
    {
        printf("Expected cocos2d::Rect, got another type!\n");
        return 0;
    }
     */
    
    NPCManager* pManager = NPCManager::getInstance();
    GameLayer* pGameLayer = pManager->getGameLayer();
    
    Vec2 worldPos = pGameLayer->positionForTileCoord(Vec2(boundsRect.origin.x, boundsRect.origin.y));
    Rect convertedRect = Rect::Rect(worldPos.x, worldPos.y, boundsRect.size.width * kTileSize, boundsRect.size.height * kTileSize);
    
    pManager->setWalkBounds(npcName, convertedRect);
    
    return 0;
}

static int lua_npc_set_delay_between_steps(lua_State* L)
{
    int argc = lua_gettop(L);
    cocos2d::Rect boundsRect;
    tolua_Error tolua_err;
    
    if (argc != 2)
    {
        tolua_error(L,"#ferror in function 'lua_npc_set_delay_between_steps', too few arguments.",&tolua_err);
        return 0;
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    float fDelay = (float)tolua_tonumber(L, 2, 0);
    
    NPCManager* pManager = NPCManager::getInstance();
    pManager->setDelayBetweenSteps(npcName, fDelay);
    
    return 0;
}

int lua_flag_text_box_state(lua_State* L, bool textBoxState)
{
    tolua_pushboolean(L, textBoxState);
	lua_setglobal(L, "gDialogueIsPresent");
    
    return 0;
}

int lua_flag_npc_movement_state(lua_State* L, bool isMoving)
{
    tolua_pushboolean(L, isMoving);
	lua_setglobal(L, "gNPCIsMoving");
    
    return 0;
}

int register_globalluamanager(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L, NULL);
    tolua_function(L, "walkNumTilesWithDirection", lua_npc_walk_numtiles_with_direction);
    tolua_function(L, "walkWithDirection", lua_npc_walk_with_direction);
    tolua_function(L, "talk", lua_npc_talk);
    tolua_function(L, "talkYesNo", lua_npc_yes_no_talk);
    tolua_function(L, "setWalkBounds", lua_npc_set_walk_bounds);
    tolua_function(L, "setStepDelay", lua_npc_set_delay_between_steps);
    tolua_endmodule(L);
    return 0;
}
