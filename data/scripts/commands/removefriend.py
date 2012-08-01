import re
import swgpy
from swgpy.command import BaseSwgCommand

class RemoveFriendCommand(BaseSwgCommand):
    def Run(self):
        split = re.split('\W+', self.GetCommandString())
        friend_name = split[0]

        player = self.GetActor().get_player()
        if player:
            # Check if the name is already our friend
            if player.is_friend(friend_name):
                player.remove_friend(friend_name)
                self.GetController().SendSystemMessage(swgpy.OutOfBand('cmnty', 'friend_removed', swgpy.ProseType.TT, friend_name), False, False)
            else:
                self.GetController().SendSystemMessage(swgpy.OutOfBand('cmnty', 'friend_not_found', swgpy.ProseType.TT, friend_name), False, False)
