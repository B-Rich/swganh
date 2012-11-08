import swgpy
import swgpy.static
from swgpy.object import *
from swgpy.sui import *
from swgpy.utility import vector3

class PyRadialMenu(RadialMenu):
	def buildRadial(self, owner, target, radials):
		radial_list = RadialOptionsList()
		radial_list.append(RadialOptions(0, RadialIdentifier.itemUse, 3, ''))
		radial_list.append(RadialOptions(0, RadialIdentifier.examine, 1, ''))
		return radial_list		
	def handleRadial(self, owner, target, action):
		print('handle radial hit')
		if action == RadialIdentifier.itemUse:
			sui = self.getKernel().serviceManager().suiService()	
			msgBox = sui.createMessageBox(MessageBoxType.OK_CANCEL, "@base_player:clone_confirm_title","@base_player:clone_confirm_prompt", owner)
			cloneBox = PythonCallback('radials.cloning', 'cloneBoxCallback')
			results = ResultList()
						
			msgBox.subscribeToEventCallback(0, '', InputTrigger.OK, results, cloneBox)
			msgBox.subscribeToEventCallback(1, '', InputTrigger.CANCEL, results, cloneBox)			
			sui.openSUIWindow(msgBox)
			
					
def cloneBoxCallback(kernel, owner, event_id, results):
	print('callback triggered')
	clone_id = -1
	if owner.container():
		static = kernel.serviceManager().staticService()
		clone_id = static.getCloneId(owner)
		print(clone_id)
	#OK
	if event_id == 0:
		if owner.bank_credits >= 1000:
			owner.bank_credits = owner.bank_credits - 1000
			owner.setIntAttribute('clone_id', clone_id)
			SystemMessage.sendSystemMessage(owner, swgpy.OutOfBand('base_player', 'clone_success'), False, False)
		else:
			needed_credits = 1000 - owner.bank_credits
			if needed_credits > 1:
				SystemMessage.sendSystemMessage(owner, swgpy.OutOfBand('error_message', 'nsf_clone', swgpy.ProseType.DI, needed_credits), False, False)
			else:
				SystemMessage.sendSystemMessage(owner, swgpy.OutOfBand('error_message', 'nsf_clone1'), False, False)
	#CANCEL
	else:
		print('cancelled')