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

CREATE PROCEDURE `sp_GetStaticTerminals`(IN planet_id INT)
BEGIN

  -- Get Static Buildings
  DECLARE start_id BIGINT;

  -- start id to return data from
  SET start_id = 4294967296;

  -- output our terminals data
  SELECT
    terminals.id,
    terminals.parent_id,
    terminal_types.object_string,
    terminals.`x`,
    terminals.`y`,
    terminals.z,
    terminals.oX,
    terminals.oY,
    terminals.oZ,
    terminals.oW,
    0 AS complexity,
    terminal_types.name,
    terminal_types.`file`,
    terminals.planet_id,
    0 AS volume,
    0 AS options_bitmask,
    0 AS incap_timer,
    0 AS condition_dmg,
    0 AS condition_max,
    0 AS is_static
FROM
  swganh_static.terminals
  INNER JOIN swganh_static.terminal_types ON (swganh_static.terminals.terminal_type = swganh_static.terminal_types.id)
  WHERE terminals.id > start_id AND terminals.planet_id = planet_id;

  -- exit
END;