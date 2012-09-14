
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

-- Dumping structure for procedure swganh_static.sp_GetObjectTemplates
DROP PROCEDURE IF EXISTS `sp_GetObjectTemplates`;
DELIMITER //
CREATE PROCEDURE `sp_GetObjectTemplates`()
BEGIN
SELECT i.iff_template, i.object_type FROM iff_templates i WHERE i.object_type != 0;
END//
DELIMITER ;
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
