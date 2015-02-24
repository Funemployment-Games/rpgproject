#include "GameLayer.h"

USING_NS_CC;

#define MAXTILEMAPSIZE 128

Layer* GameLayer::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // register lua engine
    m_pLuaEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(m_pLuaEngine);
    m_pLuaStack = m_pLuaEngine->getLuaStack();
    m_pLuaState   = m_pLuaStack->getLuaState();
    register_globalluamanager(m_pLuaStack->getLuaState());
    register_all_spritelua(m_pLuaStack->getLuaState());
    
    m_pLuaEngine->executeScriptFile("res/lua/globalmanager.lua");
    
    m_pNPCManager = NPCManager::getInstance();
    m_pNPCManager->setGameLayer(this);
    m_pNPCManager->retain();
    
    loadSavedData();
    
    m_currentStringTable.SetArray();
	m_pTileMap = nullptr;
    loadMapNamed(m_strCurrentMapName);
    
	m_pHero = nullptr;
    initTheHeros();
    
    // Enable touches TODO: What is the non deprecated way to do this?
    setTouchEnabled(true);
    
	m_pChatbox = nullptr;

    this->scheduleUpdate();
    
    
    return true;
}

bool GameLayer::loadSavedData()
{
    // Load the list of quest flags from JSON.
    //ssize_t filesize = 0;
    std::string fullPath = "res/data/questflags.json";
    
	Data fileData = FileUtils::getInstance()->getDataFromFile(fullPath.c_str());
	unsigned char* charData = fileData.getBytes();
	std::string content(reinterpret_cast<char*>(charData));
	size_t pos = content.rfind("}");
	content = content.substr(0, pos + 1);
	//delete[] charData;
    
    rapidjson::Document questFlagsJSON;
    questFlagsJSON.Parse<0>(content.c_str());
    
    if ( questFlagsJSON.HasParseError() )
    {
        // report to the user the failure
		printf("Error parsing questflags.json %s\n", questFlagsJSON.GetParseError());
        return false;
    }
    
    // Load the player's save data.
    content = "";
    fullPath = "res/data/initialconfig.json"; // TODO: replace with save file.
    
	fileData = FileUtils::getInstance()->getDataFromFile(fullPath.c_str());
	charData = charData = fileData.getBytes();
	content = reinterpret_cast<char*>(charData);
	pos = content.rfind("}");
	content = content.substr(0, pos + 1);
	//delete[] charData;
    
    rapidjson::Document gameConfigJSON;
    gameConfigJSON.Parse<0>(content.c_str());
    
    if ( gameConfigJSON.HasParseError() )
    {
        // report to the user the failure
        printf("Error parsing initialconfig.json %s\n", gameConfigJSON.GetParseError() );
        return false;
    }
    
    //Read the players quest flags from save data.
    const rapidjson::Value& a = gameConfigJSON["QuestFlags"]; // Using a reference for consecutive access is handy and faster.
    assert(a.IsArray());
    std::vector<bool> vQuestFlags;
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) // rapidjson uses SizeType instead of size_t.
    {
        //printf("QuestFlags[%d] = %s\n", i, a[i].GetBool()? "true" : "false");
        vQuestFlags.push_back(a[i].GetBool());
    }
    
    //Set the global lua table for quest flags
    lua_getglobal(m_pLuaState, "gQuestFlagsLUT");
    if (lua_istable(m_pLuaState, -1))
    {
        
        int index = 0;
        for (rapidjson::Value::ConstMemberIterator itr = questFlagsJSON.MemberonBegin();
             itr != questFlagsJSON.MemberonEnd();
             ++itr)
        {
            //printf("member is %s %s\n", itr->name.GetString(), vQuestFlags[index] ? "true" : "false");

            lua_pushboolean(m_pLuaState, vQuestFlags[index]);
            lua_setfield(m_pLuaState, -2, itr->name.GetString());
            ++index;
        }
    }
    lua_setglobal(m_pLuaState,"gQuestFlagsLUT");
    
    // Set the rest of the game's state from the player's save data.
    m_strCurrentMapName = gameConfigJSON["CurrentMap"].GetString();
    
    //The game objects for the player's party aren't constructed until after the save data is loaded
    //How do we get that data from this function into the players?
    //Maybe there is a separate game object for the "party" than there is for the visual sprite?
    
    return true;
}

