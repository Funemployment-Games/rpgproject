require("res/lua/globalmanager")

bunny_girl = {}

function bunny_girl:new(game)
    print("I am a bunny girl!")

    local object = {
        game = game,
        name = "BunnyGirl"
    }
    setmetatable(object, { __index = bunny_girl })

    return object
end

function bunny_girl:interact()
    talk(bunny_girl.name,"Tee-Hee, your father is so naughty!")
end

print("creating a bunny_girl")
bunny_girl = bunny_girl:new(game)
gNPCLUT["BunnyGirl"] = bunny_girl