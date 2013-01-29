from swgpy.combat import Buff
from swgpy.object import SystemMessage

class BurstRun(Buff):
	base_run_multiplier = 2.0
	
	def getName(self):
		return "temporary.burstrun"
		
	def getDuration(self):
		return 15 #seconds
	
	def applyBuff(self, creature):
		SystemMessage.sendSystemMessage(creature, 'cbt_spam', 'burstrun_start_single')
		creature.run_speed *= self.base_run_multiplier
		creature.setFlag("BurstRunning")
		creature.setFlag("BurstRunCooldown")
		
	def removeBuff(self, creature):
		SystemMessage.sendSystemMessage(creature, 'cbt_spam', 'burstrun_stop_single')
		SystemMessage.sendSystemMessage(creature, 'combat_effects', 'burst_run_tired')
		creature.run_speed /= self.base_run_multiplier
		creature.removeFlag("BurstRunning")
		creature.addBuff("BurstRunCooldown")