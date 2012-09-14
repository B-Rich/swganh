/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_CreateAccount`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_CreateAccount` $$
CREATE PROCEDURE `sp_CreateAccount`(IN n_username VARCHAR(32), IN n_password VARCHAR(128), IN n_email VARCHAR(128))
accountCreate:BEGIN

  -- Declare var(s)

  DECLARE account_id BIGINT;
  DECLARE salt VARCHAR(128);
  DECLARE saltedPASS VARCHAR(128);
  DECLARE check_acc_exists INT;
  DECLARE check_length INT;
  DECLARE exit_code INT DEFAULT 1;

  -- generate our SALT
  SET salt = NOW()+n_username;

  SELECT SHA1(CONCAT(n_password, '{', salt, '}')) INTO saltedPASS;

  -- check if account username exists
  SELECT COUNT(*) FROM swganh_galaxy_manager.account WHERE username = n_username INTO check_acc_exists;

  IF check_acc_exists > 1 THEN
    SET exit_code = 0;
    SELECT exit_code;
    LEAVE accountCreate;
  END IF;
  
  -- check if username is empty
  SELECT LENGTH(n_username) INTO check_length;
  
  IF check_length IS NULL or check_length < 3 THEN
	SET exit_code = 0;
	SELECT exit_code;
	LEAVE accountCreate;
  END IF;  

  -- get our new account id
  SELECT MAX(id) FROM swganh_galaxy_manager.account INTO account_id;

  IF account_id IS NULL or account_id < 1 THEN
    SET account_id = 0;
  END IF;

  SET account_id = account_id + 1;

  -- create our new account
  INSERT INTO swganh_galaxy_manager.account VALUES (account_id, n_username, n_email, saltedPASS, salt, 1, 0, 0, 8, NOW(), NOW(), NOW());

  -- return the account_id
  SELECT account_id;

END $$