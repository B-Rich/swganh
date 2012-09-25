/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_CharacterCreateStartingItems` $$
CREATE PROCEDURE `sp_CharacterCreateStartingItems`(IN `inventory_id` BIGINT, IN `character_id` BIGINT, IN `race_id` INT, IN `profession_id` INT, IN `gender_id` INT, IN planet_id INT)

BEGIN

  -- Declare var(s)
  DECLARE new_family_id INT;
  DECLARE new_type_id INT;
  DECLARE new_custom_name VARCHAR(255);
  DECLARE loopEND INT DEFAULT 0;
  DECLARE tmp_id BIGINT(20);

  -- Declare our cursor (get our starting items)
  DECLARE curStartingItems CURSOR FOR SELECT family_id, type_id, customName FROM swganh_static.starting_items WHERE req_id = (SELECT id FROM swganh_static.starting_item_requirements WHERE species = race_id AND gender = gender_id AND profession= profession_id);
  DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET loopEnd = 1;

  -- create our items
	OPEN curStartingItems;
    REPEAT
      FETCH curStartingItems INTO new_family_id, new_type_id, new_custom_name;

        IF NOT loopEnd THEN
            IF new_family_id = 7 THEN  -- clothing                                           

              SELECT sf_CreateDefaultItem(new_family_id, new_type_id, character_id, planet_id, 0, 0, 0, new_custom_name) INTO tmp_id;

              UPDATE item_attributes SET attribute_value = '1' WHERE item_id = tmp_id AND attribute_id = 11;

            ELSE  -- other items (weapons, melon)

              SELECT sf_CreateDefaultItem(new_family_id, new_type_id, inventory_id, planet_id, 0, 0, 0, new_custom_name) INTO tmp_id;

            END IF;
        END IF;
    UNTIL loopEnd END REPEAT;
  CLOSE curStartingItems;

  -- Exit

END $$