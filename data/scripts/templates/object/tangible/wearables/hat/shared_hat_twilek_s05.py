#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/tangible/wearables/hat/shared_hat_twilek_s05.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Tangible()		
		Template.init(kernel, params, result)
		
		return result
	
	@staticmethod
	def init(kernel, params, result):
		try:
			base.init(kernel, params, result)
		except AttributeError:
			print('base.init doesnt exist')
		result.template = "object/tangible/wearables/hat/shared_hat_twilek_s05.iff"
		result.attribute_template_id = 11
		result.stfName("wearables_name","hat_twilek_s05")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())