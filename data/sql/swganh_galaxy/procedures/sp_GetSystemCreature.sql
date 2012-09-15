/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_GetSystemCreature`(IN object_id BIGINT)
BEGIN
  call sp_GetSystemTangible(object_id);
  -- get our creature
  SELECT * FROM v_creatures WHERE id = object_id;

END $$