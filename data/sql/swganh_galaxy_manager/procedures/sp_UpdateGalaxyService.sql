/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy_manager;

DELIMITER $$
DROP PROCEDURE IF EXISTS `sp_UpdateGalaxyService` $$

CREATE PROCEDURE `sp_UpdateGalaxyService`(IN s_address VARCHAR(55), IN s_tcp INT, IN s_udp INT, IN s_ping INT, IN s_status INT, IN s_heartbeat DATETIME, IN s_id BIGINT)
BEGIN
<<<<<<< HEAD
    UPDATE service SET service_address = INET_ATON(s_address), tcp_port = s_tcp, udp_port = s_udp, ping_port = s_ping, last_heartbeat = s_heartbeat where id = s_id;
=======
    UPDATE service SET service_address = INET_ATON(s_address), tcp_port = s_tcp, udp_port = s_udp, ping_port = s_ping, status = s_status, last_heartbeat = s_heartbeat where id = s_id;
>>>>>>> 87494bda9c05c1c68d4710f158b6e707c975636e
END $$