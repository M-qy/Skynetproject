local skynet = require "skynet"
local mysql = require "mysql"
local socket = require "skynet.socket"

Package = {}

function Package.init(cID)
	socket.write(cID, "ok")
	skynet.sleep(10)
	socket.write(cID, "ok")
	local str = socket.read(cID)
	if str == false then
		return
	end
	local name = str

	local db = mysql.connect()
	local res = db:query(string.format("select * from package where name = \'%s\'", name))
	mysql.dump(res)
	for v , n in pairs(res[1]) do
		repeat
			if v == "name" then
				break
			end
			socket.write(cID, v)
			str = socket.read(cID)
			while str ~= "ok" do
			end
			socket.write(cID, n)
			str = socket.read(cID)
			while str ~= "ok" do
			end
		until true
	end
	socket.write(cID, "over")
	db:disconnect()
end

return Package
