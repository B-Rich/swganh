/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_GetAccountByUsername`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetAccountByUsername` $$
CREATE PROCEDURE `sp_GetAccountByUsername`(IN n_username VARCHAR(32))
BEGIN

  -- return the account_id
  SELECT id, username, password, salt, enabled FROM swganh_galaxy_manager.account WHERE username = n_username;

END $$