/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_RemoveAccountSessions`
--

DROP PROCEDURE IF EXISTS `swganh_galaxy_manager`.`sp_RemoveAccountSessions` $$
CREATE PROCEDURE `sp_RemoveAccountSessions`()
BEGIN

  TRUNCATE swganh_galaxy_manager.sessions;

END $$