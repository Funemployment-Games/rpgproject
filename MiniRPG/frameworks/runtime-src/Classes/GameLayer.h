#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "config.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "audio/include/SimpleAudioEngine.h"
#include "SimpleDPad.h"
#include "HudLayer.h"
#include "HeroSprite.h"
#include "NPCSprite.h"
#include "NPCManager.h"
#include "LuaGlobalManager.h"
#include "lua_cocos2dx_custom.hpp"
#include "ChatBox.h"
#include "MenuYesNo.h"
#include "MenuShopIntro.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"


USING_NS_CC;

struct GameCharacter
{
    std::string characterName;
    std::string characterClass;
    unsigned char currentLevel; //1
    unsigned char Strength; //1
    unsigned char Agility; //1
    unsigned char Vitality; //1
    unsigned char Intellect; //1
    unsigned char Spirit; //1
    unsigned char AttackDamage; //1
    unsigned char HitPercent; //1
    unsigned char Defense; //1
    unsigned char EvadePercent; //1
    unsigned char MagicDef; //1
    unsigned char MagicEvaPercent; //1
    unsigned short currentHP; //2
    unsigned short maxHP; //2
    unsigned short currentMP; //2
    unsigned short maxMP; //2
    unsigned int currentXP; //4
    unsigned int neededXP; //4
};

struct PartyStruct
{
    int m_iPartyGold;
    Vec2 m_vPartyCoordinates;
    GameCharacter theCharacters[4];
};

class GameLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Layer* createLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    void update(float delta);
    
    //Touches
    //virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    //virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
    //
    void setTheHudLayer(HudLayer* theHudLayer);
    HeroSprite* getTheHero();
    LuaEngine* getLuaEngine();
    void showNPCDialogue(NPCSprite* pTheNPC);
    void showNPCDialogue(std::string npcName, std::string dialogueId, std::string dialogueYesId, std::string dialogueNoId, NPCType theType = kNPCType_Normal);
    bool loadStringTable(std::string fileName);
    
    Vec2 tileCoordForPosition(Vec2 position);
    Vec2 positionForTileCoord(Vec2 tileCoord);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
private:
    void loadMapNamed(std::string mapName);
    bool loadSavedData();
    void initTheHeros();
    void initTheNPCs(std::string mapName);
    NPCType convertStringToNPCType(std::string typeString);
    void setViewpointCenter(Vec2 position);
    void setPlayerPosition(Vec2 position);
    void heroIsDoneWalking();
    bool scanMetaLayer(Vec2 tileCoord);
    bool scanNPCLayer(Vec2 tileCoord);
    bool scanTreasureLayer(Vec2 tileCoord);
    Vec2 wrapWoldMap(Vec2 tileCoord, Vec2 worldPosition);
    
    SpriteBatchNode *m_pActors;
    HeroSprite* m_pHero;
    
    TMXTiledMap* m_pTileMap;
    TMXLayer* m_pMetaLayer;
    TMXObjectGroup* m_pNPCSpawnGroup;
    TMXObjectGroup* m_pExitGroup;
    std::string m_strCurrentMapName;
    std::string m_strCurrentTalkingNPC;
    rapidjson::Document m_currentStringTable;
    
    float m_fHalfWinHeight;
    float m_fHalfWinWidth;
    float m_fMapRealWidth;
    float m_fMapRealHeight;
    Vec2 m_vCenterOfView;
    
    LuaEngine* m_pLuaEngine;
    LuaStack* m_pLuaStack;
    lua_State* m_pLuaState;
    
    NPCManager* m_pNPCManager;
    HudLayer* m_pHudLayer;
    ChatBox* m_pChatbox;
    PartyStruct m_aParty;
};

#endif // __HELLOWORLD_SCENE_H__
