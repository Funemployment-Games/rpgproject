require("res/lua/globalmanager")
require("res/lua/npcbase")


print("creating a bunny_girl")
local bunny_girl = NPC.create("BunnyGirl", "Would you like a puff-puff?")

gNPCLUT["BunnyGirl"] = bunny_girl

bunny_girl:setStepDelay(3.0)
--bunny_girl:setWalkBounds(15, 10, 2, 0)