bool GameLayer::loadStringTable(std::string fileName)
{
    //std::string fullPath = "res/data/questflags.json";
    
    Data fileData = FileUtils::getInstance()->getDataFromFile(fileName.c_str());
    unsigned char* charData = fileData.getBytes();
    std::string content(reinterpret_cast<char*>(charData));
    size_t pos = content.rfind("}");
    content = content.substr(0, pos + 1);
    //delete[] charData;
    
    m_currentStringTable.Parse<0>(content.c_str());
    
    if ( m_currentStringTable.HasParseError() )
    {
        // report to the user the failure
        printf("Error parsing %s %s\n", fileName.c_str(), m_currentStringTable.GetParseError());
        return false;
    }
    
    return true;
}

/**
 * Loads a tilemap from the bundle path with a given name.
 *
 */
void GameLayer::loadMapNamed(std::string mapName)
{
    if(m_pTileMap)
    {
        m_pTileMap->removeAllChildrenWithCleanup(true);
        this->removeChild(m_pTileMap, true);
        m_pTileMap = nullptr;
    }
    
    m_pNPCManager->removeAllNPCs();
    
    std::string fileExtension = ".tmx";
    std::string fileNameWithExtension = "res/maps/" + mapName + fileExtension;
    printf("Loading map: %s\n",fileNameWithExtension.c_str());
    m_pTileMap = TMXTiledMap::create(fileNameWithExtension);
    this->addChild(m_pTileMap, -6);
    m_pMetaLayer = m_pTileMap->getLayer("meta");
    m_pMetaLayer->setVisible(false);
    m_pExitGroup = m_pTileMap->getObjectGroup("exits");
    
    Size winSize = Director::getInstance()->getWinSize();
    m_fHalfWinWidth = winSize.width / 2;
    m_fHalfWinHeight = winSize.height / 2;
    m_vCenterOfView = Vec2(m_fHalfWinWidth, m_fHalfWinHeight);
    
    m_fMapRealWidth = m_pTileMap->getMapSize().width * kTileSize;
    m_fMapRealHeight =  m_pTileMap->getMapSize().height * kTileSize;
    
    m_pNPCSpawnGroup = m_pTileMap->getObjectGroup("npc");
    if (m_pNPCSpawnGroup)
    {
        initTheNPCs(mapName);
    }
    
    std::string mapScript = "res/lua/" + mapName + ".lua";
    m_pLuaEngine->executeScriptFile(mapScript.c_str());
}

void GameLayer::initTheHeros()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/characters/heroine/heroine.plist");
    //TODO: maybe look into creating a super texture with all the character and npc sprites for more efficient drawing.
    m_pActors = SpriteBatchNode::create("res/characters/heroine/heroine.pvr.ccz");

    m_pActors->getTexture()->setAliasTexParameters();
    this->addChild(m_pActors, -5);
    
    m_pHero = (HeroSprite*)HeroSprite::createHero("heroine");
    //m_pActors->addChild(m_pHero);
    auto startGroup = m_pTileMap->getObjectGroup("start");
    ValueMap startPoint = startGroup->getObject("HeroStart");
    int startX = startPoint["x"].asInt();
    int startY = startPoint["y"].asInt();
    m_pHero->setPosition(Vec2(startX, startY));
    m_pHero->setDesiredPosition(Vec2(startX, startY));

    //printf("\ninitTheHeros - m_pHero x: %f, m_pHero y: %f\n", m_pHero->getPosition().x, m_pHero->getPosition().y);
    //Vec2 playerTileCoords = tileCoordForPosition(Vec2(m_pHero->getPosition().x, m_pHero->getPosition().y));
    //printf("initTheHeros - playerTileCoords: %f, playerTileCoords: %f\n", playerTileCoords.x, playerTileCoords.y);
    //Vec2 playerActualPos = positionForTileCoord(playerTileCoords);
    //printf("initTheHeros - playerActualPos: %f, playerActualPos: %f\n", playerActualPos.x, playerActualPos.y);
    
    m_pHero->setScale(1.0f);
    m_pHero->setAnchorPoint(Vec2(0.0,0.0));
	m_pHero->setLocalZOrder(-5);
	this->addChild(m_pHero, m_pTileMap->getLayer("floor")->getLocalZOrder());
    m_pHero->idle();
}

