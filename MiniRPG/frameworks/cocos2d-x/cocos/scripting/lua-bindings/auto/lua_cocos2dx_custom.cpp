#include "lua_cocos2dx_custom.hpp"
#include "NPCSprite.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_custom_NPCSprite_setWalkBounds(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_setWalkBounds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "NPCSprite:setWalkBounds");
        if(!ok)
            return 0;
        cobj->setWalkBounds(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:setWalkBounds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_setWalkBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_initWithParameters(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_initWithParameters'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        std::string arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "NPCSprite:initWithParameters");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "NPCSprite:initWithParameters");
        if(!ok)
            return 0;
        bool ret = cobj->initWithParameters(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:initWithParameters",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_initWithParameters'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_createIdleAction(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_createIdleAction'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_createIdleAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_update(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "NPCSprite:update");
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_getWalkBounds(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_getWalkBounds'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_getWalkBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_getScriptName(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_getScriptName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getScriptName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:getScriptName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_getScriptName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_onFinishedWalkingCallback(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_onFinishedWalkingCallback'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_onFinishedWalkingCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_createWalkAction(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_createWalkAction'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_createWalkAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_createActions(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_createActions'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_createActions'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_getDelayBetweenSteps(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_getDelayBetweenSteps'", nullptr);
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
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_getDelayBetweenSteps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_setDelayBetweenSteps(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_NPCSprite_setDelayBetweenSteps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "NPCSprite:setDelayBetweenSteps");
        if(!ok)
            return 0;
        cobj->setDelayBetweenSteps(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "NPCSprite:setDelayBetweenSteps",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_setDelayBetweenSteps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_NPCSprite_createNPC(lua_State* tolua_S)
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

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "NPCSprite:createNPC");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "NPCSprite:createNPC");
        if(!ok)
            return 0;
        cocos2d::Sprite* ret = NPCSprite::createNPC(arg0, arg1);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "NPCSprite:createNPC",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_createNPC'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_NPCSprite_create(lua_State* tolua_S)
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

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Sprite* ret = NPCSprite::create();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "NPCSprite:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_NPCSprite_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_NPCSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NPCSprite)");
    return 0;
}

int lua_register_cocos2dx_custom_NPCSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"NPCSprite");
    tolua_cclass(tolua_S,"NPCSprite","NPCSprite","ActionSprite",nullptr);

    tolua_beginmodule(tolua_S,"NPCSprite");
        tolua_function(tolua_S,"setWalkBounds",lua_cocos2dx_custom_NPCSprite_setWalkBounds);
        tolua_function(tolua_S,"initWithParameters",lua_cocos2dx_custom_NPCSprite_initWithParameters);
        tolua_function(tolua_S,"createIdleAction",lua_cocos2dx_custom_NPCSprite_createIdleAction);
        tolua_function(tolua_S,"update",lua_cocos2dx_custom_NPCSprite_update);
        tolua_function(tolua_S,"getWalkBounds",lua_cocos2dx_custom_NPCSprite_getWalkBounds);
        tolua_function(tolua_S,"getScriptName",lua_cocos2dx_custom_NPCSprite_getScriptName);
        tolua_function(tolua_S,"onFinishedWalkingCallback",lua_cocos2dx_custom_NPCSprite_onFinishedWalkingCallback);
        tolua_function(tolua_S,"createWalkAction",lua_cocos2dx_custom_NPCSprite_createWalkAction);
        tolua_function(tolua_S,"createActions",lua_cocos2dx_custom_NPCSprite_createActions);
        tolua_function(tolua_S,"getDelayBetweenSteps",lua_cocos2dx_custom_NPCSprite_getDelayBetweenSteps);
        tolua_function(tolua_S,"setDelayBetweenSteps",lua_cocos2dx_custom_NPCSprite_setDelayBetweenSteps);
        tolua_function(tolua_S,"createNPC", lua_cocos2dx_custom_NPCSprite_createNPC);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_NPCSprite_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(NPCSprite).name();
    g_luaType[typeName] = "NPCSprite";
    g_typeCast["NPCSprite"] = "NPCSprite";
    return 1;
}
TOLUA_API int register_all_cocos2dx_custom(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_custom_NPCSprite(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

