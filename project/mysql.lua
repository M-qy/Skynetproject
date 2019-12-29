local skynet = require "skynet"
local MySQL = require "skynet.db.mysql"

Mysql = {}

function Mysql.dump(res, tab)
	tab = tab or 0
	if tab == 0 then
		skynet.error("............dump...........")
	end
	if type(res) == "table" then
		skynet.error(string.rep("\t", tab).."{")
		for k, v in pairs(res) do
			if type(v) == "table" then
				Mysql.dump(v, tab + 1)
			else
				skynet.error(string.rep("\t", tab), k, "=", v, ",")
			end
		end
		skynet.error(string.rep("\t", tab).."}")
	else
		skynet.error(string.rep("\t", tab), res)
	end
end

function Mysql.connect()
    local db = MySQL.connect(
    {
        host = "127.0.0.1",
        port = 3306;
        database = "skynet",
        user = "skynet",
        password = "123456",
        max_packet_size = 1024 * 1024,
        on_connect = function()
            skynet.error("on_connect")
        end
    })
    if not db then
        skynet.error("failed to connect")
    else
        skynet.error("success to conncet to mysql")
    end
    local res = db:query("set charset utf8");
    Mysql.dump(res)
    return db
end

return Mysql