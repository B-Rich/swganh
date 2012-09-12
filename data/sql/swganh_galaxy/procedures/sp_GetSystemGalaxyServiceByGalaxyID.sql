/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2012 The SWG:ANH Team
---------------------------------------------------------------------------------------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

use swganh_galaxy;

DELIMITER $$

DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_GetSystemGalaxyServiceByGalaxyID` $$
CREATE PROCEDURE `sp_GetSystemGalaxyServiceByGalaxyID`(IN g_id INT)
BEGIN

  -- Return our service details
  SELECT id, galaxy_id, name, type, version, address, tcp_port, udp_port, ping_port, status, TIMESTAMP(last_pulse) as last_pulse_timestamp FROM swganh_galaxy_manager.service WHERE galaxy_id = g_id ORDER BY swganh_galaxy_manager.service.type;

END $$