from swgpy.command import BaseSwgCommand
from swgpy import POSTURE
from swgpy import combat

class DeathBlowCommand(BaseSwgCommand):
    def run(self):
        target = self.getTarget()
        if target:
            if target.isIncap():
				combat_svc = self.getKernel().serviceManager().combat()
				if combat_svc not None:
					combat_svc.setDead(self.getCreatureActor(), self.getCreatureTarget())
