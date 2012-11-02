#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/tangible/loot/misc/shared_loot_skull_voritor.iff"
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
		result.template = "object/tangible/loot/misc/shared_loot_skull_voritor.iff"
		result.attribute_template_id = -1
		result.stfName("item_n","voritor_skull")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())