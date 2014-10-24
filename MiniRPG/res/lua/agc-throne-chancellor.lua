require("res/lua/globalmanager")
require("res/lua/npcbase")


print("creating a chancellor")
local chancellor = NPC.create("Chancellor", "Are you ready for your quest?")

function chancellor:interact()
    talkYesNo(self.name, self.dialogue, "Then follow me.", "Let me know when.")
end

gNPCLUT["Chancellor"] = chancellor