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
-- Table structure for view `v_intangibles`
--

DROP TABLE IF EXISTS `v_intangibles`;
/*!50001 DROP VIEW IF EXISTS `v_intangibles`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `v_intangibles` (
  `id` varchar(2),
  `stf_detail_file` varchar(15),
  `stf_detail_string` varchar(17),
  `custom_name` varchar(11),
  `genericInt` varchar(11)
) ENGINE=MyISAM */;

USE `swganh_galaxy`;

--
-- Final view structure for view `v_intangibles`
--

/*!50001 DROP TABLE IF EXISTS `v_intangibles`*/;
/*!50001 DROP VIEW IF EXISTS `v_intangibles`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50001 VIEW `v_intangibles` AS select 'id' AS `id`,'stf_detail_file' AS `stf_detail_file`,'stf_detail_string' AS `stf_detail_string`,'custom_name' AS `custom_name`,'generic_int' AS `genericInt` */;