require("res/lua/globalmanager")

MAP = {}
MAP.__index = MAP

function MAP.create(mapname)
    print("Initializing map")
    local map = {}    
   setmetatable(map,MAP)  -- make MAP handle lookup
    map.name = mapname

    return map
end

function MAP:tick()
end