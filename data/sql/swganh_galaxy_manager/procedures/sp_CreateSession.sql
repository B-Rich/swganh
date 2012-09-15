/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_CreateSession`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_CreateSession` $$
CREATE PROCEDURE `sp_CreateSession`(IN n_account_id INT, IN n_session_key VARCHAR(128), IN n_session_type INT)
BEGIN

  -- insert new session
  INSERT INTO swganh_galaxy_manager.sessions VALUES (NULL, n_account_id, n_session_type, n_session_key, NOW());

END $$