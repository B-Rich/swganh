/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_GetContainedObjects`(IN object_id BIGINT)
BEGIN

  -- get a list of our contained objects
  SELECT id, type_id FROM v_objects WHERE parent_id = object_id;

END $$