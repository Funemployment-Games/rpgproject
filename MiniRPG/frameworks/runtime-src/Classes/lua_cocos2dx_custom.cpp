#include "lua_cocos2dx_custom.hpp"
#include "NPCSprite.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"



int lua_ActionSprite_setActionState(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_setActionState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        _ActionState arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setActionState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:setActionState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_setActionState'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_setVelocity(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_setVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setVelocity(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:setVelocity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_setVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_getVelocity(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_getVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vec2 ret = cobj->getVelocity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:getVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_getVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_getCharacterName(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_getCharacterName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getCharacterName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:getCharacterName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_getCharacterName'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_getDesiredPosition(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_getDesiredPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vec2 ret = cobj->getDesiredPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:getDesiredPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_getDesiredPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_walkNumTilesWithDirection(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_walkNumTilesWithDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        _ActionSpriteDirection arg1;
        bool arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        ok &= luaval_to_boolean(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->walkNumTilesWithDirection(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:walkNumTilesWithDirection",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_walkNumTilesWithDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_createIdleAction(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_createIdleAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createIdleAction();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:createIdleAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_createIdleAction'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_update(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_update'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_walkWithDirection(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_walkWithDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        bool arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->walkWithDirection(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:walkWithDirection",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_walkWithDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_idle(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_idle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->idle();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:idle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_idle'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_setCharacterName(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_setCharacterName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setCharacterName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:setCharacterName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_setCharacterName'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_createWalkAction(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_createWalkAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createWalkAction();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:createWalkAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_createWalkAction'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_createActions(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_createActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createActions();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:createActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_createActions'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_getActionState(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_getActionState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getActionState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:getActionState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_getActionState'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_setPosition(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_setPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setPosition(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:setPosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_setPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_walkOneTileInCurrentDirection(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_walkOneTileInCurrentDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->walkOneTileInCurrentDirection();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:walkOneTileInCurrentDirection",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_walkOneTileInCurrentDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_onFinishedWalkingCallback(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_onFinishedWalkingCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
            return 0;
        cobj->onFinishedWalkingCallback(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:onFinishedWalkingCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_onFinishedWalkingCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_setDesiredPosition(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_setDesiredPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setDesiredPosition(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:setDesiredPosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_setDesiredPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_ActionSprite_directionStringToEnum(lua_State* tolua_S)
{
    int argc = 0;
    ActionSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ActionSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ActionSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_ActionSprite_directionStringToEnum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        int ret = (int)cobj->directionStringToEnum(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ActionSprite:directionStringToEnum",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_ActionSprite_directionStringToEnum'.",&tolua_err);
#endif

    return 0;
}
static int lua_ActionSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ActionSprite)");
    return 0;
}

int lua_register_ActionSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ActionSprite");
    tolua_cclass(tolua_S,"ActionSprite","ActionSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"ActionSprite");
        tolua_function(tolua_S,"setActionState",lua_ActionSprite_setActionState);
        tolua_function(tolua_S,"setVelocity",lua_ActionSprite_setVelocity);
        tolua_function(tolua_S,"getVelocity",lua_ActionSprite_getVelocity);
        tolua_function(tolua_S,"getCharacterName",lua_ActionSprite_getCharacterName);
        tolua_function(tolua_S,"getDesiredPosition",lua_ActionSprite_getDesiredPosition);
        tolua_function(tolua_S,"walkNumTilesWithDirection",lua_ActionSprite_walkNumTilesWithDirection);
        tolua_function(tolua_S,"createIdleAction",lua_ActionSprite_createIdleAction);
        tolua_function(tolua_S,"update",lua_ActionSprite_update);
        tolua_function(tolua_S,"walkWithDirection",lua_ActionSprite_walkWithDirection);
        tolua_function(tolua_S,"idle",lua_ActionSprite_idle);
        tolua_function(tolua_S,"setCharacterName",lua_ActionSprite_setCharacterName);
        tolua_function(tolua_S,"createWalkAction",lua_ActionSprite_createWalkAction);
        tolua_function(tolua_S,"createActions",lua_ActionSprite_createActions);
        tolua_function(tolua_S,"getActionState",lua_ActionSprite_getActionState);
        tolua_function(tolua_S,"setPosition",lua_ActionSprite_setPosition);
        tolua_function(tolua_S,"walkOneTileInCurrentDirection",lua_ActionSprite_walkOneTileInCurrentDirection);
        tolua_function(tolua_S,"onFinishedWalkingCallback",lua_ActionSprite_onFinishedWalkingCallback);
        tolua_function(tolua_S,"setDesiredPosition",lua_ActionSprite_setDesiredPosition);
        tolua_function(tolua_S,"directionStringToEnum",lua_ActionSprite_directionStringToEnum);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ActionSprite).name();
    g_luaType[typeName] = "ActionSprite";
    g_typeCast["ActionSprite"] = "ActionSprite";
    return 1;
}

int lua_NPCSprite_setWalkBounds(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_setWalkBounds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setWalkBounds(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:setWalkBounds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_setWalkBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_initWithParameters(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_initWithParameters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        int arg4;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_std_string(tolua_S, 2,&arg2);
        ok &= luaval_to_std_string(tolua_S, 3,&arg3);
        ok &= luaval_to_int32(tolua_S, 4,&arg4);
        
        if(!ok)
            return 0;
        bool ret = cobj->initWithParameters(arg0, arg1, arg2, arg3, (NPCType)arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:initWithParameters",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_initWithParameters'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_createIdleAction(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_createIdleAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createIdleAction();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:createIdleAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_createIdleAction'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_update(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_update'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_getWalkBounds(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_getWalkBounds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getWalkBounds();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:getWalkBounds",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_getWalkBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_getDialogueId(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_getScriptName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getDialogueId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:getScriptName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_getScriptName'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_onFinishedWalkingCallback(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_onFinishedWalkingCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
            return 0;
        cobj->onFinishedWalkingCallback(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:onFinishedWalkingCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_onFinishedWalkingCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_createWalkAction(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_createWalkAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createWalkAction();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:createWalkAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_createWalkAction'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_createActions(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_createActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->createActions();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:createActions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_createActions'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_getDelayBetweenSteps(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_getDelayBetweenSteps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDelayBetweenSteps();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:getDelayBetweenSteps",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_getDelayBetweenSteps'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_setDelayBetweenSteps(lua_State* tolua_S)
{
    int argc = 0;
    NPCSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NPCSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_NPCSprite_setDelayBetweenSteps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDelayBetweenSteps(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:setDelayBetweenSteps",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_setDelayBetweenSteps'.",&tolua_err);
#endif

    return 0;
}
int lua_NPCSprite_createNPC(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"NPCSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        int arg4;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        ok &= luaval_to_std_string(tolua_S, 3,&arg2);
        ok &= luaval_to_std_string(tolua_S, 4,&arg3);
        ok &= luaval_to_int32(tolua_S, 5,&arg4);
        
        
        if(!ok)
            return 0;
        cocos2d::Sprite* ret = NPCSprite::createNPC(arg0, arg1, arg2, arg3, (NPCType)arg4);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "NPCSprite:createNPC",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_NPCSprite_createNPC'.",&tolua_err);
#endif
    return 0;
}
static int lua_NPCSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NPCSprite)");
    return 0;
}

int lua_register_NPCSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"NPCSprite");
    tolua_cclass(tolua_S,"NPCSprite","NPCSprite","ActionSprite",nullptr);

    tolua_beginmodule(tolua_S,"NPCSprite");
        tolua_function(tolua_S,"setWalkBounds",lua_NPCSprite_setWalkBounds);
        tolua_function(tolua_S,"initWithParameters",lua_NPCSprite_initWithParameters);
        tolua_function(tolua_S,"createIdleAction",lua_NPCSprite_createIdleAction);
        tolua_function(tolua_S,"update",lua_NPCSprite_update);
        tolua_function(tolua_S,"getWalkBounds",lua_NPCSprite_getWalkBounds);
        tolua_function(tolua_S,"getDialogueID",lua_NPCSprite_getDialogueId);
        tolua_function(tolua_S,"onFinishedWalkingCallback",lua_NPCSprite_onFinishedWalkingCallback);
        tolua_function(tolua_S,"createWalkAction",lua_NPCSprite_createWalkAction);
        tolua_function(tolua_S,"createActions",lua_NPCSprite_createActions);
        tolua_function(tolua_S,"getDelayBetweenSteps",lua_NPCSprite_getDelayBetweenSteps);
        tolua_function(tolua_S,"setDelayBetweenSteps",lua_NPCSprite_setDelayBetweenSteps);
        tolua_function(tolua_S,"createNPC", lua_NPCSprite_createNPC);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(NPCSprite).name();
    g_luaType[typeName] = "NPCSprite";
    g_typeCast["NPCSprite"] = "NPCSprite";
    return 1;
}
TOLUA_API int register_all_spritelua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_ActionSprite(tolua_S);
	lua_register_NPCSprite(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

