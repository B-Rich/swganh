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

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetCharacterIdByName` $$
CREATE PROCEDURE `sp_GetCharacterIdByName`(IN n_custom_name VARCHAR(82))
BEGIN

  -- Declare var(s)
  DECLARE s_firstname VARCHAR(30);
  DECLARE s_lastname VARCHAR(50);

  -- get our first / last name
  SET s_firstname = SUBSTRING(n_custom_name, 1, INSTR(n_custom_name, ' ') - 1);
  SET s_lastname = SUBSTRING(n_custom_name, INSTR(n_custom_name, ' ') + 1);

  -- debug
  -- SELECT s_firstname, s_lastname, n_custom_name;

  -- return the ID for the character
  SELECT id FROM swganh_galaxy.characters WHERE firstname = s_firstname AND lastname = s_lastname;

END $$