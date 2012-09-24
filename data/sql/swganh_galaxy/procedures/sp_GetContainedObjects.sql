/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$
DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetContainedObjects` $$
CREATE PROCEDURE `sp_GetContainedObjects`(IN object_id BIGINT)
BEGIN

  -- get a list of our contained objects
  SELECT id, object_type FROM v_objects WHERE parent_id = object_id;

END $$