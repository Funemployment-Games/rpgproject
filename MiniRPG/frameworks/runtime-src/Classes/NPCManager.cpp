//
//  NPCManager.cpp
//  MiniRPG
//
//  Created by Matthew Barney on 10/3/14.
//
//

#include "NPCManager.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef CC_TARGET_OS_IPHONE
#include <unistd.h>
#elif CC_PLATFORM_WIN32
#endif
#include <fcntl.h>
#include "config.h"

#include "GameLayer.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

// singleton stuff
static NPCManager *s_sharedNPCManager = nullptr;

NPCManager* NPCManager::getInstance()
{
    if (!s_sharedNPCManager)
    {
        s_sharedNPCManager = new (std::nothrow) NPCManager();
        CCASSERT(s_sharedNPCManager, "FATAL: Not enough memory");
        s_sharedNPCManager->init();
    }
    
    return s_sharedNPCManager;
}

// on "init" you need to initialize your instance
bool NPCManager::init()
{
    m_pLuaEngine = LuaEngine::getInstance();
    m_pLuaStack = m_pLuaEngine->getLuaStack();
    m_pLuaState   = m_pLuaStack->getLuaState();
    
    return true;
}

void NPCManager::setGameLayer(GameLayer* pGameLayer)
{
    //m_pNPCs = [@{} mutableCopy];
    m_pGameLayer = pGameLayer;
    
    if (m_pLuaState)
    {
        tolua_pushstring(m_pLuaState, "game");
        tolua_pushuserdata(m_pLuaState, m_pGameLayer);
        lua_settable(m_pLuaState, LUA_GLOBALSINDEX);
    }
}

GameLayer* NPCManager::getGameLayer()
{
    return m_pGameLayer;
}

void NPCManager::addNPC(NPCSprite* theNPC)
{
    m_vCurrentNPCs.pushBack(theNPC);
    lua_getglobal(m_pLuaState, "gNPCLUT");
    if (lua_istable(m_pLuaState, -1))
    {
        object_to_luaval<cocos2d::Sprite>(m_pLuaState, "cc.Sprite",(cocos2d::Sprite*)theNPC);
        
        //lua_pushlightuserdata(m_pLuaState, c);
        //lua_pushstring(m_pLuaState, "Test!");
        lua_setfield(m_pLuaState, -2, theNPC->getCharacterName().c_str());
        lua_setglobal(m_pLuaState,"gNPCLUT");
    }
}

void NPCManager::removeNPC(NPCSprite* theNPC)
{
    m_vCurrentNPCs.eraseObject(theNPC);
}

void NPCManager::removeAllNPCs()
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        m_pGameLayer->removeChild(currentNPC);
    }
    
    if (!m_vCurrentNPCs.empty())
    {
        m_vCurrentNPCs.clear();
    }
}

NPCSprite* NPCManager::getNPC(std::string npcName)
{
    NPCSprite* currentNPC = nullptr;
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            break;
        }
        else
        {
            currentNPC = nullptr;
        }
    }
    
    return currentNPC;
}

void NPCManager::update(float delta)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        //currentNPC->setPosition(currentNPC->getDesiredPosition());
        currentNPC->update(delta);
    }
}

void NPCManager::interactWithClosestNPC()
{
    if (m_pClosestNPC)
    {
        m_pClosestNPC->setActionState(kActionStateTalking);
        
        m_pGameLayer->showNPCDialogue(m_pClosestNPC);
    }
}

void NPCManager::moveNPCWithDirection(std::string npcName, Vec2 theDirection, bool directionDidChange)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            currentNPC->walkWithDirection(theDirection, directionDidChange);
            break;
        }
    }
}

void NPCManager::walkNumTilesWithDirection(std::string npcName, int numTiles, std::string direction)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            ActionSpriteDirection theDirection = currentNPC->directionStringToEnum(direction);
            currentNPC->setActionState(kActionStateAutoWalkStart);
            currentNPC->walkNumTilesWithDirection(numTiles, theDirection, true);
            break;
        }
    }
}

