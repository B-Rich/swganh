/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2012 The SWG:ANH Team
---------------------------------------------------------------------------------------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

CREATE PROCEDURE `sp_CharacterCreateStartingItems`(IN `inventory_id` BIGINT, IN `race_id` INT, IN `profession_id` INT, IN `gender_id` INT)
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

              SELECT sf_CreateDefaultItem(new_family_id, new_type_id, inventory_id, 99, 0, 0, 0, new_custom_name) INTO tmp_id;

              UPDATE item_attributes SET attribute_value = '1' WHERE item_id = tmp_id AND attribute_id = 11;  -- equip our clothing

            ELSE  -- other items (weapons, melon)

              SELECT sf_CreateDefaultItem(new_family_id, new_type_id, inventory_id, 99, 0, 0, 0, new_custom_name) INTO tmp_id;

            END IF;
        END IF;
    UNTIL loopEnd END REPEAT;
  CLOSE curStartingItems;

  -- Exit

END;