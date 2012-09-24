/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_GetSystemPlayer`(IN `object_id` BIGINT)
BEGIN

  -- Declare var(s)
  DECLARE character_id BIGINT;

  -- get our character_id
  SELECT id FROM characters WHERE player_id = object_id INTO character_id;

  SELECT * FROM v_objects WHERE id = object_id;
  SELECT * FROM v_players WHERE id = object_id;

  -- get our status flags
  SELECT '' AS flag;

  -- get our profile flags
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

END $$