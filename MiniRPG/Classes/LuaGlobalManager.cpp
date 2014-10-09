//
//  LuaGlobalManager.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/7/14.
//
//

#include "LuaGlobalManager.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

USING_NS_CC;
USING_NS_CC_EXT;

static int lua_cocos2dx_createDownloadDir(lua_State* L)
{
    return 0;
}

static int lua_cocos2dx_deleteDownloadDir(lua_State* L)
{
    return 0;
}

static int lua_npc_talk(lua_State* L)
{
    int argc = lua_gettop(L);
    
    if (argc < 2)
    {
        printf("Invalid number of arguments!");
    }
    
    std::string npcName = tolua_tostring(L, 1, "");
    std::string dialogue = tolua_tostring(L, 2, "");
    
    NPCManager* pManager = NPCManager::getInstance();
    GameLayer* pGameLayer = pManager->getGameLayer();
    
    pGameLayer->showNPCDialogue(npcName, dialogue);
    
    printf("success!\n");
    return 0;
}

int register_globalluamanager(lua_State* L)
{
    tolua_open(L);
    tolua_module(L, NULL, 0);
    tolua_beginmodule(L, NULL);
    tolua_function(L, "createDownloadDir", lua_cocos2dx_createDownloadDir);
    tolua_function(L, "deleteDownloadDir", lua_cocos2dx_deleteDownloadDir);
    tolua_function(L, "talk", lua_npc_talk);
    tolua_endmodule(L);
    return 0;
}
