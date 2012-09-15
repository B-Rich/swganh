/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_CreateAccountSessionsByID`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_CreateAccountSessionByID` $$
CREATE PROCEDURE `sp_CreateAccountSessionByID`(IN n_account_id INT, IN n_session_key VARCHAR(128))
BEGIN

  -- insert new session
  INSERT INTO swganh_galaxy_manager.sessions VALUES (NULL, n_account_id, n_session_type, n_session_key, NOW());

END $$