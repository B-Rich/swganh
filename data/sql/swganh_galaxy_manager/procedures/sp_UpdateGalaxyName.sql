/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_UpdateGalaxyName` $$
CREATE PROCEDURE `sp_UpdateGalaxyName`(IN g_name VARCHAR(128), IN g_version VARCHAR(16), IN g_status INT)
BEGIN

  -- Declare var(s)
  DECLARE cur_galaxy_name VARCHAR(128);
  DECLARE galaxy_check INT DEFAULT 0;

  -- Check if our galaxy already exists
  SELECT COUNT(*) FROM swganh_galaxy_manager.galaxy WHERE galaxy_name = g_name INTO galaxy_check;

  IF galaxy_check IS NULL OR galaxy_check < 1 THEN
	-- if galaxy doesn't exist create it
    INSERT INTO swganh_galaxy_manager.galaxy VALUES (1, g_name, g_version, g_status, NOW(), NOW());
    SELECT * FROM swganh_galaxy_manager.galaxy WHERE galaxy_name = g_name;
  ELSE
	-- if galaxy does exist then update it
    UPDATE swganh_galaxy_manager.galaxy SET galaxy_name = g_name, galaxy_version = g_version, galaxy_status = g_status, updated_at = NOW();
  END IF;

END $$