void GameLayer::initTheNPCs(std::string mapName)
{
    m_pNPCManager->intializeNPCLua();
    ValueVector npcs = m_pNPCSpawnGroup->getObjects();
    for(int i=0;i<npcs.size();++i)
    {
        ValueMap npc = npcs[i].asValueMap();
        std::string basesprite = npc["basesprite"].asString();
        std::string dialogueId  = npc["dialogueId"].asString();
        std::string dialogueYesId  = npc["dialogueYesId"].asString();
        std::string dialogueNoId  = npc["dialogueNoId"].asString();
        std::string npcName = npc["npcname"].asString();
        float x = npc["x"].asFloat();
        float y = npc["y"].asFloat();
        float width = npc["width"].asFloat();
        float height = npc["height"].asFloat();
        Rect walkBounds = Rect::Rect(x, y, width, height);
                
        NPCSprite* npcSprite = (NPCSprite*)NPCSprite::createNPC(basesprite, dialogueId, dialogueYesId, dialogueNoId);
        npcSprite->setDesiredPosition(Vec2(x, y));
        npcSprite->setPosition(Vec2(x, y));
        npcSprite->setScale(1.0f);
        npcSprite->setAnchorPoint(Vec2(0.,0.0));
		npcSprite->setLocalZOrder(-5);
        npcSprite->setCharacterName(npcName);
        npcSprite->setWalkBounds(walkBounds);
        
		this->addChild(npcSprite, m_pTileMap->getLayer("floor")->getLocalZOrder());
        npcSprite->idle();
        
        m_pNPCManager->addNPC(npcSprite);
    }
}

/**
 * Keeps the viewpoint centered as the hero is walking
 */
void GameLayer::update(float delta)
{
    if (m_pHero)
    {
        //Vec2 tileCoord = tileCoordForPosition(m_pHero->getDesiredPosition());
        //printf("Update - Current TileCoordinates: %f, %f\n", tileCoord.x, tileCoord.y);
        
        m_pHero->update(delta);
        setPlayerPosition(m_pHero->getDesiredPosition());
        setViewpointCenter(m_pHero->getPosition());
        heroIsDoneWalking();
    }
    
    if (m_pNPCManager)
    {
        m_pNPCManager->update(delta);
    }
    
    m_pLuaEngine->executeString("gCurrentMap:tick()");
}

// Accessors
void GameLayer::setTheHudLayer(HudLayer* theHudLayer)
{
    m_pHudLayer = theHudLayer;
    
    for (int i=0; i<kContextMenuButton_Max;++i)
    {
        m_pHudLayer->setContextButtonVisibility((ContextMenuButton)i, false);
    }
}

HeroSprite* GameLayer::getTheHero()
{
    return m_pHero;
}

LuaEngine* GameLayer::getLuaEngine()
{
    return m_pLuaEngine;
}

/**
 * Centers the view on our character.  If the character is near the edge
 * of the map, the view won't change.  Only the character will move.
 *
 */
void GameLayer::setViewpointCenter(Vec2 position)
{
    int maxX = MAX(position.x, m_fHalfWinWidth);
    int maxY = MAX(position.y, m_fHalfWinHeight);

    int minX = MIN(maxX, (m_fMapRealWidth) - m_fHalfWinWidth);
    int minY = MIN(maxY, (m_fMapRealHeight) - m_fHalfWinHeight);
    
    Vec2 actualPosition = Vec2(minX, minY);

    Vec2 viewPoint = m_vCenterOfView - actualPosition;
    
    this->setPosition(viewPoint);
}

/**
 * Allow touches
 */
//bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	return ;
}

/**
 * Invokes player movement or dissmisal of the chat window.
 */
//void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    if(m_pChatbox)
    {
        if (m_pChatbox->isVisible())
        {
            m_pChatbox->advanceTextOrHide();
        }
        
        if (!m_pChatbox->isVisible())
        {
            this->removeChild(m_pChatbox, true);
            //delete m_pChatbox;
            m_pChatbox = nullptr;
            m_pNPCManager->setNPCState(m_strCurrentTalkingNPC, kActionStateIdle);
            lua_flag_text_box_state(m_pLuaState, false);
            m_pHudLayer->setVisible(true);
        }
        return;
    }
    return;
}

