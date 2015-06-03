--Global Lua Manager
gChestLUT = {}
gQuestFlagsLUT = {["TalkedToKingForFirstTime"] = false,}
gCurrentMap = nil
gTileSize = 16
gDialogueIsPresent = false

--MB Note: these correspond to the enum in ActionSprite.h, so if you change something there
--make sure you change it here too!
gActionState = {
    ActionStateNone = 0,
    ActionStateIdle = 1,
    ActionStateManualWalk = 2,
    ActionStateAutoWalkStart = 3,
    ActionStateAutoWalking = 4,
    ActionStateAutoWalkDone = 5,
    ActionStateTalking = 6,
}

print("result is " .. 2)