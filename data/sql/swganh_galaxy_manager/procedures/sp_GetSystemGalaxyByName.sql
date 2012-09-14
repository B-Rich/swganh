/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$
CREATE PROCEDURE `sp_GetSystemGalaxyByName`(IN g_name VARCHAR(128))
BEGIN
	select * from galaxy where galaxy_name = g_name;
END $$
