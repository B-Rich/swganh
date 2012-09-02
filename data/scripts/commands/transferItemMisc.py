import re
import swgpy
from swgpy.command import BaseSwgCommand

class TransferItem(BaseSwgCommand):
    def Run(self):
        print('transfer item misc entered')
        split = re.split('\W+', self.GetCommandString())
        container_id = split[1]
        container = self.GetKernel().service_manager().simulation_service().findObjectById(int(container_id))
        self.GetTarget().Container().Transfer(self.GetActor(), self.GetTarget(), container)