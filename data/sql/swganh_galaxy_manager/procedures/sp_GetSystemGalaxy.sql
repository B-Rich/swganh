/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetSystemGalaxy` $$
CREATE PROCEDURE `sp_GetSystemGalaxy`()
BEGIN

  -- grab our galaxy details
  SELECT * FROM galaxy ORDER BY galaxy_name;

END $$