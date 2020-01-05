Sword = {}

function Sword.find(things)
	local selection = 
	{
		["sword1"] = function()
			return 0, 20, 0
		end,
		["sword2"] = function()
			return 0, 10, 0
		end, 
	}
	local switch = selection[things]
	if switch then
		local res = switch()
	end
end

return Sword
