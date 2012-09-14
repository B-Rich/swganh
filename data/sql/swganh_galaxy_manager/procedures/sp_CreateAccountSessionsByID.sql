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

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_CreateAccountSessionsByID`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_CreateAccountSessionsByID` $$
CREATE PROCEDURE `sp_CreateAccountSessionsByID`(IN n_account_id INT, IN n_session_key VARCHAR(128))
BEGIN

  -- insert new session
  INSERT INTO swganh_galaxy_manager.sessions VALUES (NULL, n_account_id, NOW(), n_session_key);

END $$