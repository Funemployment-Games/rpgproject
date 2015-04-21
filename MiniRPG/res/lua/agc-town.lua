require("res/lua/mapbase")

print("Welcome to AG-Castle-Town")

local town_map = MAP.create("AGC Town")

local i = 0

function town_map:tick()

end

gCurrentMap = town_map

setStringTable("res/data/agctownstrings.json")