void NPCManager::setWalkBounds(std::string npcName, Rect bounds)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            currentNPC->setWalkBounds(bounds);
            break;
        }
    }
}

void NPCManager::setDelayBetweenSteps(std::string npcName, float theDelay)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            currentNPC->setDelayBetweenSteps(theDelay);
            break;
        }
    }
}

void NPCManager::setNPCState(std::string npcName, ActionState theState)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        if (currentNPC->getCharacterName() == npcName)
        {
            currentNPC->setActionState(theState);
            break;
        }
    }
}

NPCSprite* NPCManager::willHeroCollideWithAnyNPC(Vec2 herosDesiredPosition)
{
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        Vec2 npcPosition = currentNPC->getPosition();
        
        //printf("scanNPCLayer - Current desired tileCoord: %f, %f\n", tileCoord.x, tileCoord.y);
        //printf("scanNPCLayer - Current npcTileCoord: %f, %f\n", npcTileCoord.x, npcTileCoord.y);
        //printf("scanNPCLayer - Current desired Position: %f, %f\n", m_pHero->getDesiredPosition().x, m_pHero->getDesiredPosition().y);
        //printf("scanNPCLayer - Current npcPosition: %f, %f\n", npcPosition.x, npcPosition.y);
        
        bool intersectsX = ((npcPosition.x - kTileSize/2) < herosDesiredPosition.x && herosDesiredPosition.x < (npcPosition.x + kTileSize/2) );
        bool intersectsY = ((npcPosition.y - kTileSize/2) < herosDesiredPosition.y && herosDesiredPosition.y < (npcPosition.y + kTileSize/2) );
        
        if (intersectsX && intersectsY)
        {
            m_pClosestNPC = currentNPC;
            return m_pClosestNPC;
        }
    }
    
    return nullptr;
}

/**
 * For a given layer on a tile map, this method tries to load files of the format:
 * [MapName]-[NPCName].lua
 *
 * Lua files are responsible for initializing themselves and adding themselves to the
 * global npcs table.
 *
 * All Lua objects in the npcs table must have an interact method that will be invoked when
 * the player interacts with them.
 */
void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

void NPCManager::intializeNPCLua()
{    
    lua_newtable(m_pLuaState);
    lua_setfield(m_pLuaState, LUA_GLOBALSINDEX, "gNPCLUT");
}


/**
 * Executes Lua code and prints results to the console.
 */
void NPCManager::runLua(const char* luaCode)
{
#ifdef CC_TARGET_OS_IPHONE
    /*
    char buffer[256] = {0};
    int out_pipe[2];
    int saved_stdout;

    // Set up pipes for output
    saved_stdout = dup(STDOUT_FILENO);
    pipe(out_pipe);
    fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);
     */
#endif
    // Run Lua
    m_pLuaEngine->executeString(luaCode);
    
    // Grab the output
#ifdef CC_TARGET_OS_IPHONE
    /*
    int status = lua_pcall(m_pLuaState, 0, LUA_MULTRET, 0);
    
    // Report errors if there are any
    //printf("luaCode: %s\n", luaCode);
    report_errors(m_pLuaState, status);
    
    read(out_pipe[0], buffer, 255);
    dup2(saved_stdout, STDOUT_FILENO);
    
    // Print the output to the log
    std::string output = buffer;
    if(output.length() > 2)
    {
        printf("Lua: %s\n",output.c_str());
    }
     */
#endif
}

/**
 * Reports Lua errors to the console
 */
void NPCManager::report_errors(lua_State *L, int status)
{
    //TODO: I don't think this is working correctly...
    if ( status!=0 )
    {
        const char *error = lua_tostring(L, -1);
        printf("Lua Error: %s\n",error);
        lua_pop(L, 1); // remove error message
    }
}