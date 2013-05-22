/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

DROP PROCEDURE IF EXISTS `sp_ChatRoomAdd`;

DELIMITER //

CREATE PROCEDURE `sp_ChatRoomAdd`(IN in_is_private TINYINT(1), IN in_is_muted TINYINT(1), 
	IN in_name CHAR(50), IN in_creator_id BIGINT(20), IN in_title CHAR(50))
BEGIN

	INSERT INTO `chat_rooms` 
	(`is_private`, `is_muted`, `name`, `creator_id`, `owner_id`, `title`) 
	VALUES (in_is_private, in_is_muted, in_name, in_creator_id, in_creator_id, in_title);
	
	SELECT MAX(id) FROM chat_rooms;

END //
DELIMITER ;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;