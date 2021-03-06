require("res/lua/mapbase")

print("Welcome to the Throne Room!")

local throne_map = MAP.create("Throne Room")

print("8")

local i = 0

function throne_map:tick()
    if (i == 0 and gNPCLUT["Wise Man"]:getActionState() == gActionState["ActionStateIdle"]) then
        gNPCLUT["Wise Man"]:setActionState(3)
        gNPCLUT["Wise Man"]:walkNumTilesWithDirection(2, 0, true)
        i = 1
    elseif (i == 1 and gDialogueIsPresent == false and gNPCLUT["Wise Man"]:getActionState() == gActionState["ActionStateIdle"] ) then
        talk(gNPCLUT["Wise Man"]:getCharacterName(), "WiseMan1")
        i = 2
    elseif (i == 2 and gDialogueIsPresent == false) then
        talk(gNPCLUT["The King"]:getCharacterName(), "King1")
        i = 3
    end
end

gCurrentMap = throne_map

setStringTable("res/data/agcthronestrings.json")