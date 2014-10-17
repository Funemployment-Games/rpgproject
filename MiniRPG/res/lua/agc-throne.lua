print("Welcome to the Throne Room!")

map = {}

function map:new(mapname)
    print("Initializing map")
    local object = {
        name = mapname
    }
    
    setmetatable(object, { __index = map })

    return object
end

local i = 10
function map:tick()
    if (i == 0) then
        --walkNumTilesWithDirection("BunnyGirl", 3, "south")
        i = -1
    else
        i = i - 1
    end
end

map = map:new("ThroneRoom")
gCurrentMap = map
print("13")