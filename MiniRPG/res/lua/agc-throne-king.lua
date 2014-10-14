require("res/lua/globalmanager")

king = {}

function king:new(game)
    print("initializing the king")
    local object = { 
        game = game,
        name = "TheKing"
    }
    setmetatable(object, { __index = king })

    return object
end 

function king:interact()
    print("Hello World!")
    if (gQuestFlagsLUT["TalkedToKingForFirstTime"] == false) then
        talk(king.name, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas ut eleifend enim. Vestibulum ante ipsum\n primis in faucibus orci luctus et ultrices posuere cubilia Curae; Donec vestibulum dui sed augue vehicula\n tristique. Suspendisse potenti. Curabitur sed varius mauris. In eget pretium odio. Praesent vitae dolor sed\n velit tempus molestie. Fusce vehicula tempus laoreet.")
        gQuestFlagsLUT["TalkedToKingForFirstTime"] = true
    else
        talk(king.name, "Go forth and be excellent.")
    end
end

print("creating the king")
king = king:new(game)
gNPCLUT["TheKing"] = king
