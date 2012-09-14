/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

CREATE PROCEDURE `sp_CreateGalaxyService`(IN g_id BIGINT, IN s_name VARCHAR(55), IN s_type VARCHAR(55), IN s_version VARCHAR(16),IN s_address VARCHAR(55), IN s_tcp INT, IN s_udp INT, IN s_ping INT, IN s_status INT, IN s_heartbeat DATETIME, in s_created DATETIME, IN s_updated DATETIME)
BEGIN

	-- create our service
	INSERT INTO service (galaxy_id, service_name, service_type, service_address, tcp_port, udp_port, ping_port, version, status, last_heartbeat, created_at, updated_at) VALUES (g_id, s_name, s_type, INET_ATON(s_address), s_tcp, s_udp, s_ping, s_version, s_status, s_heartbeat, s_created, s_updated);

	-- return our service id
	SELECT id, last_heartbeat FROM service WHERE service_name = s_name AND galaxy_id = g_id;

END $$
