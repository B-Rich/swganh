/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_RemoveAccountSessionsByID`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_RemoveAccountSessionsByID` $$
CREATE PROCEDURE `sp_RemoveAccountSessionsByID`(IN n_account_id INT)
BEGIN

  -- remove sessions
  DELETE FROM swganh_galaxy_manager.sessions WHERE account_id = n_account_id;

END $$