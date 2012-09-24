/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE FUNCTION `sf_CreateDefaultItem`(`family_id` INT, `type_id` INT, `parent_id` BIGINT, `planet` INT, `in_x` FLOAT, `in_y` FLOAT, `in_z` FLOAT, `customName` VARCHAR(32)) RETURNS BIGINT(20)
BEGIN

  -- Declare our var(s)
  DECLARE item_id BIGINT(20);
  DECLARE attrib_id INT;
  DECLARE attrib_value VARCHAR(255);
  DECLARE attrib_order INT;
  DECLARE loopEnd INT DEFAULT 0;

  -- Declare our cursor (iterate through attributes)
  DECLARE cur1 CURSOR FOR
    SELECT
      swganh_static.object_default_attributes.attribute_id,
      swganh_static.object_default_attributes.attribute_value,
      swganh_static.object_default_attributes.attribute_order
    FROM
      swganh_static.object_default_attributes
    WHERE
      swganh_static.object_default_attributes.family_id = family_id AND swganh_static.object_default_attributes.item_type_id = type_id;
  DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET loopEnd = 1;

  -- get our next id for items
  SELECT MAX(swganh_galaxy.items.id) FROM swganh_galaxy.items INTO item_id;

  IF item_id IS NULL OR item_id < 281474976710655 THEN
    SET item_id = 281474976710656;
  END IF;

  SET item_id = item_id + 1;

  -- create our item
  INSERT INTO swganh_galaxy.items VALUES (item_id, parent_id, family_id, type_id, planet, in_x, in_y, in_z, 0, 0, 0, 1, 100, 0, customName, -2, 1);

  -- create our item attributes
  OPEN cur1;
    REPEAT
      FETCH cur1 INTO attrib_id, attrib_value, attrib_order;
        IF NOT loopEnd THEN
          INSERT INTO swganh_galaxy.item_attributes VALUES (NULL, item_id, attrib_id, attrib_value, attrib_order);
        END IF;
    UNTIL loopEnd END REPEAT;
  CLOSE cur1;

  -- Return our result and exit
  RETURN item_id;

END $$