local login = require "snax.loginserver"
local crypt = require "skynet.crypt"
local skynet = require "skynet"

local server_list = {}
local login_users = {}

local server = 
{
	host = "127.0.0.1",
	port = 8001,
	multilogin = false,--disallow multilogin
	name = "login_master",
}

function server.auth_handler(token)
	local user, server, password = token:match("([^@]+)@([^:]+):(.+)")
	user = crypt.base64decode(user)
	server = crypt.base64decode(server)
	password = crypt.base64decode(password)
	skynet.error(string.format("%s@%s:%s", user, server, password))
	assert(password == "password", "Inwalid password")
	return server, user
end

function server.login_handler(server, uid, secret)
	local msgserver = assert(server_list[server], "unknow server")
    skynet.error(string.format("%s@%s is login, secret is %s",
                uid, server, crypt.hexencode(secret)))
	local last = login_users[uid]
	if last then
		skynet.call(last.address, "lua", "kick", uid, last.subid)
	end

	local id = skynet.call(msgserver, "lua", "login", uid, secret)
	login_users[uid] = {address = msgserver, subid = id}
	return id
end

local CMD = {}

function CMD.register_gate(server, address)
	skynet.error("cmd register_gate")
	server_list[server] = address
end

function CMD.logout(uid, subid)
	local u = login_users[uid]
	if u then
		print(string.format("%s@%s is logout", uid, u.server))
		login_users[uid] = nil
	end
end

function server.command_handler(command, ...)
	local f = assert(CMD[command])
	return f(...)
end

login(server)