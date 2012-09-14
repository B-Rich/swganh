﻿/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_UpdateGalaxyStatus` $$
CREATE PROCEDURE `sp_UpdateGalaxyStatus`(IN g_id INT, IN g_status INT)
BEGIN

	-- update our galaxy status
<<<<<<< HEAD
    UPDATE swganh_galaxy_manager.galaxy SET galaxy_status = g_status, updated_at = NOW() WHERE galaxy_id = g_id;
=======
    UPDATE swganh_galaxy_manager.galaxy SET galaxy_status = g_status, updated_at = NOW() where galaxy.id = g_id;
>>>>>>> 87494bda9c05c1c68d4710f158b6e707c975636e

END $$