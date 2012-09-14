/* 
	This file is part of SWGANH which is released under the MIT license.
	See file LICENSE or go to http://swganh.com/LICENSE
*/

USE swganh_galaxy_manager;

DELIMITER $$

--
-- Definition for stored procedure `sp_AdminShowSchemaTables`
--

CREATE PROCEDURE `sp_AdminShowSchemaTables`( IN dbname CHAR(64) )
BEGIN
  SELECT
    table_name,
    engine,
    version,
    table_collation AS collation,
    table_rows AS rows
  FROM information_schema.tables
  WHERE table_schema = dbname;

END $$