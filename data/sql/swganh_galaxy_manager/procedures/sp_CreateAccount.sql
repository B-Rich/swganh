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
-- Definition for stored procedure `sp_CreateAccount`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_CreateAccount` $$
CREATE PROCEDURE `sp_CreateAccount`(IN n_username VARCHAR(32), IN n_password VARCHAR(128), IN n_email VARCHAR(128))
BEGIN

  -- Declare var(s)

  DECLARE check_acc INT;
  DECLARE account_id BIGINT;
  DECLARE salt VARCHAR(128);
  DECLARE saltedPASS VARCHAR(128);

  -- generate our SALT
  SET salt = NOW()+n_username;

  SELECT SHA1(CONCAT(n_password, '{', salt, '}')) INTO saltedPASS;


  -- get our new account id

  SELECT MAX(id) FROM swganh_galaxy_manager.accounts INTO check_acc;

  IF check_acc IS NULL or check_acc < 1 THEN
    SET account_id = 0;
  END IF;

  SET account_id = account_id + 1;

  -- create our new account
  INSERT INTO swganh_galaxy_manager.account VALUES (account_id, n_username, n_email, saltedPASS, salt, 1, 0, 0, 8, NOW(), NOW(), NOW());

  -- return the account_id
  SELECT account_id;

END $$