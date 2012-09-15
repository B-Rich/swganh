/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_GetSystemTangible`(IN object_id BIGINT)
BEGIN

  -- get our tangible data for the specified object
  SELECT * FROM v_objects WHERE id = object_id;
  SELECT * FROM v_tangibles WHERE id = object_id;

END $$