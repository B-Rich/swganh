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

--
-- Table structure for view `v_tangibles`
--

DROP TABLE IF EXISTS `v_tangibles`;
DROP VIEW IF EXISTS `v_tangibles`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `v_tangibles` (
  `id` bigint(20) unsigned,
  `customization` blob,
  `options_bitmask` bigint(20),
  `incap_timer` bigint(20),
  `condition_damage` bigint(11),
  `condition_max` bigint(11),
  `is_static` bigint(20)
) ENGINE=MyISAM */;
SET character_set_client = @saved_cs_client;

USE `swganh_galaxy`;

--
-- Final view structure for view `v_tangibles`
--

/*!50001 DROP TABLE IF EXISTS `v_tangibles`*/;
/*!50001 DROP VIEW IF EXISTS `v_tangibles`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50001 VIEW `v_tangibles` AS select `characters`.`id` AS `id`,`character_appearance`.`customization` AS `customization`,`character_attributes`.`options_bitmask` AS `options_bitmask`,0 AS `incap_timer`,0 AS `condition_damage`,0 AS `condition_max`,0 AS `is_static` from ((`characters` left join `character_appearance` on((`characters`.`id` = `character_appearance`.`character_id`))) left join `character_attributes` on((`characters`.`id` = `character_attributes`.`character_id`))) union select `items`.`id` AS `id`,'' AS `customization`,0 AS `options_bitmask`,0 AS `incap_timer`,`items`.`condition_damage` AS `condition_damage`,`items`.`condition_max` AS `condition_max`,0 AS `is_static` from `items` */;