-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.27-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL version:             7.0.0.4053
-- Date/time:                    2012-10-02 14:36:44
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

-- Dumping structure for procedure galaxy.sp_GetAccountId
DROP PROCEDURE IF EXISTS `sp_GetAccountId`;
DELIMITER //
CREATE PROCEDURE `sp_GetAccountId`(IN `in_id` BIGINT)
BEGIN
select reference_id from player_account where id = in_id;
END//
DELIMITER ;
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
