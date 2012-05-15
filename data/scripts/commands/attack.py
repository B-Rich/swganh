from swgpy.command import BaseCombatCommand
from swgpy import ACTION

class AttackCommand(BaseCombatCommand):
    def Run(self):
        actor = self.GetActor()
        
        if not actor.has_state(ACTION.COMBAT):
            actor.toggle_state_off(ACTION.PEACE);
            actor.toggle_state_on(ACTION.COMBAT)
            actor.activate_auto_attack()
