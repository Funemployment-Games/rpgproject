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

int lua_flag_text_box_state(lua_State* L, bool textBoxState)
{
    tolua_pushboolean(L, textBoxState);
	lua_setglobal(L, "gDialogueIsPresent");
    
    return 0;
}

int register_globalluamanager(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L, NULL);
    tolua_function(L, "talk", lua_npc_talk);
    tolua_function(L, "talkYesNo", lua_npc_yes_no_talk);
    tolua_endmodule(L);
    return 0;
}