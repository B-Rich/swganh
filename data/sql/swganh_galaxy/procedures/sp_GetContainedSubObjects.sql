/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetContainedSubObjects` $$
CREATE PROCEDURE `sp_GetContainedSubObjects`(IN parent BIGINT)
BEGIN
  DECLARE n BIGINT;
  DECLARE done INT DEFAULT 0;
  DECLARE cur CURSOR FOR SELECT id FROM swganh_galaxy.v_objects WHERE parent_id = parent;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

  OPEN cur;
  get_childs_fetch_loop: LOOP
    FETCH cur INTO n;

    IF done = 1 THEN
      LEAVE get_childs_fetch_loop;
    END IF;
    INSERT INTO zzChildren VALUES (n);

    CALL sp_GetSubChildren(n);

  END LOOP get_childs_fetch_loop;
  CLOSE cur;

END $$