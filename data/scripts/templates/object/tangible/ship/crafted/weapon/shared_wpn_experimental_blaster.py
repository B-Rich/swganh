#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/tangible/ship/crafted/weapon/shared_wpn_experimental_blaster.iff"
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
		result.template = "object/tangible/ship/crafted/weapon/shared_wpn_experimental_blaster.iff"
		result.attribute_template_id = 8
		result.stfName("space_crafting_n","wpn_experimental_blaster")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())