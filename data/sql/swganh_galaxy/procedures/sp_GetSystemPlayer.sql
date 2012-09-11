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

CREATE PROCEDURE `sp_GetSystemPlayer`(IN `object_id` BIGINT)
BEGIN

  -- Declare var(s)
  DECLARE character_id BIGINT;

  -- get our character_id
  SELECT id FROM characters WHERE player_id = object_id INTO character_id;

  SELECT * FROM v_objects WHERE id = object_id;
  SELECT * FROM v_players WHERE id = object_id;

  -- get our status flags (??)
  SELECT '' AS flag;

  -- ger out profile flags (??)
  SELECT '' AS flag;

  -- get draft schematics
  SELECT '' AS id, '' AS schematic_id;

  -- get friend list friends
  SELECT '' AS custom_name, '' as id;

  -- get FS Quests
  SELECT '' AS quest_mask, '' AS completed;

  -- get friend list ignores
  SELECT '' AS custom_name, '' as id;

  -- get Quest Journal entries
  SELECT '' AS quest_owner_id, '' AS quest_crc, '' AS active_step_bitmask, '' AS completed_step_bitmask, '' AS completed;

  -- get Waypoints
  SELECT '' AS id, '' AS x, '' AS y, '' AS z, '' AS oX, '' AS oY, '' AS oZ, '' AS oW, '' AS complexity, '' AS stf_file_name, '' AS stf_name_string, '' AS custom_name, '' AS volume, '' AS type_id, '' AS active, '' AS name, '' AS color;

  -- get XP

  SELECT swganh_static.xp_types.xp_type, character_xp.value FROM character_xp INNER JOIN swganh_static.xp_types ON (character_xp.xp_type_id = swganh_static.xp_types.id) WHERE character_id = character_id;

END;