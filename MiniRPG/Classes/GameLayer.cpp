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
    
    m_pLuaEngine->executeScriptFile("lua/globalmanager.lua");
    
    m_pNPCManager = NPCManager::getInstance();
    m_pNPCManager->setGameLayer(this);
    m_pNPCManager->retain();
    
    // TODO: Save game load code.
    //m_pLuaEngine->executeString("gQuestFlagsLUT = {[\"TalkedToKingForFirstTime\"] = false,}");
    
    // TODO: This should also be loaded from the save.
    m_strCurrentMapName = kStartingRoom;
    loadMapNamed(m_strCurrentMapName);
    
    initTheHero();
    
    // Enable touches TODO: What is the non deprecated way to do this?
    setTouchEnabled(true);
    
    this->scheduleUpdate();
    
    
    return true;
}

/**
 * Loads a tilemap from the bundle path with a given name.
 *
 */
void GameLayer::loadMapNamed(std::string name)
{
    if(tileMap)
    {
        tileMap->removeAllChildrenWithCleanup(true);
        this->removeChild(tileMap, true);
        tileMap = nullptr;
    }
    
    std::string fileExtension = ".tmx";
    std::string fileNameWithExtension = "maps/" + name + fileExtension;
    printf("Loading map: %s\n",fileNameWithExtension.c_str());
    tileMap = TMXTiledMap::create(fileNameWithExtension);
    this->addChild(tileMap, -6);
    metaLayer = tileMap->getLayer("meta");
    metaLayer->setVisible(true);
    m_pNPCLayer = tileMap->getLayer("npc");
    tileWidth = tileMap->getTileSize().width;
    tileHeight = tileMap->getTileSize().height;
    mapWidth = tileMap->getMapSize().width;
    mapHeight = tileMap->getMapSize().height;
    exitGroup = tileMap->getObjectGroup("exits");
    
    m_pNPCManager->loadNPCsForTileMap(tileMap, name);
}

void GameLayer::initTheHero()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("characters/heroine.plist");
    m_pActors = SpriteBatchNode::create("characters/heroine.pvr.ccz");
    m_pActors->getTexture()->setAliasTexParameters();
    this->addChild(m_pActors, -5);
    
    m_pHero = (HeroSprite*)HeroSprite::createSprite();\
    
    auto startGroup = tileMap->getObjectGroup("start");
    ValueMap startPoint = startGroup->getObject("start");
    float startX = startPoint["x"].asFloat();
    float startY = startPoint["y"].asFloat();
    Point heroPoint = Point(startX, startY);
    m_pHero->setDesiredPosition(heroPoint);

    m_pHero->setScale(1.0f);
    //m_pHero->setAnchorPoint(Vec2(-0.5,0.5));
    m_pHero->setZOrder(-5);
    this->addChild(m_pHero, tileMap->getLayer("floor")->getZOrder());
    m_pHero->idle();
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
    if (m_pNPCLayer)
    {
        if (scanNPCLayer(tileCoord))
        {
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
    
    m_pHero->setPosition(position);
}

bool GameLayer::scanMetaLayer(Vec2 tileCoord)
{
    //printf("scanMetaLayer - Current TileCoordinates: %f, %f\n", tileCoord.x, tileCoord.y);
    
    int tileGid = metaLayer->getTileGIDAt(tileCoord);
    
    if (tileGid)
    {
        Value tileValue = tileMap->getPropertiesForGID(tileGid);
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

    if (exitGroup)
    {
        ValueVector exits = exitGroup->getObjects();
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