/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_RemoveSystemGalaxyServiceByID` $$
CREATE PROCEDURE `sp_RemoveSystemGalaxyServiceByID`(IN s_id INT)
BEGIN

  -- Delete our service
  DELETE FROM swganh_galaxy_manager.service WHERE id = s_id;

END $$