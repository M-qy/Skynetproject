local skynet = require "skynet"
local mysql = require "mysql"
local socket = require "skynet.socket"
local sword = require "swords"
local armor = require "armors"

Equipment = {}

function Equipment.start(cID, name, job)
	socket.write(cID, "ok")
	skynet.sleep(10)
	socket.write(cID, "ok")
	operation = socket.read(cID)
	if operation == false then
		return
	end
	socket.write(cID, "ok")
	local db = mysql.connect()
	local things = socket.read(cID)
	if things == false then
		return
	end
	socket.write(cID, "ok")
	local things_name = socket.read(cID)
	if things_name == false then
		return
	end

	local m_blood, m_attack, m_defense
	if operation == "puton" then
		local res = db:query(string.format("update %s set %s=\'%s\' where name = \'%s\'", job, things, things_name, name))
		mysql.dump(res)
		local blood, attack, defense
		if things == "arm" then
			blood, attack, defense = sword.find(things_name)
		else
			blood, attack, defense = armor.find(things_name)
		end
		res = db:query(string.format("select * from %s where name = \'%s\'", job, name))
		mysql.dump(res)
		m_blood, m_attack, m_defense = res[1]["blood"], res[1]["attack"], res[1]["defense"]
		m_blood = m_blood + blood
		m_attack = m_attack + attack
		m_defense = m_defense + defense 
	else
		local res = db:query(string.format("update %s set %s=NULL where name = \'%s\'", job, things, name))
		mysql.dump(res)
		local blood, attack, defense
		if things == "arm" then
			blood, attack, defense = sword.find(things_name)
		else
			blood, attack, defense = armor.find(things_name)
		end
		res = db:query(string.format("select * from %s where name = \'%s\'", job, name))
		mysql.dump(res)
		m_blood, m_attack, m_defense = res[1]["blood"], res[1]["attack"], res[1]["defense"]
		m_blood = m_blood - blood
		m_attack = m_attack - attack
		m_defense = m_defense - defense
	end
	res = db:query(string.format("update %s set blood = %d, attack = %d, defense = %d where name = \'%s\'", job, m_blood, m_attack, m_defense, name))
	mysql.dump(res)
	socket.write(cID, "ok")
	db:disconnect()
end

return Equipment
