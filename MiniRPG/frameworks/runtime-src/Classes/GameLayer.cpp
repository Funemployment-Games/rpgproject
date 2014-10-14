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
    
    m_pLuaEngine->executeScriptFile("res/lua/globalmanager.lua");
    
    m_pNPCManager = NPCManager::getInstance();
    m_pNPCManager->setGameLayer(this);
    m_pNPCManager->retain();
    
    // TODO: Save game load code.
    m_pLuaEngine->executeString("gQuestFlagsLUT = {[\"TalkedToKingForFirstTime\"] = false,}");
    
    // TODO: This should also be loaded from the save.
    m_strCurrentMapName = kStartingRoom;
    loadMapNamed(m_strCurrentMapName);
    
    initTheHeros();
    
    // Enable touches TODO: What is the non deprecated way to do this?
    setTouchEnabled(true);
    
    this->scheduleUpdate();
    
    
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
    
    std::string fileExtension = ".tmx";
    std::string fileNameWithExtension = "res/maps/" + mapName + fileExtension;
    printf("Loading map: %s\n",fileNameWithExtension.c_str());
    m_pTileMap = TMXTiledMap::create(fileNameWithExtension);
    this->addChild(m_pTileMap, -6);
    m_pMetaLayer = m_pTileMap->getLayer("meta");
    m_pMetaLayer->setVisible(false);
    tileWidth = m_pTileMap->getTileSize().width;
    tileHeight = m_pTileMap->getTileSize().height;
    mapWidth = m_pTileMap->getMapSize().width;
    mapHeight = m_pTileMap->getMapSize().height;
    m_pExitGroup = m_pTileMap->getObjectGroup("exits");
    
    m_pNPCSpawnGroup = m_pTileMap->getObjectGroup("npc");
    if (m_pNPCSpawnGroup)
    {
        initTheNPCs(mapName);
    }
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
    ValueMap startPoint = startGroup->getObject("start");
    float startX = startPoint["x"].asFloat();
    float startY = startPoint["y"].asFloat();
    m_pHero->setDesiredPosition(Vec2(startX, startY));

    m_pHero->setScale(1.0f);
    m_pHero->setAnchorPoint(Vec2(0.0,0.0));
    m_pHero->setZOrder(-5);
    this->addChild(m_pHero, m_pTileMap->getLayer("floor")->getZOrder());
    m_pHero->idle();
}

void GameLayer::initTheNPCs(std::string mapName)
{
    ValueVector npcs = m_pNPCSpawnGroup->getObjects();
    for(int i=0;i<npcs.size();++i)
    {
        ValueMap npc = npcs[i].asValueMap();
        std::string basesprite = npc["basesprite"].asString();
        std::string behaviorscript  = npc["behaviorscript"].asString();
        float x = npc["x"].asFloat();
        float y = npc["y"].asFloat();
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/characters/" + basesprite + "/" + basesprite + ".plist");
        
        NPCSprite* npcSprite = (NPCSprite*)NPCSprite::createNPC(basesprite, behaviorscript);
        npcSprite->setDesiredPosition(Vec2(x, y));
        
        npcSprite->setScale(1.0f);
        npcSprite->setAnchorPoint(Vec2(0.,0.0));
        npcSprite->setZOrder(-5);
        this->addChild(npcSprite, m_pTileMap->getLayer("floor")->getZOrder());
        npcSprite->idle();
        
        m_vCurrentNPCs.pushBack(npcSprite);
    }

    m_pNPCManager->loadNPCsForTileMap(m_pTileMap, mapName);
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
    
    for (Vector<NPCSprite*>::iterator npcIterator = m_vCurrentNPCs.begin() ; npcIterator != m_vCurrentNPCs.end(); ++npcIterator)
    {
        NPCSprite* currentNPC = (NPCSprite*)*npcIterator;
        currentNPC->setPosition(currentNPC->getDesiredPosition());
        currentNPC->update(delta);
    }
}

