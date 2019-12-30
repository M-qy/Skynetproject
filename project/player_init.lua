local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "mysql"

Player_init = {}

function Player_init.init(cID)
    local db = mysql.connect()
    local name = socket.read(cID)
    socket.write(cID, "ok")
    local job = socket.read(cID)
    socket.write(cID, "ok")
    local res = db:query(string.format("select * from %s where name = \'%s\'", job, name))
    
    if res[1]["arm"] == nil then
        socket.write(cID, "NULL")
    else
        socket.write(cID, res[1]["arm"])
    end
    local str = socket.read(cID)
    while str ~= "ok" do
    end

    if res[1]["armor"] == nil then
        socket.write(cID, "NULL")
    else
        socket.write(cID, res[1]["armor"])
    end
end

return Player_init