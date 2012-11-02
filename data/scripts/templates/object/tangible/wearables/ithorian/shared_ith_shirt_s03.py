#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/tangible/wearables/ithorian/shared_ith_shirt_s03.iff"
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
		result.template = "object/tangible/wearables/ithorian/shared_ith_shirt_s03.iff"
		result.attribute_template_id = 11
		result.stfName("wearables_name","ith_shirt_s03")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())