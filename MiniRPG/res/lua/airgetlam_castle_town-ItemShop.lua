require("lua/globalmanager")

merchant = {}

function merchant:new(game)
    print("initializing the merchant")
    local object = { 
        game = game,
        name = "Merchant"
    }
    setmetatable(object, { __index = merchant })

    return object
end 

function merchant:interact()
    talk(merchant.name, "This is an item shop.")
end

print("creating the item merchant")
merchant = merchant:new(game)
gNPCLUT["ItemShop"] = merchant