/**
 * Moves the player to a given position. Also performs collision detection
 * against the meta layer for tiles with the property "Collidable" set
 * to true.
 *
 * If the player encounters an NPC or an item, they are no permitted to move
 * and the logic is handed off to the NPCManager to execut the related lua
 * script.
 */
void GameLayer::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = tileCoordForPosition(position);
    
    //printf("\nsetPlayerPosition - Current TileCoordinates: %f, %f\n", tileCoord.x, tileCoord.y);
    //printf("setPlayerPosition - Current desiredPosition: %f, %f\n", position.x, position.y);
    
    //position = wrapWoldMap(tileCoord, position);
    
    //printf("setPlayerPosition - Current positionFromTileCoord: %f, %f\n", position.x, position.y);
    
    // Check walls
    if (scanMetaLayer(tileCoord))
    {
        m_pHero->idle();
        return;
    }

    
    //Check NPCs
    if (m_pNPCSpawnGroup)
    {
        if (scanNPCLayer(tileCoord))
        {
            m_pHero->idle();
            return;
        }
    }
    
    /*
    if (m_pTreasureLayer)
    {
        if (scanTreasureLayer(tileCoord))
        {
            return;
        }
    }
     */
    
    //m_pHero->setPosition(position);
    m_pHero->walkOneTileInCurrentDirection();
}

