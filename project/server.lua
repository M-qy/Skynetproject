local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "skynet.db.mysql"
local login = require "login"
local character = require "character"
local player_init = require "player_init"
local package = require "package_init"
local equipment = require "equipments"
local attribute = require "attribute_init"
local fight = require "fight"

local function echo(cID, addr)
	socket.start(cID)
	
	local account, name, job

	while true do
        local str = socket.read(cID)
        local ret
		if str then
            skynet.error("recv "..addr.." "..str)

			local selection = 
			{
				["register"] = function()
					login.register_init(cID)
				end,
				["signin"] = function()
					account = login.signin(cID)
				end,
				["character"] = function()
					character.read(cID)
				end,
				["player_init"] = function()
					name, job = player_init.init(cID)
				end,
				["package"] = function()
					package.init(cID)
				end,
				["equipment"] = function()
					equipment.start(cID, name, job)
				end,
				["attribute"] = function()
					attribute.start(cID, name, job)
				end,
				["fight"] = function()
					fight.start(cID, account, name, job)
				end,
			}
			local switch = selection[str]
			if switch then
				local res = switch()
			end

		else
			socket.close(cID)
			skynet.error(addr.." disconnect")
			return
        end
		str = ""
	end
end

local function accept(cID, addr)
	skynet.error(addr.." accepted")
	skynet.fork(echo, cID, addr)
end

skynet.start(function()
		local addr = "0.0.0.0:8001"
		skynet.error("listen "..addr)
		local lID = socket.listen(addr)
		assert(lID)
		socket.start(lID, accept)
end)
