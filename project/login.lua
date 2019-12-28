local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "skynet.db.mysql"

login = {}

local function dump(res, tab)
	tab = tab or 0
	if tab == 0 then
		skynet.error("............dump...........")
	end
	if type(res) == "table" then
		skynet.error(string.rep("\t", tab).."{")
		for k, v in pairs(res) do
			if type(v) == "table" then
				dump(v, tab + 1)
			else
				skynet.error(string.rep("\t", tab), k, "=", v, ",")
			end
		end
		skynet.error(string.rep("\t", tab).."}")
	else
		skynet.error(string.rep("\t", tab), res)
	end
end

local function register(account, password)
    local db = mysql.connect(
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
    dump(res)

    account = tonumber(account)
    res = db:query(string.format("insert into account (id) values (%d)", account))
    dump(res)
    if res["err"] ~= nil then
        db:disconnect()
        return 0
    else
        res = db:query(string.format("update account set password=\'%s\' where id=%d",
                    password, account))
        dump(res)
        db:disconnect()
        return 1
    end
end

function login.register_init(cID)
    local account, password, ret
    while true do
        account = socket.read(cID)
        if account == false then
            break
        end
        socket.write(cID, "ok")
        password = socket.read(cID)
        if password == false then
            break
        end
        ret = register(account, password)
        if ret == 1 then
            socket.write(cID, "ok")
            break
        else
            socket.write(cID, "default")
        end
    end
end

function login.signin(cID)
    local db = mysql.connect(
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
    dump(res)

    local account, password, str
    account = socket.read(cID)  
    if account == false then
        return
    end
    str = "ok"
    socket.write(cID, str)
    password = socket.read(cID)
    if password == false then
        return
    end
    account = tonumber(account)
    res = db:query(string.format("select password from account where id = %d", account))
    dump(res)
    if res[1]["password"] == password then
        socket.write(cID, "ok")
        return
    else
        socket.write(cID, "default")
        return
    end
    db:disconnect()
end

return login