/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_UpdateGalaxyStatus` $$
CREATE PROCEDURE `sp_UpdateGalaxyStatus`(IN g_id INT, IN g_status INT)
BEGIN

	-- update our galaxy status
    UPDATE swganh_galaxy_manager.galaxy SET galaxy_status = g_status, updated_at = NOW() WHERE galaxy_id = g_id;

END $$