require("res/lua/globalmanager")

NPC = {}
NPC.__index = NPC

function NPC.create(name, dialogue)
   local npc = {}             -- our new object
   setmetatable(npc,NPC)  -- make Account handle lookup
   npc.name = name      -- initialize our object
   npc.dialogue = dialogue
   return npc
end

function NPC:interact()
    talk(self.name, self.dialogue)
end

function NPC:setStepDelay(delayInSeconds)
    setStepDelay(self.name, delayInSeconds)
end

function NPC:setWalkBounds(startX, startY, width, height)
    setWalkBounds(self.name, cc.rect(startX, startY, width, height))
end