Armor = {}

function Armor.find(things)
	local selection = 
	{
		["armor1"] = function()
			return 100, 20, 10
		end,
		["armor2"] = function()
			return 300, 0, 20
		end, 
	}
	local switch = selection[things]
	if switch then
		return switch()
	end
end

return Armor
