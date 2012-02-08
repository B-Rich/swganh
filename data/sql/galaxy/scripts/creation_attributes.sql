
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `creation_attributes` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `profession_id` int(11) NOT NULL,
  `species_id` int(11) NOT NULL,
  `health` int(10) unsigned NOT NULL,
  `strength` int(10) unsigned NOT NULL,
  `constitution` int(10) unsigned NOT NULL,
  `action` int(10) unsigned NOT NULL,
  `quickness` int(10) unsigned NOT NULL,
  `stamina` int(10) unsigned NOT NULL,
  `mind` int(10) unsigned NOT NULL,
  `focus` int(10) unsigned NOT NULL,
  `willpower` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`),
  CONSTRAINT `FK_98197A65BF023994` FOREIGN KEY (`profession_id`) REFERENCES `skill` (`id`) ON DELETE CASCADE,
  CONSTRAINT `FK_98197A65BA023905` FOREIGN KEY (`species_id`) REFERENCES `species` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=61 DEFAULT CHARSET=latin1 COMMENT='Starting HAM attributes';

DELETE FROM `creation_attributes`;
    
/*!40000 ALTER TABLE `creation_attributes` DISABLE KEYS */;
INSERT INTO `creation_attributes` (`id`,`species_id`,`profession_id`,`health`,`strength`,`constitution`,`action`,`quickness`,`stamina`,`mind`,`focus`,`willpower`) VALUES 
 (1,1,50,700,400,400,800,400,400,1100,600,600),
 (2,6,50,600,300,300,1000,600,400,1100,600,500),
 (3,4,50,600,300,300,700,300,450,1300,800,650),
 (4,2,50,600,300,300,900,500,750,1000,500,550),
 (5,3,50,850,600,700,700,300,300,1000,500,600),
 (6,7,50,800,300,600,1050,700,400,800,350,400),
 (7,5,50,950,650,450,900,400,400,1100,650,600),
 (8,8,50,800,300,300,1000,300,300,1000,500,900),
 (9,9,50,600,300,300,700,300,450,1300,800,550),
 (10,10,50,800,300,300,1000,300,300,1000,500,800),
 (11,1,30,900,400,450,900,500,500,800,450,500),
 (12,6,30,800,300,350,1100,700,500,800,450,400),
 (13,4,30,800,300,350,800,400,550,1000,650,550),
 (14,2,30,800,300,350,1000,600,850,700,350,450),
 (15,3,30,1050,600,750,800,400,400,700,350,500),
 (16,7,30,800,300,600,1050,700,400,800,350,400),
 (17,5,30,1150,650,500,1000,500,500,800,500,500),
 (18,8,30,1000,300,350,1100,400,400,700,350,800),
 (19,9,30,800,300,350,800,400,550,1000,650,550),
 (20,10,30,1000,300,350,1100,400,400,700,350,800),
 (21,1,70,700,400,400,900,500,400,1000,500,600),
 (22,6,70,600,300,300,1100,700,400,1000,500,500),
 (23,4,70,600,300,300,800,400,450,1200,700,650),
 (24,2,70,600,300,300,1000,600,750,900,400,550),
 (25,3,70,850,600,700,800,400,300,900,400,600),
 (26,7,70,600,300,550,1050,700,300,1000,400,500),
 (27,5,70,950,650,450,1000,500,500,1000,550,600),
 (28,8,70,800,300,300,1100,400,300,900,400,900),
 (29,9,70,600,300,300,800,400,450,1200,700,650),
 (30,10,70,800,300,300,1100,400,300,900,400,900),
 (31,1,90,1100,600,500,900,450,450,600,400,400),
 (32,6,90,1000,500,400,1100,650,450,600,400,300),
 (33,4,90,1000,500,400,800,350,500,800,600,450),
 (34,2,90,1000,500,400,1000,550,800,500,300,350),
 (35,3,90,1250,800,800,800,350,350,500,300,400),
 (36,7,90,1000,500,650,1050,650,350,600,300,300),
 (37,5,90,1350,850,550,1000,450,450,600,450,400),
 (38,8,90,1200,500,400,1100,350,350,500,300,700),
 (39,9,90,1000,500,400,800,350,500,800,600,450),
 (40,10,90,1200,500,400,1100,350,350,500,300,700),
 (41,1,10,600,400,400,1100,500,500,900,500,500),
 (42,6,10,500,300,300,1300,700,500,900,500,400),
 (43,4,10,500,300,300,1000,400,550,1100,700,550),
 (44,2,10,500,300,300,1200,600,850,800,400,450),
 (45,3,10,750,600,700,1000,400,400,800,400,500),
 (46,7,10,500,300,550,1250,700,400,900,400,400),
 (47,5,10,850,650,450,1200,500,500,900,550,500),
 (48,8,10,700,300,300,1300,400,400,800,400,800),
 (49,9,10,500,300,300,1000,400,550,1100,700,550),
 (50,10,10,700,300,300,1300,400,400,800,400,800),
 (51,1,109,1100,550,400,900,550,400,700,400,400),
 (52,6,109,1000,450,300,1100,750,400,700,400,400),
 (53,4,109,1000,450,300,800,450,450,900,600,450),
 (54,2,109,1000,450,300,1000,650,750,600,300,350),
 (55,3,109,1250,750,700,800,450,300,600,300,400),
 (56,7,109,1000,450,550,1050,750,300,700,300,300),
 (57,5,109,1350,800,450,1000,550,400,700,450,400),
 (58,8,109,1200,450,300,1100,450,300,600,300,700),
 (59,9,109,1000,450,300,800,450,450,900,600,450),
 (60,10,109,1200,450,300,1100,450,300,600,300,700);
/*!40000 ALTER TABLE `creation_attributes` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
