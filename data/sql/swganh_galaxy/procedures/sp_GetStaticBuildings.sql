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

CREATE PROCEDURE `sp_GetStaticBuildings`(IN planet_id INT)
BEGIN

  -- Get Static Buildings

  -- output our building data
  SELECT
    buildings.id,
    0 AS parent_id,
    building_types.model,
    buildings.`x`,
    buildings.`y`,
    buildings.z,
    buildings.oX,
    buildings.oY,
    buildings.oZ,
    buildings.oW,
    0 AS complexity,
    building_types.`file`,
    building_types.name,
    0 AS volume,
    0 AS options_bitmask,
    0 AS incap_timer,
    0 AS condition_dmg,
    0 AS condition_max,
    0 AS is_static
  FROM
    swganh_static.buildings
    LEFT OUTER JOIN swganh_static.building_types ON (swganh_static.buildings.type_id = swganh_static.building_types.id)
    LEFT OUTER JOIN swganh_static.building_families ON (swganh_static.building_types.family_id = swganh_static.building_families.id)
    WHERE buildings.planet_id = planet_id;


  -- output our building cell data
  SELECT
    cells.id,
    buildings.id AS parent_id,
    building_types.model,
    buildings.`x`,
    buildings.`y`,
    buildings.z,
    buildings.oX,
    buildings.oY,
    buildings.oZ,
    buildings.oW,
    0 AS complexity,
    building_types.`file`,
    building_types.name,
    0 AS volume,
    0 AS options_bitmask,
    0 AS incap_timer,
    0 AS condition_dmg,
    0 AS condition_max,
    0 AS is_static
  FROM
    swganh_static.buildings
    LEFT OUTER JOIN swganh_static.building_types ON (swganh_static.buildings.type_id = swganh_static.building_types.id)
    LEFT OUTER JOIN swganh_static.building_families ON (swganh_static.building_types.family_id = swganh_static.building_families.id)
    INNER JOIN swganh_static.cells ON (swganh_static.buildings.id = swganh_static.cells.building_id)
    WHERE buildings.planet_id = planet_id;

END $$