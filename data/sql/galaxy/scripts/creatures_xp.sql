
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `creatures_xp` (
  `creature_id` bigint(20) NOT NULL,
  `xp_type_id` int(11) NOT NULL,
  `value` int(10) NOT NULL default '0',
  PRIMARY KEY  (`creature_id`,`xp_type_id`),
  KEY `fk_charxp_xp_xp` (`xp_type_id`),
  CONSTRAINT `character_xp_ibfk_2` FOREIGN KEY (`creature_id`) REFERENCES `creature` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_charxp_xp_xp` FOREIGN KEY (`xp_type_id`) REFERENCES `xp_type` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DELETE FROM `creatures_xp`;
    
/*!40000 ALTER TABLE `creatures_xp` DISABLE KEYS */;
/*!40000 ALTER TABLE `creatures_xp` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
