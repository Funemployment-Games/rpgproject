require("res/lua/globalmanager")
require("res/lua/mapbase")

print("Welcome to the Throne Room!")

local throne_map = MAP.create("Throne Room")

print("4")

local i = 0

function throne_map:tick()
    if (i == 0 and gNPCLUT["Wise Man"]:getActionState() == 1) then
        gNPCLUT["Wise Man"]:setActionState(3)
        gNPCLUT["Wise Man"]:walkNumTilesWithDirection(2, 0, true)
        i = 1
    elseif (i == 1 and gDialogueIsPresent == false and gNPCLUT["Wise Man"]:getActionState() == 1 ) then
        talk(gNPCLUT["Wise Man"]:getCharacterName(), "My liege, I've had a terrible vision!\nI saw the crystal shatter.\nI fear the dark lord may have escaped.")
        i = 2
    elseif (i == 2 and gDialogueIsPresent == false) then
        talk(gNPCLUT["The King"]:getCharacterName(), "How horrible!\nWhat can we possibly do?\nMy daughter you must investigate!")
        i = 3
    end
end

gCurrentMap = throne_map