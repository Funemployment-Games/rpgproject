//
//  LuaGlobalManager.h
//  MiniRPG
//
//  Created by Matthew Barney on 10/7/14.
//
//

#ifndef MiniRPG_LuaGlobalManager_h
#define MiniRPG_LuaGlobalManager_h

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "GameLayer.h"

TOLUA_API int register_globalluamanager(lua_State* tolua_S);

extern int lua_flag_text_box_state(lua_State* L, bool textBoxState);
extern int lua_flag_npc_movement_state(lua_State* L, bool isMoving);

#endif
