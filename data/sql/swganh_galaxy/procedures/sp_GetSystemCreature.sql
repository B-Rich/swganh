/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_GetSystemCreature`(IN object_id BIGINT)
BEGIN

  -- get our creature
  SELECT * FROM v_objects WHERE id = object_id;
  SELECT * FROM v_tangibles WHERE id = object_id;
  SELECT * FROM v_creatures WHERE id = object_id;
  -- Skills
  SELECT s.skill_name FROM character_skills cs 
  INNER JOIN swganh_static.skills s ON s.skill_id = cs.skill_id
  WHERE cs.character_id = object_id;
  -- Skill Mods
  SELECT sm.skillmod_name, csm.skillmod_value FROM character_skill_mods csm
  INNER JOIN swganh_static.skillmods sm ON sm.skillmod_id = csm.skillmod_id
  WHERE csm.character_id = object_id;
  
  CALL sp_GetContainedObjects(object_id);

END $$