/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetSystemGalaxyName` $$
CREATE PROCEDURE `sp_GetSystemGalaxyName`()
BEGIN

  -- grab our galaxy name
  SELECT galaxy_name FROM swganh_galaxy_manager.galaxy WHERE id = 1;

END $$