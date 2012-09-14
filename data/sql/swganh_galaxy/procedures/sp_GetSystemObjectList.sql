/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetSystemObjectList` $$
CREATE PROCEDURE `swganh_galaxy`.`sp_GetSystemObjectList` ()
BEGIN
  SELECT
    objects.object_string,
    object_types.object_type
  FROM
    swganh_static.objects
  INNER JOIN swganh_static.object_types ON (swganh_static.objects.object_type = swganh_static.object_types.id);

END $$