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

CREATE FUNCTION `sf_SpeciesShort`(species VARCHAR(255)) RETURNS char(128) CHARSET utf8
BEGIN

  -- Declare var(s)
  DECLARE speciesShort CHAR(128);

  -- get our short species
  SET species = REPLACE(species, 'object/creature/player/shared_', 'object/creature/player/');

  SELECT SUBSTRING_INDEX(TRIM(LEADING 'object/creature/player/' FROM species), '_', 1) INTO speciesShort;

  RETURN speciesShort;

END $$