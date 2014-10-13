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

void NPCManager::setClosestNPCName(std::string closestNPC)
{
    m_closestNPC = closestNPC;
}

/**
 * Loads all NPCs on a given tile map.  Initialized empty Lua table to hold
 * NPCs in Lua.
 */
void NPCManager::interactWithNPCNamed(std::string npcName)
{
    std::string luaCode = "gNPCLUT[\"" + npcName + "\"]:interact()";
    runLua(luaCode.c_str());
}

void NPCManager::interactWithClosestNPC()
{
    if (std::strcmp(m_closestNPC.c_str(), STD_STRING_EMPTY.c_str()) != 0)
    {
        interactWithNPCNamed(m_closestNPC);
    }
}

void NPCManager::loadNPCsForTileMap(TMXTiledMap* map, std::string  name)
{
    // Reset NPCs for the current map
    runLua("gNPCLUT = {}");
    
    loadLuaFilesForMap(map,"npc", name);
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

void NPCManager::loadLuaFilesForMap(TMXTiledMap* map, std::string layerName, std::string name)
{
    //NSFileManager *manager = [NSFileManager defaultManager];
    TMXLayer* layer = map->getLayer(layerName);
    
    if (!layer)
    {
        printf("%s has no lua!\n", name.c_str());
        return;
    }

    // Enumerate the layer
    for(int i = 0; i < layer->getLayerSize().width; i++)
    {
        for(int j = 0; j < layer->getLayerSize().height; j++)
        {
            Vec2 tileCoord = Vec2(j,i);
            int tileGid = layer->getTileGIDAt(tileCoord);

            // Check to see if there is an NPC at this location
            if(tileGid)
            {
                // Fetch the name of the NPC
                Value tileValue = map->getPropertiesForGID(tileGid);
                if (tileValue.getType() != Value::Type::NONE)
                {
                    ValueMap properties = tileValue.asValueMap();
                    if (properties.size() > 0)
                    {
                        const std::string npcName = properties.at("name").asString();

                        // Resolve the path to the NPCs Lua file
                        std::string roomName = name;
                        //ReplaceStringInPlace(roomName, ".tmx", "");
                        std::string npcFilename = "lua/" + roomName + "-" + npcName + ".lua";
                        std::string fullPath    = FileUtils::getInstance()->fullPathForFilename(npcFilename);
                        std::string contentStr  = FileUtils::getInstance()->getStringFromFile(fullPath);

                        // If the NPC has a Lua file, initialize it.
                        if(contentStr != "")
                        {
                            runLua(contentStr.c_str());
                        }
                        else
                        {
                            printf("Warning: No Lua file for npc %s at path %s",npcName.c_str(),fullPath.c_str());
                        }
                    }
                }
            }
        }
    }
}


/**
 * Executes Lua code and prints results to the console.
 */
void NPCManager::runLua(const char* luaCode)
{
#ifdef CC_TARGET_OS_IPHONE
    char buffer[256] = {0};
    int out_pipe[2];
    int saved_stdout;

    // Set up pipes for output
    saved_stdout = dup(STDOUT_FILENO);
    pipe(out_pipe);
    fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);
#endif
    // Run Lua
    m_pLuaEngine->executeString(luaCode);
    
    // Grab the output
#ifdef CC_TARGET_OS_IPHONE
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
        printf("Lua: %s",output.c_str());
    }
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