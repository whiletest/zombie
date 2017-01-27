function construct(this)
	local tb = {bmp = "res\\object\\WashPot.bmp"}
	return tb
end

--[[
function isOnObject(this,pt)
	return false
end

function isBulletOn(this,pt)
	return false
end
]]

function onObjectWhere(this,pt)
	if pt.x > this.xpos + this.width/3 and pt.x < this.xpos + 2*this.width/3 then
		return this.ypos + 15
	end
	return this.ypos + 10
end
