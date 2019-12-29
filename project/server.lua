local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "skynet.db.mysql"
local login = require "login"
local character = require "character"

local function echo(cID, addr)
	socket.start(cID)

	while true do
        local str = socket.read(cID)
        local ret
		if str then
            skynet.error("recv "..addr.." "..str)

            if str == "register" then
                socket.write(cID, "ok")
                login.register_init(cID)

            elseif str == "signin" then
                socket.write(cID, "ok")
				login.signin(cID)
				
			elseif str == "character" then
				socket.write(cID, "ok")
				skynet.sleep(5)
				socket.write(cID, "success")
				character.read(cID)

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