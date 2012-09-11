﻿/*
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

CREATE PROCEDURE `sp_CharacterCreateXP`(IN character_id BIGINT, IN profession_id INT)
BEGIN

  -- Declare our Var(s)
  DECLARE loopEnd INT DEFAULT 0;
  DECLARE xp_type_id INT;
  DECLARE cur_1 CURSOR FOR SELECT skills_base_xp_groups.xp_type_id FROM swganh_static.skills_base_xp_groups WHERE skills_base_xp_groups.skill_id = profession_id;
  DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET loopEnd = 1;

  OPEN cur_1;
    REPEAT
      FETCH cur_1 INTO xp_type_id;

      IF NOT loopEnd THEN
        IF(xp_type_id IS NOT NULL) THEN
          INSERT INTO character_xp VALUES (character_id, xp_type_id, 0);
        END IF;
      END IF;
    UNTIL loopEnd END REPEAT;
  CLOSE cur_1;

END;