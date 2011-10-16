# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.3.1-MariaDB
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3603
# Date/time:                    2011-10-15 23:25:17
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table galaxy.player_session
CREATE TABLE IF NOT EXISTS `player_session` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `player` int(11) NOT NULL,
  `session_key` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=80 DEFAULT CHARSET=latin1;

# Dumping data for table galaxy.player_session: ~65 rows (approximately)
/*!40000 ALTER TABLE `player_session` DISABLE KEYS */;
INSERT INTO `player_session` (`id`, `player`, `session_key`) VALUES
	(1, 2, '2011-Oct-15 10:34:12.860786583892433'),
	(2, 2, '2011-Oct-15 11:00:04.2395191911554948'),
	(3, 2, '2011-Oct-15 11:01:58.578059108479490'),
	(4, 2, '2011-Oct-15 11:17:55.731805650786457'),
	(5, 2, '2011-Oct-15 12:05:00.5653771487939274'),
	(6, 2, '2011-Oct-15 12:08:01.1237042075744114'),
	(7, 2, '2011-Oct-15 12:49:19.1854411764510336'),
	(8, 2, '2011-Oct-15 12:50:48.2655361754873045'),
	(9, 2, '2011-Oct-15 12:57:43.378279915998978'),
	(10, 2, '2011-Oct-15 13:04:25.911303334053504'),
	(11, 2, '2011-Oct-15 13:04:47.329528600393932'),
	(12, 2, '2011-Oct-15 13:12:56.993535264187668'),
	(13, 2, '2011-Oct-15 13:25:08.7733901110267100'),
	(14, 2, '2011-Oct-15 13:29:54.992761915279206'),
	(15, 2, '2011-Oct-15 13:34:00.0257761180118089'),
	(16, 2, '2011-Oct-15 13:34:36.1828441818830991'),
	(17, 2, '2011-Oct-15 13:35:04.8634852110858782'),
	(18, 2, '2011-Oct-15 13:35:18.211248420897138'),
	(19, 2, '2011-Oct-15 13:36:13.7594251075671536'),
	(20, 2, '2011-Oct-15 14:02:35.2878841229588087'),
	(21, 2, '2011-Oct-15 14:19:14.2210191810387001'),
	(22, 2, '2011-Oct-15 14:20:48.4774101412176211'),
	(23, 2, '2011-Oct-15 14:22:15.2193721808469961'),
	(24, 2, '2011-Oct-15 14:22:24.514903674461812'),
	(25, 2, '2011-Oct-15 14:22:35.389525614345484'),
	(26, 2, '2011-Oct-15 14:22:51.2714341792301727'),
	(27, 2, '2011-Oct-15 14:23:45.498535542708350'),
	(28, 2, '2011-Oct-15 14:24:34.3233283475407'),
	(29, 2, '2011-Oct-15 14:24:45.657976452202188'),
	(30, 2, '2011-Oct-15 14:24:57.475652244333101'),
	(31, 2, '2011-Oct-15 14:27:15.7725621167001973'),
	(32, 2, '2011-Oct-15 14:35:10.1146931495082282'),
	(33, 2, '2011-Oct-15 19:14:49.1443991240941611'),
	(34, 2, '2011-Oct-15 19:17:58.9742571082620740'),
	(35, 2, '2011-Oct-15 19:18:10.851936407907072'),
	(36, 2, '2011-Oct-15 19:18:26.617838982351806'),
	(37, 2, '2011-Oct-15 19:23:12.504189202717191'),
	(38, 2, '2011-Oct-15 19:25:18.3373871921131807'),
	(39, 2, '2011-Oct-15 20:09:08.3468151574718986'),
	(40, 4, '2011-Oct-15 20:14:55.871692382036121'),
	(41, 2, '2011-Oct-15 21:43:08.650422915998978'),
	(42, 2, '2011-Oct-15 21:44:07.134767329085001'),
	(43, 2, '2011-Oct-15 21:46:34.697207410916549'),
	(44, 2, '2011-Oct-15 21:48:15.994001334053504'),
	(45, 2, '2011-Oct-15 21:49:19.881655600393932'),
	(46, 2, '2011-Oct-15 21:50:26.6334731550269654'),
	(47, 2, '2011-Oct-15 21:51:38.780599746135632'),
	(48, 2, '2011-Oct-15 21:51:59.5287861937335259'),
	(49, 2, '2011-Oct-15 21:52:36.1218791407323509'),
	(50, 2, '2011-Oct-15 21:52:55.7930041037269226'),
	(51, 2, '2011-Oct-15 22:07:51.8832581830570219'),
	(52, 2, '2011-Oct-15 22:08:35.466750329085001'),
	(53, 4, '2011-Oct-15 22:09:23.3984921127886644'),
	(54, 4, '2011-Oct-15 22:09:44.0286721479834330'),
	(55, 4, '2011-Oct-15 22:10:35.9796431286091244'),
	(56, 4, '2011-Oct-15 22:10:49.520418441081887'),
	(57, 4, '2011-Oct-15 22:11:11.9927032072208797'),
	(58, 4, '2011-Oct-15 22:12:17.5964561384937044'),
	(59, 2, '2011-Oct-15 22:12:59.290840915998978'),
	(60, 5, '2011-Oct-15 22:18:04.423293905737709'),
	(61, 2, '2011-Oct-15 22:18:30.869806329085001'),
	(62, 5, '2011-Oct-15 22:32:32.4999441132157944'),
	(63, 2, '2011-Oct-15 22:32:56.055291832247424'),
	(64, 2, '2011-Oct-15 22:35:37.083502274145258'),
	(65, 5, '2011-Oct-15 22:36:09.3263462075744114'),
	(66, 5, '2011-Oct-15 22:43:20.125986935330467'),
	(67, 2, '2011-Oct-15 22:50:08.1983271014652949'),
	(68, 5, '2011-Oct-15 22:50:14.537689211499130'),
	(69, 2, '2011-Oct-15 22:50:58.8642241487222956'),
	(70, 5, '2011-Oct-15 22:51:45.5578952097756459'),
	(71, 2, '2011-Oct-15 22:51:59.4766912094078862'),
	(72, 2, '2011-Oct-15 22:52:46.687392415000720'),
	(73, 5, '2011-Oct-15 22:55:17.4060122054696072'),
	(74, 5, '2011-Oct-15 22:55:40.7673481614432571'),
	(75, 5, '2011-Oct-15 23:00:45.431774915998978'),
	(76, 5, '2011-Oct-15 23:01:41.641989650786457'),
	(77, 5, '2011-Oct-15 23:05:16.856299650786457'),
	(78, 5, '2011-Oct-15 23:06:03.7569811467093917'),
	(79, 5, '2011-Oct-15 23:08:53.349681650786457');
/*!40000 ALTER TABLE `player_session` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
