local skynet = require "skynet"
local mysql = require "mysql"
local socket = require "skynet.socket"

Fight = {}

function Fight.start(cID, account, name, job)
	socket.write(cID, "ok")
	math.randomseed(os.time())
	local o_cID, o_name, o_job
	local str
	local db = mysql.connect()
	local res = db:query("select cID from account where team = 1 and teamer is NULL")
	if res[1] == nil then
		res = db:query(string.format("update account set team = 1 where id = %d", account))
		mysql.dump(res)
		local simble = 0
		while true do
			res = db:query(string.format("select teamer from account where id = %d", account))
			mysql.dump(res)
			if res[1]["teamer"] == nil then
				simble = simble + 1
				skynet.sleep(100);
			else
				local temp = math.random(1, 2)
				_, _, o_name, o_job = string.find(res[1]["teamer"], "(%a+)%((%a+)%)")
				
				socket.write(cID, o_name)
				str = socket.read(cID)
				while str ~= "ok" do
				end
				socket.write(cID, o_job)
				str = socket.read(cID)
				while str ~= "ok" do
				end
				res = db:query(string.format("select * from %s where name = \'%s\'", o_job, o_name))
				mysql.dump(res)
				if res[1]["arm"] == nil then
					socket.write(cID, "NULL")
				else
					socket.write(cID, res[1]["arm"])
				end
				str = socket.read(cID)
				while str ~= "ok" do
				end
				if res[1]["armor"] == nil then
					socket.write(cID, "NULL")
				else
					socket.write(cID, res[1]["armor"])
				end
				o_cID = res[1]["cID"]
				str = socket.read(cID)
				while str ~= "start" do
				end
				if temp == 1 then
					res = db:query(string.format("update account set offensive = \'first\' where id = %d", account))
					mysql.dump(res)
					res = db:query(string.format("update account set offensive = \'second\' where cID = %d", o_cID))
					mysql.dump(res) 
				else
					res = db:query(string.format("update account set offensive = \'second\' where id = %d", account))
					mysql.dump(res)
					res = db:query(string.format("update account set offensive = \'first\' where cID = %d", o_cID))
					mysql.dump(res)
				end
				if temp == 1 then
					socket.write(cID, "first")
				else
					socket.write(cID, "second")
				end
				break
			end
			if simble == 10 then
				socket.write(cID, "default")
				res = db:query(string.format("update account set team = 0 where id = %d", tonumber(account)))
				mysql.dump(res)
				db:disconnect()
				return
			end
		end
	else
		o_cID = res[1]["cID"]
		res = db:query(string.format("update account set teamer = \'%s(%s)\' where cID = %d", name, job, o_cID))
		mysql.dump(res)
		res = db:query(string.format("select login_cha from account where cID = %d", o_cID))
		mysql.dump(res)
		_, _, o_name, o_job = string.find(res[1]["login_cha"], "(%a+)%((%a+)%)")
		socket.write(cID, o_name)
		str = socket.read(cID)
		while str ~= "ok" do
		end
		socket.write(cID, o_job)
		str = socket.read(cID)
		while str ~= "ok" do
		end
		res = db:query(string.format("select * from %s where name = \'%s\'", o_job, o_name))
		mysql.dump(res)
		if res[1]["arm"] == nil then
			socket.write(cID, "NULL")
		else
			socket.write(cID, res[1]["arm"])
		end
		str = socket.read(cID)
		while str ~= "ok" do
		end
		if res[1]["armor"] == nil then
			socket.write(cID, "NULL")
		else
			socket.write(cID, res[1]["armor"])
		end 
		str = socket.read(cID)
		while str ~= "start" do
		end
		while res[1]["offensive"] == nil do
			res = db:query(string.format("select offensive from account where cID = %d", cID))
			mysql.dump(res)
			skynet.sleep(10)
		end
		socket.write(cID, res[1]["offensive"])
	end

	while true do
		skynet.error("reading...")
		str = socket.read(cID)
		if str == false then
			res = db:query(string.format("update account set team = 0, teamer = NULL, offensive = NULL where id = %d", account))
			mysql.dump(res)
			db:disconnect()
			return
		end
		skynet.error(str)
		if str == "surrender" then
			socket.write(o_cID, "surrender")
			res = db:query(string.format("update account set team = 0, teamer = NULL, offensive = NULL where id = %d", account))
			mysql.dump(res)
			db:disconnect()
			return
		elseif str == "o_surrender" then
			res = db:query(string.format("update account set team = 0, teamer = NULL, offensive = NULL where id = %d", account))
			mysql.dump(res)
			db:disconnect()
			return
		elseif str == "over" then
			socket.write(o_cID, "over")
			res = db:query(string.format("update account set team = 0, teamer = NULL, offensive = NULL where id = %d", account))
			mysql.dump(res)
			db:disconnect()
			return
		elseif str == "ace" then
			socket.write(o_cID, "ace")
			socket.write(cID, "ok")
			str = socket.read(cID)
			if str == "bleed" then
				socket.write(o_cID, "bleed")
			else
				socket.write(o_cID, "unbleed")
			end
		end
	end
end

return Fight
