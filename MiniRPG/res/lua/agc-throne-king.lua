require("res/lua/globalmanager")
require("res/lua/npcbase")


print("creating the king")
local king = NPC.create("TheKing", "Go Forth and be excellent!\n")
gNPCLUT["TheKing"] = king
