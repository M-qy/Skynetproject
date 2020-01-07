local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "mysql"

Attribute = {}

function Attribute.start(cID, name, job)
	socket.write(cID, "ok")
	skynet.sleep(10)
	socket.write(cID, "ok")
	local str = socket.read(cID)
	while str ~= "ok" do
	end
	local db = mysql.connect()
	local res = db:query(string.format("select * from %s where name = \'%s\'", job, name))
	socket.write(cID, res[1]["blood"])
	str = socket.read(cID)
	while str ~= "ok" do
	end
	socket.write(cID, res[1]["attack"])
	str = socket.read(cID)
	while str ~= "ok" do
	end 
	socket.write(cID, res[1]["defense"])
	db:disconnect()
end

return Attribute
