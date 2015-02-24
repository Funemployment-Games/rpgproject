rpgproject
==========

Progress

World Map
* Basic navigation - done
* Ability to enter locations - works
* Impassable terrain - can be defined with meta tiles
* Ocean - in progress
* River - in Progress
* Map wrap - in progress, the map wraps but the camera stops at edges so its kinda wonky.
* Encounter grids - not started
* Other features?

Interior Maps (Towns/Dungeons)
* Basic navigation - done
* Ability to exit/enter locations - mostly done
* Event triggers - not started
* Searchable tiles - not started
* Yes/No dialogues - first pass done
* Quest Flags - can be defined in json and used in lua.
* Encounter maps - not started
* Destructible/removable terrain/objects - not started
* Chests - Not started

NPCs
* Basic NPC interaction - done
* Animation - They now have support for walk/idle just like the player.
* Ability to give repeating paths - first pass is done
* Ability for designer to script npc movements during events - first pass is done 

Party
* Make it so all 4 party member sprites show and follow leader. - not started

Menus (in game)
* Inventory - not started
* Status - not started
* Equip - not started
* Magic - not started
* Shops - not started

Audio
* Not started

Input
* Basic D-Pad - Done
* Basic Context Sensitive button - Done
* Improved touch input - Done I guess
* Keyboard/controller support - keyboard works on mac and pc, will eventually need to make remappable.

Casino
* Not started

Combat
* Not started

Save system
* Some stuff has been done with the json stuff, should be easy enough to write a couple functions to handle the rest.

Menus (out of game)
* Title
* Options
* Credits
* Load/Erase save game
* Resume quick save
* Name main character

Strings
* Loaded from json
* Currently a single json file of strings per map, could fairly easily be adjusted to a single table.
* String table is loaded via lua.
* dialogueId for basic dialogue, if an NPC can ask a yes/no question add dialogueYesId and dialogueNoId. These ids must correspond to entries in the string table.

Current Tackle List
Matthew - 
Strings are now tied to npc's in the map file, use the property "dialgoueId" to set them.
Probably gonna start on chests or the shop next.
