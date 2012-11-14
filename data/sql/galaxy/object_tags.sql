-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.25-MariaDB-log - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL version:             7.0.0.4053
-- Date/time:                    2012-11-12 12:03:52
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

-- Dumping structure for table galaxy.object_tags
DROP TABLE IF EXISTS `object_tags`;
CREATE TABLE IF NOT EXISTS `object_tags` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `object_id` bigint(20) NOT NULL,
  `tag` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `object_id` (`object_id`),
  CONSTRAINT `FK__object` FOREIGN KEY (`object_id`) REFERENCES `object` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Dumping data for table galaxy.object_tags: ~0 rows (approximately)
DELETE FROM `object_tags`;
/*!40000 ALTER TABLE `object_tags` DISABLE KEYS */;
/*!40000 ALTER TABLE `object_tags` ENABLE KEYS */;
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
