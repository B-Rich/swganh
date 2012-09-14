/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_ReturnAccountCharacters` $$
CREATE PROCEDURE `swganh_galaxy_manager`.`sp_ReturnAccountCharacters` (IN n_account_id BIGINT)
BEGIN

  -- return our characters for the requested account
  SELECT
    characters.id,
    CONCAT(firstname, ' ', characters.lastname),
    character_attributes.object_template_id,
    swganh_static.objects.object_string
  FROM
    swganh_galaxy.characters
  INNER JOIN swganh_galaxy.character_attributes ON (swganh_galaxy.characters.id = swganh_galaxy.character_attributes.character_id)
  INNER JOIN swganh_static.objects ON (swganh_galaxy.character_attributes.object_template_id = swganh_static.objects.id)
  WHERE
    swganh_galaxy.characters.account_id = n_account_id;

END $$