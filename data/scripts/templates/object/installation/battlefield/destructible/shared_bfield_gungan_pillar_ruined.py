#### NOTICE: THIS FILE IS AUTOGENERATED
#### MODIFICATIONS MAY BE LOST IF DONE IMPROPERLY
#### PLEASE SEE THE ONLINE DOCUMENTATION FOR EXAMPLES

from swgpy.object import *
from . import base

class Template(BaseTemplate):
	name = "object/installation/battlefield/destructible/shared_bfield_gungan_pillar_ruined.iff"
	is_prototype = False
	
	def create(self, kernel, params):
		result = Installation()		
		Template.init(kernel, params, result)
		
		return result
	
	@staticmethod
	def init(kernel, params, result):
		try:
			base.init(kernel, params, result)
		except AttributeError:
			print('base.init doesnt exist')
		result.template = "object/installation/battlefield/destructible/shared_bfield_gungan_pillar_ruined.iff"
		result.attribute_template_id = -1
		result.stfName("battlefield","gungan_pillar_ruined")	
		
		#### BEGIN MODIFICATIONS ####		
		####  END MODIFICATIONS  ####
		
def loadTemplates(addTemplate):
	addTemplate(Template())