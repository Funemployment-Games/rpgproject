require("res/lua/globalmanager")
require("res/lua/mapbase")

print("Welcome to the Throne Room!")

local throne_map = MAP.create("Throne Room")

print("1")

local i = 0
function throne_map:tick()
    if (i == 0 and gNPCIsMoving == false) then
        gNPCLUT["Wise Man"]:walkNumTilesWithDirection(2, "north")
        i = 1
    elseif (i == 1 and gDialogueIsPresent == false and gNPCIsMoving == false ) then
        gNPCLUT["Wise Man"]:talk("This is a test.\nThis is only a test.\nSoon this test will be over.")
        i = 2
    elseif (i == 2 and gDialogueIsPresent == false) then
        gNPCLUT["The King"]:talk("How horrible!\nWhat can we possibly do?\nWe need a hero!")
        i = 3
    end
end

gCurrentMap = throne_map