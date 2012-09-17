﻿/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

use swganh_galaxy;

DELIMITER $$

CREATE PROCEDURE `sp_CharacterCreate`(IN `account_id` INT, IN `galaxy_id` INT, IN `firstname` char(30), IN `lastname` char(50), IN `profession` char(64), IN `city` char(32), IN `scale` FLOAT, IN `biography` text(2048), IN `appearance_customization` BLOB, IN `hair_model` CHAR(64), IN `hair_customization` BLOB, IN `base_model_string` CHAR(64), OUT `character_id` BIGINT
    )
charCreate:BEGIN

  -- Declare Var(s)

  DECLARE gender INT;
  DECLARE nameCheck INT;
  DECLARE shortSpecies VARCHAR(32);
  DECLARE character_id BIGINT;
  DECLARE new_player_id BIGINT;
  DECLARE inventory_id BIGINT;
  DECLARE datapad_id BIGINT;
  DECLARE bank_id BIGINT;
  DECLARE spawn_x FLOAT;
  DECLARE spawn_y FLOAT;
  DECLARE spawn_z FLOAT;
  DECLARE planet INT;
  DECLARE race_id INT;
  DECLARE health INT;
  DECLARE strength INT;
  DECLARE constitution INT;
  DECLARE action INT;
  DECLARE quickness INT;
  DECLARE stamina INT;
  DECLARE mind INT;
  DECLARE focus INT;
  DECLARE willpower INT;
  DECLARE profession_id INT;
  DECLARE object_type_id INT;
  DECLARE hair_type_id INT;
  DECLARE hair_id BIGINT;

  DECLARE t_id INT;
  DECLARE t_species VARCHAR(16);
  DECLARE t_profession VARCHAR(16);
  DECLARE longHair VARCHAR(64);
  DECLARE arrangement_id INT DEFAULT -2;
  DECLARE permission_type INT DEFAULT 5;
  
  -- get our short species name
  SELECT sf_speciesShort(base_model_string) INTO shortSpecies;

  -- get our race id
  SELECT id FROM swganh_static.race WHERE race.name like shortSpecies into race_id;

  -- get our gender
  IF base_model_string LIKE '%female%' THEN
    SET gender = 0;
  ELSE
    SET gender = 1;
  END IF;

  -- check if our firstname & lastname is valid
  SELECT sf_CharacterCheckName(firstname, lastname, race_id, account_id) INTO nameCheck;

  IF nameCheck <> 666 THEN
    SELECT(nameCheck);
    LEAVE charCreate;
  END IF;

  -- get our new creature id
  SELECT MAX(id) FROM swganh_galaxy.characters INTO character_id;

  SET character_id = character_id + 10;

  IF character_id IS NULL OR character_id < 8589934592 THEN
    SET character_id = 8589934593;
  END IF;

  -- get our player id
  SELECT MAX(player_id) FROM swganh_galaxy.characters INTO new_player_id;

  IF new_player_id IS NULL OR new_player_id < 17179869184 THEN
    SET new_player_id = 17179869184;
  END IF;

  SET new_player_id = new_player_id + 1;

  -- get our other required IDs (inventory, datapad, hair)
  SET inventory_id = character_id + 2;
  SET datapad_id = character_id + 4;
  SET hair_id = character_id + 6;
  SET bank_id = character_id + 8;

  -- get our object_type_id
  SELECT id FROM swganh_static.objects WHERE object_string LIKE REPLACE('object/creature/player/twilek_male.iff', 'object/creature/player/', 'object/creature/player/shared_') INTO object_type_id;
  
  -- create our character hair
  IF hair_model IS NOT NULL OR hair_model != '' THEN
    SET longHair = REPLACE(hair_model, '/hair_', '/shared_hair_');  	
    SELECT id FROM swganh_static.objects WHERE swganh_static.objects.object_string LIKE longHair INTO hair_type_id;
  END IF;

  IF hair_model IS NULL OR hair_model = '' THEN
    SET hair_type_id = 0;
	END IF;

  -- get our location details
  SELECT planet_id, x, y, z FROM swganh_static.starting_location WHERE location LIKE city INTO planet, spawn_x, spawn_y, spawn_z;

  -- get our starting HAM details
  SELECT * FROM swganh_static.starting_attributes WHERE starting_attributes.species = shortSpecies AND starting_attributes.profession = profession INTO t_id, t_species, t_profession, health, strength, constitution, action, quickness, stamina, mind, focus, willpower;

  -- create our character
  INSERT INTO characters VALUES (character_id, new_player_id, account_id, 1, firstname, lastname, gender, race_id, planet, 0, spawn_x, spawn_y, spawn_z, 0, 0, 0, 0, NOW(), 0, 0, 0, permission_type, arrangement_id, arrangement_id, NOW(), NOW());
  INSERT INTO character_appearance VALUES (character_id, scale, appearance_customization, hair_type_id, hair_id, hair_customization, -2, 0);
  INSERT INTO character_attributes VALUES (character_id, health, strength, constitution, action, quickness, stamina, mind, focus, willpower, health, strength, constitution, action, quickness, stamina, mind, focus, willpower, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0, 100, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, profession, 0, object_type_id, object_type_id, object_type_id);
  INSERT INTO character_flags VALUES (character_id, 0, 0, 0, 0, 0);
  INSERT INTO character_credits VALUES (character_id, bank_id, arrangement_id, 10000, 10000);
  
  -- create our biography
  INSERT INTO character_biographies VALUES (character_id, biography);

  -- create our character additional data
  INSERT INTO character_guild VALUES (character_id, 0);
  INSERT INTO character_faction VALUES (character_id, 2, 0);  -- rebel
  INSERT INTO character_faction VALUES (character_id, 3, 0);  -- imperial

  -- create our inventory / datapad
  INSERT INTO inventories VALUES (inventory_id, character_id, 10708, arrangement_id, 6);
  INSERT INTO datapads VALUES (datapad_id, character_id, 7233, arrangement_id, 6);

  -- get our starting skill (profession)
  SELECT skill_id FROM swganh_static.skills WHERE skills.skill_name like profession INTO profession_id;

  IF city <> 'tutorial' THEN
    SET profession_id = profession_id + 1;
    CALL sp_CharacterCreateSkills(character_id, profession_id, race_id);
    CALL sp_CharacterCreateXP(character_id, profession_id);
  END IF;

  -- create the starting items
  CALL sp_CharacterCreateStartingItems(inventory_id, race_id, profession_id - 1, gender);

  -- Debug
  -- SELECT 'Character ID --> ', character_id;
  -- SELECT 'Species -------> ', shortSpecies;
  -- SELECT 'Profession ----> ', profession;
  -- SELECT 'Gender --------> ', gender;
  -- SELECT 'Location ------> ', planet, spawn_x, spawn_y, spawn_z;
  -- SELECT 'HAM -----------> ', health, strength, constitution, action, quickness, stamina, mind, focus, willpower;

END $$