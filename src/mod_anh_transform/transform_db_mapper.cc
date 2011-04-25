/*
 This file is part of MMOServer. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 MMOServer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMOServer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMOServer.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "transform_db_mapper.h"
#include <anh/database/database_manager_interface.h>

namespace transform {

TransformDBMapper::TransformDBMapper(std::shared_ptr<anh::database::DatabaseManagerInterface> db_manager)
	: BaseDBMapper(db_manager)
{

}
void TransformDBMapper::persist()
{
	std::stringstream query_stream;
	query_stream << "UPDATE ";
}
std::shared_ptr<sql::ResultSet> TransformDBMapper::query_result()
{
	auto query_result = std::make_shared<sql::ResultSet>();
	return query_result;
}

} // transform