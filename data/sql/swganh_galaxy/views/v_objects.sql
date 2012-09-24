/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

--
-- Table structure for view `v_objects`
--

DROP TABLE IF EXISTS `v_objects`;
DROP VIEW IF EXISTS `v_objects`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE TABLE `v_objects` (
  `id` bigint(20) unsigned,
  `planet_id` bigint(20),
  `parent_id` bigint(20),
  `iff_template_text` varchar(255),
  `x` float,
  `y` float,
  `z` float,
  `oX` float,
  `oY` float,
  `oZ` float,
  `oW` float,
  `complexity` bigint(20),
  `stf_name_file_id` varchar(255),
  `stf_name_string_id` varchar(255),
  `custom_name` varchar(255),
  `volume` bigint(20),
  `object_type` int(11)
  
) ENGINE=MyISAM */;

USE `swganh_galaxy`;

--
-- Final view structure for view `v_objects`
--

DROP TABLE IF EXISTS `v_objects`;
DROP VIEW IF EXISTS `v_objects`;
CREATE VIEW `v_objects` AS 
-- characters
	

SELECT 
	characters.id AS id,
	characters.planet_id AS planet_id,
	characters.parent_id AS parent_id,
	swganh_static.objects.object_string AS iff_template_text,
	characters.x AS x,
	characters.y AS y,
	characters.z AS z,
	characters.oX AS oX,
	characters.oY AS oY,
	characters.oZ AS oZ,
	characters.oW AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	CONCAT(characters.firstname, ' ', characters.lastname) AS custom_name,
	characters.arrangement_id AS arrangement_id,
	characters.permission_type AS permission_type,
    swganh_static.object_types.object_type,
	0 AS volume
FROM characters
  LEFT JOIN character_attributes ON (characters.id = character_attributes.character_id)
  LEFT JOIN swganh_static.objects ON (character_attributes.object_template_id = swganh_static.objects.id)
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)
  
UNION

	-- players

SELECT
	characters.player_id AS id,
	characters.planet_id AS planet_id,
	characters.id AS parent_id,
	'object/player/shared_player.iff' AS iff_template_text,
	characters.x AS x,
	characters.y AS y,
	characters.z AS z,
	characters.oX AS oX,
	characters.oY AS oY,
	characters.oZ AS oZ,
	characters.oW AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	CONCAT(characters.firstname, ' ', characters.lastname) AS custom_name,
	characters.player_arrangement_id AS arrangement_id,
	5 AS permission_type,
	1347174745 AS object_type,
	0 AS volume
FROM characters
  LEFT JOIN character_attributes ON (characters.id = character_attributes.character_id)
  LEFT JOIN swganh_static.objects ON (character_attributes.object_template_id = swganh_static.objects.id)
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)

UNION

	-- hair

SELECT
	character_appearance.hair_id AS id,
	characters.planet_id AS planet_id,
	characters.id AS parent_id,
	swganh_static.objects.object_string AS iff_template_text,
	characters.x AS x,
	characters.y AS y,
	characters.z AS z,
	characters.oX AS oX,
	characters.oY AS oY,
	characters.oZ AS oZ,
	characters.oW AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	CONCAT(characters.firstname, ' ', characters.lastname) AS custom_name,
	character_appearance.hair_arrangement_id AS arrangement_id,
	1 AS permission_type,
	swganh_static.object_types.object_type,
	0 AS volume
FROM characters
  LEFT JOIN character_appearance ON (characters.id = character_appearance.character_id)
  LEFT JOIN swganh_static.objects ON (character_appearance.hair_model = swganh_static.objects.id)
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)
WHERE character_appearance.hair_model IS NOT NULL		

UNION

	-- inventories

SELECT 
	inventories.id AS id,
	0 AS planet_id,
	inventories.parent_id AS parent_id,
	swganh_static.objects.object_string AS iff_template_text,
	0 AS x,
	0 AS y,
	0 AS z,
	0 AS oX,
	0 AS oY,
	0 AS oZ,
	0 AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	'' AS custom_name,
	inventories.arrangement_id AS arrangement_id,
	inventories.permission_type AS permission_type,
	swganh_static.object_types.object_type,
	0 AS volume
FROM inventories
  LEFT JOIN swganh_static.objects ON (inventories.inventory_type = swganh_static.objects.id)
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)

UNION

	-- datapads

SELECT 
	datapads.id AS id,
	0 AS planet_id,
	datapads.parent_id AS parent_id,
	swganh_static.objects.object_string AS iff_template_text,
	0 AS x,
	0 AS y,
	0 AS z,
	0 AS oX,
	0 AS oY,
	0 AS oZ,
	0 AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	'' AS custom_name,
	datapads.arrangement_id AS arrangement_id,
	datapads.permission_type AS permission_type,
	swganh_static.object_types.object_type,
	0 AS volume
FROM datapads
  LEFT JOIN swganh_static.objects ON (datapads.datapad_type = swganh_static.objects.id)
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)

UNION

	-- banks
	
SELECT 
	character_credits.bank_id AS id,
	0 AS planet_id,
	characters.id AS parent_id,
	'object/tangible/bank/shared_character_bank.iff' AS iff_template_text,
	0 AS x,
	0 AS y,
	0 AS z,
	0 AS oX,
	0 AS oY,
	0 AS oZ,
	0 AS oW,
	0 AS complexity,
	'item_n' AS stf_name_file_id,
	'bank' AS stf_name_string_id,
	'' AS custom_name,
	character_credits.bank_arrangement_id AS arrangement_id,
	6 AS permission_type,
	1230261839 AS object_type,
	0 AS volume
FROM characters
  LEFT JOIN character_credits ON (characters.id = character_credits.character_id)

UNION

	-- items

SELECT 
	items.id AS id,
	items.planet_id AS planet_id,
	items.parent_id AS parent_id,
	swganh_static.objects.object_string AS iff_template_text,
	items.x AS x,
	items.y AS y,
	items.z AS z,
	items.oX AS oX,
	items.oY AS oY,
	items.oZ AS oZ,
	items.oW AS oW,
	0 AS complexity,
	swganh_static.objects.objectName_1 AS stf_name_file_id,
	swganh_static.objects.objectName_2 AS stf_name_string_id,
	items.custom_name AS custom_name,
	items.arrangement_type AS arrangement_id,
	items.permission_type AS permission_type,
	swganh_static.object_types.object_type,
	1 AS volume
FROM items
  LEFT JOIN swganh_static.objects ON (items.item_type = swganh_static.objects.id) 
  LEFT JOIN swganh_static.object_types ON ( swganh_static.objects.object_type = swganh_static.object_types.id)