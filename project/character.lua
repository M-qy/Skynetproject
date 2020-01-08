local skynet = require "skynet"
local mysql = require "mysql"
local socket = require "skynet.socket"

Character = {}

local function check(account)
    local db = mysql.connect()

    local res = db:query(string.format("select char_num from account where id = %s", account))
    mysql.dump(res)
    db:disconnect()
    return res[1]["char_num"]
end

local function make(cID, account, num)
    local job, name
    job = socket.read(cID)
    if job == false then
        return
    end
    socket.write(cID, "success")
    while true do
        name = socket.read(cID)
        if name == false then
            return
        end
        local db = mysql.connect()
        local res = db:query(string.format("select * from %s where name = \'%s\'", job, name))
        mysql.dump(res)
        if res[1] == nil then
            account = tonumber(account)
            res = db:query(string.format("insert into %s (name, id, cID) values (\'%s\', %d, 0)",
                        job, name, account))
            mysql.dump(res)
            num = tonumber(num)
            res = db:query(string.format("update account set char_num = %d, character%d = \'%s\', job%d = \'%s\' where id = %d",
                    num+1, num+1, name, num+1, job, account))
            mysql.dump(res)
            if job == "saber" then
                res = db:query(string.format("update saber  set blood = 1000, attack = 10, defense = 10 where name = \'%s\'", name))
				mysql.dump(res)
				res = db:query(string.format("insert into package (name, armor1, armor2, sword1, sword2) values(\'%s\', 1, 1, 1, 1)", name)) 
				mysql.dump(res)
            end
            socket.write(cID, "success")
            db:disconnect()
            break
        else
            socket.write(cID, "default")
        end
    end
end

local function signin(cID, account, num)
	local name, job
    account = tonumber(account)
    local db = mysql.connect()
    local res = db:query(string.format("select * from account where id = %d", account))
    mysql.dump(res)
    for var = 1, num do
        name = res[1][string.format("character%d", var)]
        socket.write(cID, name)
        local str = socket.read(cID)
        if str == false then
            return
        end
        while str ~= "ok" do
        end
        job = res[1][string.format("job%d", var)]
        socket.write(cID, job)
        str = socket.read(cID)
        if str == false then
            return
        end
        while str ~= "ok" do
        end
    end
end

function Character.read(cID)
    local str, num, account, name, job
	socket.write(cID, "ok")
	skynet.sleep(5)
	socket.write(cID, "success") 
    account = socket.read(cID)
    if account == false then
        return
    end
    socket.write(cID, "success")
    while true do
        str = socket.read(cID)
        if str == false then
            return
        end
        if str == "check_character" then
            num = check(account)
            socket.write(cID, num)

        elseif str == "make" then
            socket.write(cID, "success")
            make(cID,account, num)

        elseif str == "character_signin" then
            signin(cID, account, num)
        elseif str == "over" then
            break
        end
    end
end

return Character
