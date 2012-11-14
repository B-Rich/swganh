from swgpy.object import *
from swgpy.command import BaseSwgCommand
from swgpy.sui import ListBoxType, EventResultList

class ActivateClone(BaseSwgCommand):
	def run(self):
		creatureActor = self.getCreatureActor()
		if creatureActor:
			#bring up SUI window
			clone_list = EventResultList()
			clone_list.append('@base_player:revive_closest')
			
			sui = self.getKernel().serviceManager().suiService()
			#cloneSelect","Select Clone Destination","Select clone destination"
			window = sui.createListBox(ListBoxType.OK, 'cloneSelect', 'Select Clone Destination', clone_list, creatureActor)
			#Find predesignated location
			