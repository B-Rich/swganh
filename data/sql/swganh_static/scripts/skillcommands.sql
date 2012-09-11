-- ---------------------------------------------------------------------------------------
-- This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)
--
-- For more information, visit http://www.swganh.com
--
-- Copyright (c) 2006 - 2012 The SWG:ANH Team
-- ---------------------------------------------------------------------------------------
-- This library is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Lesser General Public
-- License as published by the Free Software Foundation; either
-- version 2.1 of the License, or (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public
-- License along with this library; if not, write to the Free Software
-- Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
-- ---------------------------------------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

USE swganh_static;

--
-- Table structure for table `skillcommands`
--

DROP TABLE IF EXISTS `skillcommands`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `skillcommands` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` char(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `pk_skillcommands_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=955 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `skillcommands`
--

LOCK TABLES `skillcommands` WRITE;
/*!40000 ALTER TABLE `skillcommands` DISABLE KEYS */;
INSERT INTO `skillcommands` VALUES (115,'access_fee'),
(242,'actionShot1'),
(325,'actionShot2'),
(950,'admin_broadcast'),
(952,'admin_broadcastGalaxy'),
(951,'admin_broadcastPlanet'),
(954,'admin_cancelShutdownGalaxy'),
(953,'admin_shutdownGalaxy'),
(942,'admin_sys_msg'),
(943,'admin_warp_self'),
(532,'ad_fees_1'),
(247,'aim'),
(694,'animalAttack'),
(693,'animalCalm'),
(692,'animalScare'),
(583,'applyDisease'),
(582,'applyPoison'),
(502,'areatrack'),
(503,'areatrack_animal'),
(505,'areatrack_direction'),
(507,'areatrack_distance'),
(506,'areatrack_npc'),
(508,'areatrack_player'),
(770,'avoidIncapacitation'),
(490,'bandfill'),
(132,'berserk1'),
(142,'berserk2'),
(555,'bleedingShot'),
(214,'bodyShot1'),
(224,'bodyShot2'),
(303,'bodyShot3'),
(589,'boostmorale'),
(872,'bstrike1'),
(874,'bstrike2'),
(859,'bstrike3'),
(345,'burstShot1'),
(348,'burstShot2'),
(134,'centerOfBeing'),
(632,'cert_axe_heavy_duty'),
(173,'cert_axe_vibro'),
(154,'cert_baton_gaderiffi'),
(397,'cert_baton_stun'),
(635,'cert_carbine_cdef'),
(195,'cert_carbine_dh17'),
(234,'cert_carbine_dh17_snubnose'),
(243,'cert_carbine_dxr6'),
(237,'cert_carbine_e11'),
(244,'cert_carbine_ee3'),
(327,'cert_carbine_elite'),
(240,'cert_carbine_laser'),
(328,'cert_carbine_nym_slugthrower'),
(793,'cert_droid_astromech_1'),
(833,'cert_droid_astromech_2'),
(839,'cert_droid_astromech_3'),
(845,'cert_droid_astromech_4'),
(851,'cert_droid_astromech_5'),
(800,'cert_droid_astromech_6'),
(569,'cert_grenade_cryoban'),
(565,'cert_grenade_fragmentation'),
(636,'cert_grenade_fragmentation_light'),
(570,'cert_grenade_glop'),
(571,'cert_grenade_imperial_detonator'),
(566,'cert_grenade_proton'),
(572,'cert_grenade_thermal_detonator'),
(574,'cert_heavy_acid_beam'),
(575,'cert_heavy_lightning_beam'),
(573,'cert_heavy_particle_beam'),
(133,'cert_knife_dagger'),
(629,'cert_knife_stone'),
(630,'cert_knife_survival'),
(158,'cert_knife_vibroblade'),
(183,'cert_lance_controllerfp'),
(180,'cert_lance_staff_metal'),
(631,'cert_lance_staff_wood_s1'),
(179,'cert_lance_staff_wood_s2'),
(449,'cert_lance_vibrolance'),
(186,'cert_lance_vibro_axe'),
(645,'cert_onehandlightsaber'),
(723,'cert_onehandlightsaber_gen1'),
(733,'cert_onehandlightsaber_gen2'),
(737,'cert_onehandlightsaber_gen3'),
(730,'cert_onehandlightsaber_gen4'),
(771,'cert_onehandlightsaber_training'),
(792,'cert_ordnance_level1'),
(812,'cert_ordnance_level2'),
(813,'cert_ordnance_level3'),
(814,'cert_ordnance_level4'),
(815,'cert_ordnance_level5'),
(816,'cert_ordnance_level6'),
(817,'cert_ordnance_level7'),
(818,'cert_ordnance_level8'),
(798,'cert_ordnance_level9'),
(799,'cert_ordnance_levelten'),
(634,'cert_pistol_cdef'),
(194,'cert_pistol_d18'),
(222,'cert_pistol_dh17'),
(215,'cert_pistol_dl44'),
(216,'cert_pistol_dl44_metal'),
(294,'cert_pistol_dx2'),
(231,'cert_pistol_fwg5'),
(562,'cert_pistol_launcher'),
(226,'cert_pistol_power5'),
(295,'cert_pistol_republic_blaster'),
(545,'cert_pistol_scatter'),
(221,'cert_pistol_scout_blaster'),
(229,'cert_pistol_srcombat'),
(225,'cert_pistol_striker'),
(230,'cert_pistol_tangle'),
(705,'cert_polearmlightsaber'),
(724,'cert_polearmlightsaber_gen1'),
(742,'cert_polearmlightsaber_gen2'),
(746,'cert_polearmlightsaber_gen3'),
(731,'cert_polearmlightsaber_gen4'),
(564,'cert_rifle_acid_beam'),
(639,'cert_rifle_bowcaster'),
(633,'cert_rifle_cdef'),
(193,'cert_rifle_dlt20'),
(200,'cert_rifle_dlt20a'),
(212,'cert_rifle_e11'),
(563,'cert_rifle_flame_thrower'),
(211,'cert_rifle_jawa_ion'),
(205,'cert_rifle_laser'),
(546,'cert_rifle_lightning'),
(204,'cert_rifle_sg82'),
(208,'cert_rifle_spraystick'),
(258,'cert_rifle_t21'),
(201,'cert_rifle_tusken'),
(561,'cert_rocket_launcher'),
(811,'cert_starships_awing'),
(796,'cert_starships_bwing'),
(857,'cert_starships_decimator'),
(803,'cert_starships_firespray'),
(912,'cert_starships_heavyblacksunfighter'),
(907,'cert_starships_heavyhuttfighter'),
(903,'cert_starships_hutt_turret_ship'),
(908,'cert_starships_lightblacksunfighter'),
(898,'cert_starships_lighthuttfighter'),
(910,'cert_starships_mediumblacksunfighter'),
(905,'cert_starships_mediumhuttfighter'),
(868,'cert_starships_tieadvanced'),
(869,'cert_starships_tieaggressor'),
(866,'cert_starships_tiebomber'),
(861,'cert_starships_tiefighter'),
(863,'cert_starships_tiefighterin'),
(855,'cert_starships_tiefighterlight'),
(865,'cert_starships_tieinterceptor'),
(858,'cert_starships_tieoppressor'),
(809,'cert_starships_xwing'),
(797,'cert_starships_ykl37r'),
(900,'cert_starships_yt1300'),
(805,'cert_starships_ywing'),
(807,'cert_starships_ywinglongprobe'),
(791,'cert_starships_z95headhunter'),
(153,'cert_sword_01'),
(155,'cert_sword_02'),
(167,'cert_sword_2h_axe'),
(176,'cert_sword_2h_cleaver'),
(170,'cert_sword_2h_katana'),
(428,'cert_sword_2h_maul'),
(446,'cert_sword_2h_scythe'),
(164,'cert_sword_blade_rantok'),
(161,'cert_sword_blade_ryyk'),
(670,'cert_twohandlightsaber'),
(725,'cert_twohandlightsaber_gen1'),
(738,'cert_twohandlightsaber_gen2'),
(741,'cert_twohandlightsaber_gen3'),
(732,'cert_twohandlightsaber_gen4'),
(362,'cert_vibroknuckler'),
(765,'channelForce'),
(354,'chargeShot1'),
(358,'chargeShot2'),
(595,'city_map'),
(602,'city_spec_cloning'),
(609,'city_spec_doctor'),
(608,'city_spec_entertainer'),
(598,'city_spec_industry'),
(610,'city_spec_missions'),
(599,'city_spec_research'),
(611,'city_spec_sample_rich'),
(603,'city_spec_stronghold'),
(475,'colorlights'),
(504,'conceal'),
(271,'concealShot'),
(554,'confusionShot'),
(342,'cripplingShot'),
(499,'cureDisease'),
(497,'curePoison'),
(105,'customizeVehicle'),
(3,'dancer'),
(476,'dazzle'),
(80,'diagnose'),
(311,'disarmingShot1'),
(298,'disarmingShot2'),
(477,'distract'),
(219,'diveShot'),
(313,'doubleTap'),
(90,'dragIncapacitatedPlayer'),
(767,'drainForce'),
(935,'droid+droidcommand_testweaponoverload1'),
(896,'droidcommand_engineefficiencyfour'),
(880,'droidcommand_engineefficiencyone'),
(891,'droidcommand_engineefficiencythree'),
(886,'droidcommand_engineefficiencytwo'),
(881,'droidcommand_enginenormalize'),
(895,'droidcommand_engineoverloadfour'),
(879,'droidcommand_engineoverloadone'),
(890,'droidcommand_engineoverloadthree'),
(885,'droidcommand_engineoverloadtwo'),
(794,'droidcommand_mutedroid'),
(919,'droidcommand_reactornormalize'),
(932,'droidcommand_reactoroverloadfour'),
(918,'droidcommand_reactoroverloadone'),
(928,'droidcommand_reactoroverloadthree'),
(924,'droidcommand_reactoroverloadtwo'),
(849,'droidcommand_shieldadjustfrontfour'),
(831,'droidcommand_shieldadjustfrontone'),
(843,'droidcommand_shieldadjustfrontthree'),
(837,'droidcommand_shieldadjustfronttwo'),
(850,'droidcommand_shieldadjustrearfour'),
(832,'droidcommand_shieldadjustrearone'),
(844,'droidcommand_shieldadjustrearthree'),
(838,'droidcommand_shieldadjustreartwo'),
(841,'droidcommand_shieldbacktofronteighty'),
(835,'droidcommand_shieldbacktofrontfifty'),
(847,'droidcommand_shieldbacktofronthundred'),
(829,'droidcommand_shieldbacktofronttwenty'),
(852,'droidcommand_shieldemergencyfront'),
(853,'droidcommand_shieldemergencyrear'),
(842,'droidcommand_shieldfronttobackeighty'),
(836,'droidcommand_shieldfronttobackfifty'),
(848,'droidcommand_shieldfronttobackhundred'),
(830,'droidcommand_shieldfronttobacktwenty'),
(828,'droidcommand_shieldnormalize'),
(941,'droidcommand_testbacktofrontfifty'),
(940,'droidcommand_testfronttobackfifty'),
(939,'droidcommand_testweaponnormalize'),
(936,'droidcommand_testweaponoverload2'),
(937,'droidcommand_testweaponoverload3'),
(938,'droidcommand_testweaponoverload4'),
(921,'droidcommand_weapcapequalize'),
(933,'droidcommand_weapcappowerupfour'),
(920,'droidcommand_weapcappowerupone'),
(929,'droidcommand_weapcappowerupthree'),
(925,'droidcommand_weapcappoweruptwo'),
(934,'droidcommand_weapcaptoshieldfour'),
(922,'droidcommand_weapcaptoshieldone'),
(930,'droidcommand_weapcaptoshieldthree'),
(926,'droidcommand_weapcaptoshieldtwo'),
(894,'droidcommand_weaponeffeciencyfour'),
(877,'droidcommand_weaponeffeciencyone'),
(889,'droidcommand_weaponeffeciencythree'),
(884,'droidcommand_weaponeffeciencytwo'),
(878,'droidcommand_weaponnormalize'),
(893,'droidcommand_weaponoverloadfour'),
(876,'droidcommand_weaponoverloadone'),
(888,'droidcommand_weaponoverloadthree'),
(883,'droidcommand_weaponoverloadtwo'),
(550,'droid_find'),
(551,'droid_track'),
(523,'emboldenpets'),
(525,'enragepets'),
(915,'epulse1'),
(916,'epulse2'),
(902,'epulse3'),
(641,'equilibrium'),
(821,'eshields'),
(913,'ethrust'),
(871,'eweapons'),
(498,'extinguishFire'),
(556,'eyeShot'),
(37,'fanfar'),
(317,'fanShot'),
(548,'fastBlast'),
(541,'feignDeath'),
(580,'fireAcidCone1'),
(568,'fireAcidCone2'),
(579,'fireAcidSingle1'),
(581,'fireAcidSingle2'),
(487,'firejet'),
(559,'fireLightningCone1'),
(549,'fireLightningCone2'),
(558,'fireLightningSingle1'),
(560,'fireLightningSingle2'),
(84,'firstAid'),
(32,'fizz'),
(577,'flameCone1'),
(567,'flameCone2'),
(576,'flameSingle1'),
(578,'flameSingle2'),
(9,'flourish+1'),
(10,'flourish+2'),
(11,'flourish+3'),
(12,'flourish+4'),
(13,'flourish+5'),
(14,'flourish+6'),
(15,'flourish+7'),
(16,'flourish+8'),
(287,'flurryShot1'),
(290,'flurryShot2'),
(279,'flushingShot1'),
(283,'flushingShot2'),
(492,'flutedroopy'),
(70,'forage'),
(750,'forceAbsorb1'),
(758,'forceAbsorb2'),
(756,'forceArmor1'),
(759,'forceArmor2'),
(709,'forceChoke'),
(672,'forceCureDisease'),
(671,'forceCurePoison'),
(755,'forceFeedback1'),
(757,'forceFeedback2'),
(720,'forceIntimidate'),
(748,'forceIntimidate1'),
(749,'forceIntimidate2'),
(663,'forceKnockdown1'),
(697,'forceKnockdown2'),
(747,'forceKnockdown3'),
(719,'forceLightningCone1'),
(721,'forceLightningCone2'),
(696,'forceLightningSingle1'),
(699,'forceLightningSingle2'),
(768,'forceMeditate'),
(371,'forceOfWill'),
(760,'forceResistBleeding'),
(761,'forceResistDisease'),
(762,'forceResistPoison'),
(763,'forceResistStates'),
(662,'forceRun1'),
(702,'forceRun2'),
(751,'forceRun3'),
(766,'forceShield1'),
(769,'forceShield2'),
(753,'forceSpeed1'),
(754,'forceSpeed2'),
(665,'forceThrow1'),
(698,'forceThrow2'),
(703,'forceWeaken1'),
(722,'forceWeaken2'),
(588,'formup'),
(352,'fullAutoArea1'),
(356,'fullAutoArea2'),
(236,'fullAutoSingle1'),
(326,'fullAutoSingle2'),
(594,'grantZoningRights'),
(54,'harvestCorpse'),
(199,'headShot1'),
(207,'headShot2'),
(265,'headShot3'),
(657,'healActionSelf1'),
(685,'healActionSelf2'),
(684,'healActionWoundOther1'),
(715,'healActionWoundOther2'),
(658,'healActionWoundSelf1'),
(686,'healActionWoundSelf2'),
(666,'healAllOther1'),
(691,'healAllOther2'),
(661,'healAllSelf1'),
(690,'healAllSelf2'),
(644,'healBattleFatigueSelf1'),
(649,'healBattleFatigueSelf2'),
(75,'healDamage'),
(500,'healEnhance'),
(655,'healHealthSelf1'),
(681,'healHealthSelf2'),
(682,'healHealthWoundOther1'),
(714,'healHealthWoundOther2'),
(656,'healHealthWoundSelf1'),
(683,'healHealthWoundSelf2'),
(584,'healMind'),
(659,'healMindSelf1'),
(687,'healMindSelf2'),
(688,'healMindWoundOther1'),
(716,'healMindWoundOther2'),
(660,'healMindWoundSelf1'),
(689,'healMindWoundSelf2'),
(495,'healState'),
(718,'healStatesOther'),
(700,'healStatesSelf'),
(228,'healthShot1'),
(293,'healthShot2'),
(76,'healWound'),
(819,'iffscramble'),
(4,'imagedesigner'),
(825,'inspacereload'),
(824,'inspacerepair'),
(802,'inspacerr'),
(605,'installMissionTerminal'),
(131,'intimidate1'),
(141,'intimidate2'),
(695,'jediMindTrick'),
(820,'jstart1'),
(823,'jstart2'),
(801,'jstart3'),
(220,'kipUpShot'),
(40,'kloohorn'),
(553,'knockdownFire'),
(623,'language+bothese'),
(620,'language+dosh'),
(627,'language+ithorian'),
(626,'language+lekku'),
(621,'language+moncalamarian'),
(619,'language+rodese'),
(624,'language+ryl'),
(622,'language+shyriiwook'),
(628,'language+sullustan'),
(625,'language+zabrak'),
(544,'lastDitch'),
(233,'legShot1'),
(239,'legShot2'),
(339,'legShot3'),
(543,'lowBlow'),
(534,'maintenance_fees_1'),
(600,'manage_militia'),
(593,'manage_taxes'),
(25,'mandoviol'),
(58,'maskscent'),
(77,'medicalForage'),
(361,'meditate'),
(421,'melee1hBlindHit1'),
(424,'melee1hBlindHit2'),
(157,'melee1hBodyHit1'),
(415,'melee1hBodyHit2'),
(418,'melee1hBodyHit3'),
(160,'melee1hDizzyHit1'),
(404,'melee1hDizzyHit2'),
(408,'melee1hHealthHit1'),
(413,'melee1hHealthHit2'),
(152,'melee1hHit1'),
(396,'melee1hHit2'),
(399,'melee1hHit3'),
(127,'melee1hLunge1'),
(138,'melee1hLunge2'),
(401,'melee1hScatterHit1'),
(406,'melee1hScatterHit2'),
(163,'melee1hSpinAttack1'),
(411,'melee1hSpinAttack2'),
(432,'melee2hArea1'),
(434,'melee2hArea2'),
(437,'melee2hArea3'),
(169,'melee2hHeadHit1'),
(439,'melee2hHeadHit2'),
(441,'melee2hHeadHit3'),
(166,'melee2hHit1'),
(427,'melee2hHit2'),
(430,'melee2hHit3'),
(128,'melee2hLunge1'),
(139,'melee2hLunge2'),
(444,'melee2hMindHit1'),
(445,'melee2hMindHit2'),
(175,'melee2hSpinAttack1'),
(442,'melee2hSpinAttack2'),
(172,'melee2hSweep1'),
(443,'melee2hSweep2'),
(374,'melee_damage_mitigation_1'),
(377,'melee_damage_mitigation_2'),
(365,'melee_damage_mitigation_3'),
(533,'merchant_fees_1'),
(664,'mindBlast1'),
(667,'mindBlast2'),
(210,'mindShot1'),
(263,'mindShot2'),
(297,'multiTargetPistolShot'),
(2,'musician'),
(486,'nalargon'),
(873,'nblast'),
(494,'omnibox'),
(192,'overChargeShot1'),
(197,'overChargeShot2'),
(542,'panicShot'),
(512,'pet_attack'),
(510,'pet_follow'),
(527,'pet_followother'),
(521,'pet_formation'),
(528,'pet_friend'),
(526,'pet_group'),
(519,'pet_guard'),
(520,'pet_patrol'),
(515,'pet_rangedattack'),
(511,'pet_release'),
(516,'pet_specialattack1'),
(517,'pet_specialattack2'),
(518,'pet_stay'),
(514,'pet_transfer'),
(319,'pistolMeleeDefense1'),
(322,'pistolMeleeDefense2'),
(596,'place_bank'),
(472,'place_cantina'),
(592,'place_cityhall'),
(601,'place_cloning'),
(618,'place_exotic_garden'),
(604,'place_faction_terminal'),
(614,'place_fountain'),
(607,'place_garage'),
(496,'place_hospital'),
(617,'place_large_garden'),
(616,'place_medium_garden'),
(535,'place_merchant_tent'),
(597,'place_shuttleport'),
(615,'place_small_garden'),
(613,'place_statue'),
(612,'place_streetlamp'),
(473,'place_theater'),
(190,'pointBlankArea1'),
(305,'pointBlankArea2'),
(191,'pointBlankSingle1'),
(300,'pointBlankSingle2'),
(464,'polearmActionHit1'),
(465,'polearmActionHit2'),
(459,'polearmArea1'),
(461,'polearmArea2'),
(178,'polearmHit1'),
(448,'polearmHit2'),
(451,'polearmHit3'),
(182,'polearmLegHit1'),
(458,'polearmLegHit2'),
(460,'polearmLegHit3'),
(125,'polearmLunge1'),
(136,'polearmLunge2'),
(188,'polearmSpinAttack1'),
(456,'polearmSpinAttack2'),
(185,'polearmStun1'),
(453,'polearmStun2'),
(462,'polearmSweep1'),
(463,'polearmSweep2'),
(368,'powerBoost'),
(117,'premium_auctions'),
(414,'private_1hand_ability_1'),
(416,'private_1hand_ability_2'),
(417,'private_1hand_ability_3'),
(419,'private_1hand_ability_4'),
(400,'private_1hand_accuracy_1'),
(402,'private_1hand_accuracy_2'),
(403,'private_1hand_accuracy_3'),
(405,'private_1hand_accuracy_4'),
(398,'private_1hand_master'),
(395,'private_1hand_novice'),
(407,'private_1hand_speed_1'),
(409,'private_1hand_speed_2'),
(410,'private_1hand_speed_3'),
(412,'private_1hand_speed_4'),
(420,'private_1hand_support_1'),
(422,'private_1hand_support_2'),
(423,'private_1hand_support_3'),
(425,'private_1hand_support_4'),
(431,'private_2hand_accuracy_1'),
(433,'private_2hand_accuracy_2'),
(435,'private_2hand_accuracy_3'),
(436,'private_2hand_accuracy_4'),
(429,'private_2hand_master'),
(426,'private_2hand_novice'),
(438,'private_2hand_speed_1'),
(440,'private_2hand_speed_2'),
(114,'private_artisan_business_1'),
(116,'private_artisan_business_2'),
(118,'private_artisan_business_3'),
(119,'private_artisan_business_4'),
(110,'private_artisan_domestic_1'),
(111,'private_artisan_domestic_2'),
(112,'private_artisan_domestic_3'),
(113,'private_artisan_domestic_4'),
(106,'private_artisan_engineering_1'),
(107,'private_artisan_engineering_2'),
(108,'private_artisan_engineering_3'),
(109,'private_artisan_engineering_4'),
(104,'private_artisan_master'),
(101,'private_artisan_novice'),
(120,'private_artisan_survey_1'),
(121,'private_artisan_survey_2'),
(122,'private_artisan_survey_3'),
(123,'private_artisan_survey_4'),
(151,'private_brawler_1hand_1'),
(156,'private_brawler_1hand_2'),
(159,'private_brawler_1hand_3'),
(162,'private_brawler_1hand_4'),
(165,'private_brawler_2hand_1'),
(168,'private_brawler_2hand_2'),
(171,'private_brawler_2hand_3'),
(174,'private_brawler_2hand_4'),
(135,'private_brawler_master'),
(124,'private_brawler_novice'),
(177,'private_brawler_polearm_1'),
(181,'private_brawler_polearm_2'),
(184,'private_brawler_polearm_3'),
(187,'private_brawler_polearm_4'),
(143,'private_brawler_unarmed_1'),
(145,'private_brawler_unarmed_2'),
(147,'private_brawler_unarmed_3'),
(149,'private_brawler_unarmed_4'),
(344,'private_carbine_ability_1'),
(346,'private_carbine_ability_2'),
(347,'private_carbine_ability_3'),
(349,'private_carbine_ability_4'),
(330,'private_carbine_accuracy_1'),
(332,'private_carbine_accuracy_2'),
(334,'private_carbine_accuracy_3'),
(336,'private_carbine_accuracy_4'),
(329,'private_carbine_master'),
(324,'private_carbine_novice'),
(338,'private_carbine_speed_1'),
(340,'private_carbine_speed_2'),
(341,'private_carbine_speed_3'),
(343,'private_carbine_speed_4'),
(351,'private_carbine_support_1'),
(353,'private_carbine_support_2'),
(355,'private_carbine_support_3'),
(357,'private_carbine_support_4'),
(41,'private_entertainer_dance_1'),
(43,'private_entertainer_dance_2'),
(45,'private_entertainer_dance_3'),
(47,'private_entertainer_dance_4'),
(26,'private_entertainer_hair_1'),
(27,'private_entertainer_hair_2'),
(28,'private_entertainer_hair_3'),
(29,'private_entertainer_hair_4'),
(49,'private_entertainer_healing_1'),
(50,'private_entertainer_healing_2'),
(51,'private_entertainer_healing_3'),
(52,'private_entertainer_healing_4'),
(21,'private_entertainer_master'),
(30,'private_entertainer_music_1'),
(33,'private_entertainer_music_2'),
(35,'private_entertainer_music_3'),
(38,'private_entertainer_music_4'),
(1,'private_entertainer_novice'),
(875,'private_imperial_navy_droid_1'),
(882,'private_imperial_navy_droid_2'),
(887,'private_imperial_navy_droid_3'),
(892,'private_imperial_navy_droid_4'),
(856,'private_imperial_navy_master'),
(854,'private_imperial_navy_novice'),
(860,'private_imperial_navy_starships_1'),
(862,'private_imperial_navy_starships_2'),
(864,'private_imperial_navy_starships_3'),
(867,'private_imperial_navy_starships_4'),
(232,'private_marksman_carbine_1'),
(235,'private_marksman_carbine_2'),
(238,'private_marksman_carbine_3'),
(241,'private_marksman_carbine_4'),
(196,'private_marksman_master'),
(189,'private_marksman_novice'),
(213,'private_marksman_pistol_1'),
(217,'private_marksman_pistol_2'),
(223,'private_marksman_pistol_3'),
(227,'private_marksman_pistol_4'),
(198,'private_marksman_rifle_1'),
(202,'private_marksman_rifle_2'),
(206,'private_marksman_rifle_3'),
(209,'private_marksman_rifle_4'),
(245,'private_marksman_support_1'),
(248,'private_marksman_support_2'),
(252,'private_marksman_support_3'),
(254,'private_marksman_support_4'),
(93,'private_medic_ability_1'),
(94,'private_medic_ability_2'),
(95,'private_medic_ability_3'),
(96,'private_medic_ability_4'),
(97,'private_medic_crafting_1'),
(98,'private_medic_crafting_2'),
(99,'private_medic_crafting_3'),
(100,'private_medic_crafting_4'),
(82,'private_medic_injury_1'),
(83,'private_medic_injury_2'),
(85,'private_medic_injury_3'),
(86,'private_medic_injury_4'),
(81,'private_medic_master'),
(74,'private_medic_novice'),
(88,'private_medic_speed_1'),
(89,'private_medic_speed_2'),
(91,'private_medic_speed_3'),
(92,'private_medic_speed_4'),
(917,'private_neutral_droid_1'),
(923,'private_neutral_droid_2'),
(927,'private_neutral_droid_3'),
(931,'private_neutral_droid_4'),
(899,'private_neutral_master'),
(897,'private_neutral_novice'),
(904,'private_neutral_starships_1'),
(906,'private_neutral_starships_2'),
(909,'private_neutral_starships_3'),
(911,'private_neutral_starships_4'),
(310,'private_pistol_ability_1'),
(312,'private_pistol_ability_2'),
(314,'private_pistol_ability_3'),
(316,'private_pistol_ability_4'),
(299,'private_pistol_accuracy_1'),
(301,'private_pistol_accuracy_2'),
(302,'private_pistol_accuracy_3'),
(304,'private_pistol_accuracy_4'),
(318,'private_pistol_defense_1'),
(320,'private_pistol_defense_2'),
(321,'private_pistol_defense_3'),
(323,'private_pistol_defense_4'),
(296,'private_pistol_master'),
(292,'private_pistol_novice'),
(306,'private_pistol_speed_1'),
(307,'private_pistol_speed_2'),
(308,'private_pistol_speed_3'),
(309,'private_pistol_speed_4'),
(452,'private_polearm_accuracy_1'),
(454,'private_polearm_accuracy_2'),
(455,'private_polearm_accuracy_3'),
(457,'private_polearm_accuracy_4'),
(450,'private_polearm_master'),
(447,'private_polearm_novice'),
(827,'private_rebel_navy_droid_1'),
(834,'private_rebel_navy_droid_2'),
(840,'private_rebel_navy_droid_3'),
(846,'private_rebel_navy_droid_4'),
(795,'private_rebel_navy_master'),
(790,'private_rebel_navy_novice'),
(804,'private_rebel_navy_starships_1'),
(806,'private_rebel_navy_starships_2'),
(808,'private_rebel_navy_starships_3'),
(810,'private_rebel_navy_starships_4'),
(278,'private_rifle_ability_1'),
(280,'private_rifle_ability_2'),
(282,'private_rifle_ability_3'),
(284,'private_rifle_ability_4'),
(262,'private_rifle_accuracy_1'),
(264,'private_rifle_accuracy_2'),
(266,'private_rifle_accuracy_3'),
(268,'private_rifle_accuracy_4'),
(259,'private_rifle_master'),
(256,'private_rifle_novice'),
(270,'private_rifle_speed_1'),
(273,'private_rifle_speed_2'),
(274,'private_rifle_speed_3'),
(277,'private_rifle_speed_4'),
(286,'private_rifle_support_1'),
(288,'private_rifle_support_2'),
(289,'private_rifle_support_3'),
(291,'private_rifle_support_4'),
(69,'private_scout_camp_1'),
(71,'private_scout_camp_2'),
(72,'private_scout_camp_3'),
(73,'private_scout_camp_4'),
(65,'private_scout_harvest_1'),
(66,'private_scout_harvest_2'),
(67,'private_scout_harvest_3'),
(68,'private_scout_harvest_4'),
(55,'private_scout_master'),
(56,'private_scout_movement_1'),
(57,'private_scout_movement_2'),
(59,'private_scout_movement_3'),
(60,'private_scout_movement_4'),
(53,'private_scout_novice'),
(61,'private_scout_tools_1'),
(62,'private_scout_tools_2'),
(63,'private_scout_tools_3'),
(64,'private_scout_tools_4'),
(786,'private_shipwright_defense_1'),
(787,'private_shipwright_defense_2'),
(788,'private_shipwright_defense_3'),
(789,'private_shipwright_defense_4'),
(774,'private_shipwright_engineering_1'),
(775,'private_shipwright_engineering_2'),
(776,'private_shipwright_engineering_3'),
(777,'private_shipwright_engineering_4'),
(773,'private_shipwright_master'),
(772,'private_shipwright_novice'),
(778,'private_shipwright_propulsion_1'),
(779,'private_shipwright_propulsion_2'),
(780,'private_shipwright_propulsion_3'),
(781,'private_shipwright_propulsion_4'),
(782,'private_shipwright_systems_1'),
(783,'private_shipwright_systems_2'),
(784,'private_shipwright_systems_3'),
(785,'private_shipwright_systems_4'),
(380,'private_unarmed_ability_1'),
(382,'private_unarmed_ability_2'),
(384,'private_unarmed_ability_3'),
(386,'private_unarmed_ability_4'),
(366,'private_unarmed_accuarcy_1'),
(367,'private_unarmed_accuarcy_2'),
(369,'private_unarmed_accuracy_3'),
(370,'private_unarmed_accuracy_4'),
(363,'private_unarmed_master'),
(359,'private_unarmed_novice'),
(372,'private_unarmed_speed_1'),
(375,'private_unarmed_speed_2'),
(376,'private_unarmed_speed_3'),
(378,'private_unarmed_speed_4'),
(388,'private_unarmed_support_1'),
(390,'private_unarmed_support_2'),
(392,'private_unarmed_support_3'),
(393,'private_unarmed_support_4'),
(914,'ptrap1'),
(901,'ptrap2'),
(870,'pumpreactor'),
(87,'quickHeal'),
(590,'rally'),
(272,'ranged_damage_mitigation_1'),
(276,'ranged_damage_mitigation_2'),
(261,'ranged_damage_mitigation_3'),
(606,'recruitSkillTrainer'),
(752,'regainConsciousness'),
(637,'regeneration'),
(468,'registerWithLocation'),
(509,'rescue'),
(591,'retreat'),
(501,'revivePlayer'),
(218,'rollShot'),
(652,'saber1hComboHit1'),
(647,'saber1hComboHit2'),
(736,'saber1hComboHit3'),
(650,'saber1hFlurry'),
(727,'saber1hFlurry2'),
(653,'saber1hHeadHit1'),
(648,'saber1hHeadHit2'),
(734,'saber1hHeadHit3'),
(651,'saber1hHit1'),
(654,'saber1hHit2'),
(735,'saber1hHit3'),
(677,'saber2hBodyHit1'),
(675,'saber2hBodyHit2'),
(739,'saber2hBodyHit3'),
(674,'saber2hFrenzy'),
(668,'saber2hHit1'),
(679,'saber2hHit2'),
(673,'saber2hHit3'),
(728,'saber2hPhantom'),
(678,'saber2hSweep1'),
(680,'saber2hSweep2'),
(740,'saber2hSweep3'),
(708,'saberPolearmDervish'),
(729,'saberPolearmDervish2'),
(704,'saberPolearmHit1'),
(711,'saberPolearmHit2'),
(744,'saberPolearmHit3'),
(710,'saberPolearmLegHit1'),
(712,'saberPolearmLegHit2'),
(743,'saberPolearmLegHit3'),
(706,'saberPolearmSpinAttack1'),
(713,'saberPolearmSpinAttack2'),
(745,'saberPolearmSpinAttack3'),
(643,'saberSlash1'),
(646,'saberSlash2'),
(669,'saberThrow1'),
(676,'saberThrow2'),
(726,'saberThrow3'),
(102,'sample'),
(530,'sampleDNA'),
(331,'scatterShot1'),
(335,'scatterShot2'),
(539,'slice_armor'),
(536,'slice_containers'),
(537,'slice_terminals'),
(540,'slice_weaponsadvanced'),
(538,'slice_weaponsbasic'),
(20,'slitherhorn'),
(478,'smokebomb'),
(275,'sneak'),
(269,'sniperShot'),
(642,'space_navigator'),
(474,'spotlight'),
(547,'sprayShot'),
(5,'startdance'),
(17,'startdance+basic'),
(42,'startdance+basic2'),
(948,'startdance+breakdance'),
(949,'startdance+breakdance2'),
(482,'startdance+exotic'),
(483,'startdance+exotic2'),
(470,'startdance+exotic3'),
(471,'startdance+exotic4'),
(46,'startdance+footloose'),
(22,'startdance+footloose2'),
(48,'startdance+formal'),
(23,'startdance+formal2'),
(481,'startdance+lyrical'),
(469,'startdance+lyrical2'),
(467,'startdance+poplock'),
(480,'startdance+poplock2'),
(466,'startdance+popular'),
(479,'startdance+popular2'),
(18,'startdance+rhythmic'),
(44,'startdance+rhythmic2'),
(946,'startdance+tumble'),
(947,'startdance+tumble2'),
(281,'startleShot1'),
(285,'startleShot2'),
(7,'startMusic'),
(489,'startmusic+ballad'),
(24,'startmusic+ceremonial'),
(36,'startmusic+folk'),
(944,'startmusic+funk'),
(493,'startmusic+jazz'),
(31,'startmusic+rock'),
(19,'startmusic+starwars1'),
(34,'startmusic+starwars2'),
(39,'startmusic+starwars3'),
(945,'startmusic+starwars4'),
(485,'startmusic+virtuoso'),
(491,'startmusic+waltz'),
(586,'steadyaim'),
(701,'stopBleeding'),
(6,'stopDance'),
(8,'stopMusic'),
(315,'stoppingShot'),
(257,'strafeShot1'),
(260,'strafeShot2'),
(255,'suppressionFire1'),
(350,'suppressionFire2'),
(267,'surpriseShot'),
(103,'survey'),
(585,'sysgroup'),
(203,'takeCover'),
(513,'tame'),
(129,'taunt'),
(79,'tendDamage'),
(78,'tendWound'),
(246,'threatenShot'),
(557,'torsoShot'),
(707,'totalHealOther'),
(717,'totalHealSelf'),
(529,'train_mount'),
(764,'transferForce'),
(484,'traz'),
(522,'trick1'),
(524,'trick2'),
(250,'tumbleToKneeling'),
(249,'tumbleToProne'),
(251,'tumbleToStanding'),
(148,'unarmedBlind1'),
(389,'unarmedBodyHit1'),
(383,'unarmedCombo1'),
(387,'unarmedCombo2'),
(381,'unarmedDizzy1'),
(394,'unarmedHeadHit1'),
(144,'unarmedHit1'),
(360,'unarmedHit2'),
(364,'unarmedHit3'),
(373,'unarmedKnockdown1'),
(379,'unarmedKnockdown2'),
(391,'unarmedLegHit1'),
(126,'unarmedLunge1'),
(137,'unarmedLunge2'),
(150,'unarmedSpinAttack1'),
(385,'unarmedSpinAttack2'),
(146,'unarmedStun1'),
(552,'underHandShot'),
(531,'vendor_fees_1'),
(488,'ventriloquism'),
(640,'vitalize'),
(587,'volleyFire'),
(822,'vrepair'),
(826,'vrepairother'),
(130,'warcry1'),
(140,'warcry2'),
(253,'warningShot'),
(333,'wildShot1'),
(337,'wildShot2'),
(638,'wookieeRoar');
/*!40000 ALTER TABLE `skillcommands` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2012-08-27  9:42:10