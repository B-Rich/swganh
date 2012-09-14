/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetAccountBySessionID` $$
CREATE PROCEDURE `sp_GetAccountBySessionID`(IN s_key VARCHAR(255))
BEGIN

  -- grab our galaxy population via sessions table
  SELECT account_id FROM swganh_galaxy_manager.sessions WHERE session = s_key;

END $$