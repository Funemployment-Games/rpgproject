#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "config.h"
#include "CCLuaEngine.h"
#include "SimpleDPad.h"
#include "HudLayer.h"
#include "HeroSprite.h"
#include "NPCSprite.h"
#include "NPCManager.h"
#include "LuaGlobalManager.h"
#include "ChatBox.h"

USING_NS_CC;

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
    void showNPCDialogue(std::string npcName, std::string dialogue);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
private:
    void loadMapNamed(std::string mapName);
    void initTheHeros();
    void initTheNPCs(std::string mapName);
    void setViewpointCenter(Vec2 position);
    void setPlayerPosition(Vec2 position);
    void heroIsDoneWalking();
    bool scanMetaLayer(Vec2 tileCoord);
    bool scanNPCLayer(Vec2 tileCoord);
    bool scanTreasureLayer(Vec2 tileCoord);
    Vec2 tileCoordForPosition(Vec2 position);
    Vec2 positionForTileCoord(Vec2 tileCoord);
    Vec2 wrapWoldMap(Vec2 tileCoord, Vec2 worldPosition);
    
    SpriteBatchNode *m_pActors;
    HeroSprite* m_pHero;
    
    TMXTiledMap* m_pTileMap;
    TMXLayer* m_pMetaLayer;
    TMXObjectGroup* m_pNPCSpawnGroup;
    TMXObjectGroup* m_pExitGroup;
    std::string m_strCurrentMapName;
    
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
};

#endif // __HELLOWORLD_SCENE_H__