bool GameLayer::scanMetaLayer(Vec2 tileCoord)
{
    //printf("scanMetaLayer - Current TileCoordinates: %f, %f\n", tileCoord.x, tileCoord.y);
    
    int tileGid = m_pMetaLayer->getTileGIDAt(tileCoord);
    
    if (tileGid)
    {
        Value tileValue = m_pTileMap->getPropertiesForGID(tileGid);
        if (tileValue.getType() != Value::Type::NONE)
        {
            ValueMap properties = tileValue.asValueMap();
            if (properties.size() > 0)
            {
                const std::string collision = properties.at("collidable").asString();
                //printf("%s at %f, %f\n",collision.c_str(), tileCoord.x, tileCoord.y);
                if (collision.compare("true") == 0)
                {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool GameLayer::scanNPCLayer(Vec2 tileCoord)
{
    NPCSprite* collidedSprite = m_pNPCManager->willHeroCollideWithAnyNPC(m_pHero->getDesiredPosition());
     if (collidedSprite)
     {
         if (!m_pHudLayer->getContextButtonVisibility(kContextMenuButton_Talk))
         {
             printf("Collided with: %s\n",collidedSprite->getCharacterName().c_str());
             m_pHudLayer->setContextButtonVisibility(kContextMenuButton_Talk, true);
         }
         return true;
     }
     else
     {
         if (m_pHudLayer->getContextButtonVisibility(kContextMenuButton_Talk))
         {
             m_pHudLayer->setContextButtonVisibility(kContextMenuButton_Talk, false);
         }
     }
    
    return false;
}

bool GameLayer::scanTreasureLayer(Vec2 tileCoord)
{
    return false;
}

Vec2 GameLayer::wrapWoldMap(Vec2 tileCoord, Vec2 worldPosition)
{
    if (tileCoord.x > (MAXTILEMAPSIZE - kTileSize/4))
    {
        tileCoord.x = kTileSize/4;
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.x < kTileSize/4)
    {
        tileCoord.x = (MAXTILEMAPSIZE - kTileSize/4);
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.y > (MAXTILEMAPSIZE - kTileSize/4))
    {
        tileCoord.y = kTileSize/4;
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.y < kTileSize/4)
    {
        tileCoord.y = (MAXTILEMAPSIZE - kTileSize/4);
        worldPosition = positionForTileCoord(tileCoord);
    }
    
    return worldPosition;
}

/**
 * Called after the hero is done with his walk sequence
 */
void GameLayer::heroIsDoneWalking()
{
    if (m_pHero->getActionState() != kActionStateIdle)
    {
        //printf("m_pHero x: %f, m_pHero y: %f\n", m_pHero->getPosition().x, m_pHero->getPosition().y);
        Vec2 playerTileCoords = tileCoordForPosition(Vec2(m_pHero->getPosition().x, m_pHero->getPosition().y));
        //printf("playerTileCoords: %f, playerTileCoords: %f\n", playerTileCoords.x, playerTileCoords.y);
        return;
    }

    if (m_pExitGroup)
    {
        ValueVector exits = m_pExitGroup->getObjects();
        for(int i=0;i<exits.size();++i)
        {
            ValueMap exit = exits[i].asValueMap();
            float x = exit["x"].asFloat();
            float y = exit["y"].asFloat();
            float width = exit["width"].asFloat()/16;
            float height = exit["height"].asFloat()/16;
            
            Rect exitRect = Rect(x, y, width, height);
            
            if (exitRect.containsPoint(m_pHero->getPosition()))
            {
                //printf("exitRect.x: %f, exitRect.y: %f\n", exitRect.origin.x, exitRect.origin.y);
                Vec2 exitRectTileCoords = tileCoordForPosition(Vec2(exitRect.origin.x, exitRect.origin.y));
                //printf("exitRectTileCoords: %f, exitRectTileCoords: %f\n", exitRectTileCoords.x, exitRectTileCoords.y);
                
                //printf("m_pHero x: %f, m_pHero y: %f\n", m_pHero->getPosition().x, m_pHero->getPosition().y);
                Vec2 playerTileCoords = tileCoordForPosition(Vec2(m_pHero->getPosition().x, m_pHero->getPosition().y));
                //printf("playerTileCoords: %f, playerTileCoords: %f\n", playerTileCoords.x, playerTileCoords.y);
                
                
                m_strCurrentMapName = exit.at("destination").asString();
                loadMapNamed(m_strCurrentMapName);
                
                Vec2 posFromTileCoord = positionForTileCoord(Vec2(exit["startx"].asFloat(), exit["starty"].asFloat()));
                //printf("posFromTileCoord.x %f, posFromTileCoord.y %f\n", posFromTileCoord.x, posFromTileCoord.y);
                //printf("TileCoord.x %f, TileCoord.y %f\n", exit["startx"].asFloat(), exit["starty"].asFloat());
                
                m_pHero->idle();
                m_pHero->setDesiredPosition(posFromTileCoord);
                m_pHero->setPosition(posFromTileCoord);
				m_pHero->setLocalZOrder(-5);
                m_pHero->simpleDPadTouchEnded();
                return;
            }
        }
    }
}


/**
 * Given a point on the map, returns the tile coordinate for that point.
 */
Vec2 GameLayer::tileCoordForPosition(Vec2 position)
{
    int x = position.x / (kTileSize);
    int y = ((m_fMapRealHeight) - position.y) / (kTileSize) -1;
    return Vec2(x, y);
}

/**
 * Given a tile coordinate, returns the position on screen
 */
Vec2 GameLayer::positionForTileCoord(Vec2 tileCoord)
{
    int x = (tileCoord.x * kTileSize);
    int y = (m_fMapRealHeight) - (tileCoord.y * kTileSize) - kTileSize;
    
    return Vec2(x, y);
}

void GameLayer::showNPCDialogue(std::string npcName, std::string stringID, std::string yesResponse, std::string noResponse)
{
    if (m_pChatbox == nullptr)
    {
        if (yesResponse == "" && noResponse == "")
        {
            const char* id = stringID.c_str();
            std::string dialogue = m_currentStringTable[id].GetString();
            m_pChatbox = ChatBox::createChatBox( npcName, dialogue);
            //delete id;
        }
        else
        {
            const char* id = stringID.c_str();
            std::string dialogue = m_currentStringTable[id].GetString();
            m_pChatbox = YesNoBox::createYesNoBox(npcName, dialogue, yesResponse, noResponse);
            //delete id;
        }
        Vec2 vCenteredBoxPos = Vec2(this->getPosition().x * -1.f, this->getPosition().y * -2.65f);
        m_pChatbox->setPosition(Vec2(vCenteredBoxPos));
        this->addChild(m_pChatbox, 5);
        m_pChatbox->advanceTextOrHide();
        m_strCurrentTalkingNPC = npcName;
        
        m_pHudLayer->setVisible(false);
    }
}