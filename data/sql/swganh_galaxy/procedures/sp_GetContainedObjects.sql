/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetContainedObjects` $$
CREATE PROCEDURE `sp_GetContainedObjects`(IN parent BIGINT)
BEGIN

  DECLARE n INT;

  DROP TABLE IF EXISTS `zzChildren`;
  CREATE TABLE `zzChildren` (
    id BIGINT NOT NULL
  ) ENGINE = MEMORY;

  -- check if object is a container
  SELECT COUNT(*) FROM swganh_galaxy.v_objects WHERE parent_id = parent INTO n;

  IF n <> 0 THEN CALL sp_GetContainedSubObjects(parent);
  END IF;

  SELECT t1.parent_id, t1.id, t1.object_type FROM v_objects AS t1 JOIN zzchildren USING(id);

END $$