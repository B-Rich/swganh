from swgpy.object import *
from swgpy.command import BaseSwgCommand, Callback

class BurstRunCommand(BaseSwgCommand):
	def setup(self, properties):
		properties.health_cost = 100
		properties.action_cost = 100
		properties.mind_cost = 100
		
	def validate(self):
		actor = self.getActor()

		if actor == None:
			return False

		if actor.hasFlag("BurstRunning"):
			SystemMessage.sendSystemMessage(actor, 'combat_effects', 'burst_run_no')
			return False

		if actor.hasFlag("BurstRunCooldown"):
			SystemMessage.sendSystemMessage(actor, 'combat_effects', 'burst_run_wait')
			return False

		# @TODO Check for mounts and whether or not in a space station/vehicle
		
		return True

	def run(self):
		actor = self.getActor()       
		# Apply The Buff
		actor.addBuff("BurstRun")