// Accessors
void GameLayer::setTheHudLayer(HudLayer* theHudLayer)
{
    m_pHudLayer = theHudLayer;
    
    for (int i=0; i<eContextMenuButton_Max;++i)
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
    
    Size winSize = Director::getInstance()->getWinSize();
    
    float halfWidth = winSize.width / 2;
    float halfHeight = winSize.height / 2;
    
    float mapRealW = mapWidth * tileWidth;
    float mapRealH = mapHeight * tileHeight;
    
    int maxX = MAX(position.x, halfWidth);
    int maxY = MAX(position.y, halfHeight);

    int minX = MIN(maxX, (mapRealW) - halfWidth);
    int minY = MIN(maxY, (mapRealH) - halfHeight);
    
    Vec2 actualPosition = Vec2(minX, minY);
    Vec2 centerOfView = Vec2(winSize.width/2, winSize.height/2);
    Vec2 viewPoint = centerOfView - actualPosition;
    
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
        return;
    }

    
    //Check NPCs
    /*
    if (m_pNPCLayer)
    {
        if (scanNPCLayer(tileCoord))
        {
            return;
        }
    }
     */
    
    /*
    if (m_pTreasureLayer)
    {
        if (scanTreasureLayer(tileCoord))
        {
            return;
        }
    }
     */
    
    m_pHero->setPosition(position);
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
                //printf("%s\n",collision.c_str());
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
    /*
    int tileGid = m_pNPCLayer->getTileGIDAt(tileCoord);
    if (tileGid)
    {
        Value tileValue = tileMap->getPropertiesForGID(tileGid);
        if (tileValue.getType() != Value::Type::NONE)
        {
            ValueMap properties = tileValue.asValueMap();
            if (properties.size() > 0)
            {
                if (!m_pHudLayer->getContextButtonVisibility(eContextMenuButton_Talk))
                {
                    const std::string npcName = properties.at("name").asString();
                    printf("%s\n",npcName.c_str());
                    m_pNPCManager->setClosestNPCName(npcName);
                    m_pHudLayer->setContextButtonVisibility(eContextMenuButton_Talk, true);
                }
                return true;
            }
        }
    }
    else
    {
        if (m_pHudLayer->getContextButtonVisibility(eContextMenuButton_Talk))
        {
            m_pNPCManager->setClosestNPCName(STD_STRING_EMPTY);
            m_pHudLayer->setContextButtonVisibility(eContextMenuButton_Talk, false);
        }
    }
    */
    return false;
}

bool GameLayer::scanTreasureLayer(Vec2 tileCoord)
{
    return false;
}

Vec2 GameLayer::wrapWoldMap(Vec2 tileCoord, Vec2 worldPosition)
{
    if (tileCoord.x > (MAXTILEMAPSIZE - tileWidth/4))
    {
        tileCoord.x = tileWidth/4;
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.x < tileWidth/4)
    {
        tileCoord.x = (MAXTILEMAPSIZE - tileWidth/4);
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.y > (MAXTILEMAPSIZE - tileHeight/4))
    {
        tileCoord.y = tileHeight/4;
        worldPosition = positionForTileCoord(tileCoord);
    }
    else if (tileCoord.y < tileHeight/4)
    {
        tileCoord.y = (MAXTILEMAPSIZE - tileHeight/4);
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
            float width = exit["width"].asFloat();
            float height = exit["height"].asFloat();
            
            Rect exitRect = Rect(x, y, width, height);
            
            if (exitRect.containsPoint(m_pHero->getPosition()))
            {
                m_strCurrentMapName = exit.at("destination").asString();
                loadMapNamed(m_strCurrentMapName);
                
                Vec2 posFromTileCoord = positionForTileCoord(Vec2(exit["startx"].asFloat(), exit["starty"].asFloat()));
                printf("posFromTileCoord.x %f, posFromTileCoord.y %f\n", posFromTileCoord.x, posFromTileCoord.y);
                
                m_pHero->idle();
                m_pHero->setDesiredPosition(posFromTileCoord);
                m_pHero->setPosition(posFromTileCoord);
                m_pHero->setZOrder(-5);
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
    int x = position.x / (tileWidth);
    int y = ((mapHeight * tileHeight) - position.y) / (tileHeight);
    return Vec2(x, y);
}

/**
 * Given a tile coordinate, returns the position on screen
 */
Vec2 GameLayer::positionForTileCoord(Vec2 tileCoord)
{
    int x = (tileCoord.x * tileWidth) + tileWidth;
    int y = (mapHeight * tileHeight) - (tileCoord.y * tileHeight) - tileHeight;
    
    return Vec2(x, y);
}

void GameLayer::showNPCDialogue(std::string npcName, std::string dialogue)
{
    if (!m_pChatbox)
    {
        m_pChatbox = m_pChatbox->createChatBox( npcName, dialogue);
        this->addChild(m_pChatbox, 5);
        m_pChatbox->advanceTextOrHide();
    }
}