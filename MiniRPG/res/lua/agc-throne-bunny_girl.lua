require("res/lua/globalmanager")
require("res/lua/npcbase")


print("creating a bunny_girl")
local bunny_girl = NPC.create("BunnyGirl", "Would you like a puff-puff?")
gNPCLUT["BunnyGirl"] = bunny_girl