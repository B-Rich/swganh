/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetSystemGalaxyServiceByID` $$
CREATE PROCEDURE `sp_GetSystemGalaxyServiceByID`(IN s_id INT)
BEGIN

  -- Return our service details by the specified ID
  SELECT * FROM service WHERE id = s_id;

END $$