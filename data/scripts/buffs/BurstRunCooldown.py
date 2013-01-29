from swgpy.combat import Buff
from swgpy.object import SystemMessage

class BurstRunCooldown(Buff):
	
	def getName(self):
		return "temporary.burstrun_cooldown"
		
	def getDuration(self):
		return 60 #seconds
	
	def applyBuff(self, creature):
		pass
		
	def removeBuff(self, creature):
		creature.removeFlag("BurstRunCooldown")
		SystemMessage.sendSystemMessage(creature, 'combat_effects', 'burst_run_not_tired')