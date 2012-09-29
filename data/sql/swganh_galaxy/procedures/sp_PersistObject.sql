/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$
DROP PROCEDURE IF EXISTS `swganh_galaxy`.`sp_PersistObject`$$
CREATE PROCEDURE `sp_PersistObject`(IN `in_object_id` BIGINT, IN `in_scene_id` INT, IN `in_parent_id` BIGINT, IN `template_string` VARCHAR(255), IN `posX` dOUBLE, IN `posY` dOUBLE, IN `posZ` DOUBLE, IN `oX` DOUBLE, IN `oY` DOUBLE, IN `oZ` DOUBLE, IN `oW` DOUBLE, IN `in_complexity` DOUBLE, IN `in_stf_name_file` VARCHAR(255), IN `in_stf_name_string` VARCHAR(255), IN `in_custom_name` VARCHAR(50), IN `in_volume` INT, IN `in_arrangement_id` INT, IN `in_permission_type` INT, IN `object_type` INT)
BEGIN
	
	-- First get our template_id
    DECLARE iff_template INT;

    SELECT swganh_static.objects.id FROM swganh_static.objects WHERE swganh_static.objects.object_string LIKE template_string INTO iff_template;
	
	-- Determine what the object is
	IF 	   object_type 	=	1112885583 		THEN	--building'
	ELSEIF object_type 	=	1129465167 		THEN	--creature'
	ELSEIF object_type 	=	1145850183 		THEN	--guild'
	ELSEIF object_type 	=	1178818900 		THEN	--factory_crate'
	ELSEIF object_type 	=	1196578128 		THEN	--group'
	ELSEIF object_type 	=	1229869903 		THEN	--installation'
	ELSEIF object_type 	=	1230261839 		THEN	--intangible'
	ELSEIF object_type 	=	1296651087 		THEN	--mission'
	ELSEIF object_type 	=	1297302351 		THEN	--manufacture_schematic'
	ELSEIF object_type 	=	1347174745 		THEN	--player'
	ELSEIF object_type 	=	1380142671 		THEN	--resource_container'
	ELSEIF object_type 	=	1396919380 		THEN	--cell'
	ELSEIF object_type 	=	1398030671 		THEN	--static'
	ELSEIF object_type 	=	1413566031 		THEN	--tangible'
	ELSEIF object_type 	=	1463900496 		THEN	--waypoint'
	ELSEIF object_type 	=	1789660414 		THEN	--weapon'
	ELSEIF object_type 	=	1874303456 		THEN	--ship'
	END IF;

END $$