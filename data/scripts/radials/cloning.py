import swgpy
from swgpy.object import *
from swgpy.sui import RadialMenu, RadialOptions, RadialOptionsList, RadialIdentifier
from swgpy.static import CloningData
from swgpy.utility import vector3, quat

class PyRadialMenu(RadialMenu):
		
	def handleRadial(self, owner, target, action):
		if action == RadialIdentifier.itemUse:
			sui = self.getKernel().serviceManager().suiService()	
			msgBox = sui.createMessageBox(MessageBoxType.OK_CANCEL, "@base_player:clone_confirm_title","@base_player:clone_confirm_prompt", owner)
			cloneBox = PythonCallback('radials.cloning', 'cloneBoxCallback')
			msgBox.subscribeToEventCallback(0, '', InputTrigger.OK, results, cloneBox)
			msgBox.subscribeToEventCallback(1, '', InputTrigger.CANCEL, results, cloneBox)			
			
					
def cloneBoxCallback(owner, event_id, results):
	clone_id = self.kernel.serviceManager().staticService().getCloneId(owner.container().position)
	#OK
	if event_id == 0:
		if clone_id != -1:
			owner.setIntAttribute('clone_id', clone_id)
			SystemMessage.sendSystemMessage(owner, swgpy.OutOfBand('base_player', 'clone_success'), False, False)
	else
		print('cancelled')
	#CANCEL