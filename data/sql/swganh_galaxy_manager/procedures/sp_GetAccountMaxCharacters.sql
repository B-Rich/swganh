/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_GetAccountMaxCharacters` $$
CREATE PROCEDURE `swganh_galaxy_manager`.`sp_GetAccountMaxCharacters` (IN n_account_id BIGINT)
BEGIN

  -- return number of allowed characters for account
  SELECT max_characters FROM swganh_galaxy_manager.account WHERE id = n_account_id;

END $$