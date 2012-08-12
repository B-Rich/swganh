// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "object_factory.h"


#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include "anh/logger.h"

#include "anh/database/database_manager.h"
#include "swganh/object/object.h"
#include "swganh/object/object_manager.h"
#include "swganh/object/exception.h"
#include "swganh/simulation/simulation_service_interface.h"

using namespace sql;
using namespace std;
using namespace anh::database;
using namespace swganh::object;
using namespace swganh::simulation;

ObjectFactory::ObjectFactory(DatabaseManagerInterface* db_manager,
                             anh::EventDispatcher* event_dispatcher)
    : db_manager_(db_manager)
    , event_dispatcher_(event_dispatcher)
{}

void ObjectFactory::PersistObject(const shared_ptr<Object>& object)
{
    try {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>
            (conn->prepareStatement("CALL sp_PersistObject(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);"));
        PersistObject(object, statement);
        // Now execute the update
        statement->executeUpdate();
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

void ObjectFactory::PersistObject(const shared_ptr<Object>& object, const shared_ptr<sql::PreparedStatement>& prepared_statement)
{
    try {
        prepared_statement->setUInt64(1, object->GetObjectId());
		if (object->GetContainer() != nullptr)
		{
			prepared_statement->setUInt(2, object->GetSceneId());
			prepared_statement->setUInt64(3, object->GetContainer()->GetObjectId());
		}
        else
		{
			prepared_statement->setUInt(2, object->GetSceneId());
            prepared_statement->setUInt64(3, 0);
		}
        prepared_statement->setString(4, object->GetTemplate());
        auto position = object->GetPosition();
        prepared_statement->setDouble(5, position.x);
        prepared_statement->setDouble(6, position.y);
        prepared_statement->setDouble(7, position.z);
        auto orientation = object->GetOrientation();
        prepared_statement->setDouble(8, orientation.x);
        prepared_statement->setDouble(9, orientation.y);
        prepared_statement->setDouble(10, orientation.z);
        prepared_statement->setDouble(11, orientation.w);
        prepared_statement->setDouble(12, object->GetComplexity());
        prepared_statement->setString(13, object->GetStfNameFile());
        prepared_statement->setString(14, object->GetStfNameString());
        auto custom_name = object->GetCustomName();
        prepared_statement->setString(15, string(begin(custom_name), end(custom_name)));
        prepared_statement->setUInt(16, object->GetVolume());
		prepared_statement->setInt(17, object->GetArrangementId());

    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
void ObjectFactory::CreateBaseObjectFromStorage(const shared_ptr<Object>& object, const shared_ptr<sql::ResultSet>& result)
{
    try {
        result->next();
        // Set Event Dispatcher
        object->SetEventDispatcher(event_dispatcher_);
        object->SetSceneId(result->getUInt("scene_id"));
        object->SetPosition(glm::vec3(result->getDouble("x_position"),result->getDouble("y_position"), result->getDouble("z_position")));
        object->SetOrientation(glm::quat(
            static_cast<float>(result->getDouble("x_orientation")),
            static_cast<float>(result->getDouble("y_orientation")),
            static_cast<float>(result->getDouble("z_orientation")), 
            static_cast<float>(result->getDouble("w_orientation")))
            );

        object->SetComplexity(static_cast<float>(result->getDouble("complexity")));
        object->SetStfName(result->getString("stf_name_file"),
                           result->getString("stf_name_string"));
        string custom_string = result->getString("custom_name");
        object->SetCustomName(wstring(begin(custom_string), end(custom_string)));
        object->SetVolume(result->getUInt("volume"));
        object->SetTemplate(result->getString("iff_template"));
		object->SetArrangementId(result->getInt("arrangement_id"));

		object_manager_->LoadSlotsForObject(object);
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}

uint32_t ObjectFactory::LookupType(uint64_t object_id) const
{
    uint32_t type = 0;
    try {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = conn->prepareStatement("CALL sp_GetType(?);");
        statement->setUInt64(1, object_id);
        auto result = unique_ptr<sql::ResultSet>(statement->executeQuery());        
        while (result->next())
        {
            type = result->getUInt("description");
        }
        return type;
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
        return type;
    }
}

void ObjectFactory::LoadContainedObjects(
    const shared_ptr<Object>& object,
    const shared_ptr<Statement>& statement)
{
    // Check for contained objects        
    if (statement->getMoreResults())
    {
        unique_ptr<ResultSet> result(statement->getResultSet());

        uint64_t contained_id;
        uint32_t contained_type;

        while (result->next())
        {
            contained_id = result->getUInt64("id");
            contained_type = result->getUInt("type_id");

            auto contained_object = object_manager_->CreateObjectFromStorage(contained_id, contained_type);

			if(contained_object->GetArrangementId() == -2)
			{
				//This object has never been loaded before and needs to be put into the default slot.
				object->AddObject(contained_object);
			}
			else 
			{
				//Put it back where it was persisted
				object->AddObject(contained_object, contained_object->GetArrangementId());
			}

        }
    }
}
