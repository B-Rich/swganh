/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetSystemGalaxyServiceByGalaxyID` $$
CREATE PROCEDURE `sp_GetSystemGalaxyServiceByGalaxyID`(IN g_id INT)
BEGIN

  -- Return our service details
  SELECT * FROM service WHERE galaxy_id = g_id ORDER BY service.service_type;

END $$