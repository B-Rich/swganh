/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetGalaxyPopulation` $$
CREATE PROCEDURE `sp_GetGalaxyPopulation`()
BEGIN

  -- grab our galaxy population via sessions table
  SELECT COUNT(*) FROM swganh_galaxy_manager.sessions WHERE galaxy_id = 1;

END $$