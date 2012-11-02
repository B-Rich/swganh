#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s5_gen2.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Weapon()		
		Template.init(kernel, params, result)
		
		return result
	
	@staticmethod
	def init(kernel, params, result):
		try:
			base.init(kernel, params, result)
		except AttributeError:
			print('base.init doesnt exist')
		result.template = "object/weapon/melee/sword/crafted_saber/shared_sword_lightsaber_one_handed_s5_gen2.iff"
		result.attribute_template_id = 10
		result.stfName("weapon_name","sword_lightsaber_type5")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())