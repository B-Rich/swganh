/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2012 The SWG:ANH Team
---------------------------------------------------------------------------------------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_UpdateGalaxyName` $$
CREATE PROCEDURE `sp_UpdateGalaxyName`(IN g_name VARCHAR(128), IN g_version VARCHAR(16), IN g_status INT)
BEGIN

  -- Declare var(s)
  DECLARE cur_galaxy_name VARCHAR(128);
  DECLARE galaxy_check INT DEFAULT 0;

  -- Check if our galaxy already exists
  SELECT COUNT(*) FROM swganh_galaxy_manager.galaxy WHERE galaxy_name = g_name INTO galaxy_check;

  IF galaxy_check IS NULL OR galaxy_check < 1 THEN
    INSERT INTO swganh_galaxy_manager VALUES (1, g_name, g_version, g_status, NOW(), NOW());
  ELSE
    UPDATE swganh_galaxy_manager.galaxy SET galaxy_name = g_name, galaxy_version = g_version, galaxy_status = g_status, updated_at = NOW();
  END IF;

END $$