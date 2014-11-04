require("res/lua/globalmanager")
require("res/lua/npcbase")


print("creating the wise_man")
local wise_man = NPC.create("Wise Man", "Seek the four treasures!\n")
gNPCLUT["Wise Man"] = wise_man
