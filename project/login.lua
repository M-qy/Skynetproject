local skynet = require "skynet"
local socket = require "skynet.socket"
local mysql = require "mysql"

Login = {}

local function register(account, password)
    local db = mysql.connect()

    account = tonumber(account)
    local res = db:query(string.format("insert into account (id, cID, char_num, team) values (%d, 0, 0, 0)", account))
    mysql.dump(res)
    if res["err"] ~= nil then
        db:disconnect()
        return 0
    else
        res = db:query(string.format("update account set password=\'%s\' where id=%d",
                    password, account))
        mysql.dump(res)
        db:disconnect()
        return 1
    end
end

function Login.register_init(cID)
    local account, password, ret
    socket.write(cID, "ok")
    while true do
        account = socket.read(cID)
        if account == false then
            break
        end
        socket.write(cID, "success")
        password = socket.read(cID)
        if password == false then
            break
        end
        ret = register(account, password)
        if ret == 1 then
            socket.write(cID, "success")
            break
        else
            socket.write(cID, "default")
        end
    end
end

function Login.signin(cID)
    socket.write(cID, "ok")
    local db = mysql.connect()

    local account, password
    account = socket.read(cID)  
    if account == false then
        return
    end
    socket.write(cID, "success")
    password = socket.read(cID)
    if password == false then
        return
    end
    account = tonumber(account)
    local res = db:query(string.format("select password from account where id = %d", account))
    mysql.dump(res)
    if res[1] == nil then
        socket.write(cID, "default")
        db:disconnect()
        return
    elseif res[1]["password"] == password then
        socket.write(cID, "success")
		res = db:query(string.format("update account set cID = %d where id = %d", cID, account))
		mysql.dump(res)
		local sID = tonumber(socket.read(cID))
		res = db:query(string.format("update account set sID = %d where id = %d", sID, account))
		mysql.dump(res)
        db:disconnect()
        return account
    else
        socket.write(cID, "default")
        db:disconnect()
        return
    end
end

return Login
