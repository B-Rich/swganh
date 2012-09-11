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

CREATE FUNCTION `sf_GenerateFirstName`(start_species CHAR(16), start_gender INT(11)) RETURNS char(16) CHARSET utf8
BEGIN

  -- Declare our Var(s)
  DECLARE new_firstname CHAR(16);
  DECLARE race_id INT(8);

  -- get our race_id
  SELECT id FROM swganh_static.race WHERE race.name = start_species INTO race_id;

  -- get our random first name
  SELECT firstname FROM swganh_static.namegen_firstname WHERE namegen_firstname.species = race_id AND namegen_firstname.gender = start_gender ORDER BY RAND() LIMIT 1 INTO new_firstname;

  -- return value
  RETURN new_firstname;

END;