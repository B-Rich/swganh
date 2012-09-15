// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "mysql_session_provider.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>

#include "swganh/logger.h"

#include "swganh/database/database_manager.h"


using namespace swganh::connection;
using namespace swganh::login;
using namespace std;

MysqlSessionProvider::MysqlSessionProvider(swganh::database::DatabaseManagerInterface* db_manager)
    : SessionProviderInterface()
    , db_manager_(db_manager) {}

MysqlSessionProvider::~MysqlSessionProvider() {}

uint64_t MysqlSessionProvider::GetPlayerId(uint32_t account_id) {

	// TODO: Cleanup
   /* try {
        string sql = "select id from player_account where reference_id = ?";
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt(1, account_id);
        auto result_set = unique_ptr<sql::ResultSet>(statement->executeQuery());
        
        if (result_set->next()) {
            player_id = result_set->getUInt64("id");
            
        } else {
            LOG(warning) << "No Player Id found for account_id: " << account_id << endl;
        }

    } catch(sql::SQLException &e) {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }*/

    return account_id;
}

bool MysqlSessionProvider::CreateGameSession(uint64_t account_id, uint32_t session_id) {
    // create new game session 
    std::string game_session = boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::local_time())
        + boost::lexical_cast<std::string>(session_id);

    try {
        string sql = "CALL sp_CreateSession(?,?,?);";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, account_id);
        statement->setString(2, game_session);
		statement->setInt(3, 2);
        statement->execute();
        while (statement->getMoreResults());
	} catch(sql::SQLException &e) {
		LOG(warning) << "Couldn't create session for player " << account_id << endl;
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
    return true;
}
void MysqlSessionProvider::EndGameSession(uint64_t player_id)
{
	try {
        string sql = "CALL sp_RemoveAccountSessionsByID(?);";
        auto conn = db_manager_->getConnection("galaxy_manager");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, player_id);
        statement->execute();        

    } catch(sql::SQLException &e) {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
uint32_t MysqlSessionProvider::GetAccountId(uint64_t player_id) {
	return static_cast<uint32_t>(player_id);
	// TODO: Fix up
    /*uint32_t account_id = 0;

    try {
        string sql = "select reference_id from player_account where id = ?";
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement(sql));
        statement->setUInt64(1, player_id);
        auto result_set = unique_ptr<sql::ResultSet>(statement->executeQuery());
        
        if (result_set->next()) {
            account_id = result_set->getUInt("reference_id");
            
        } else {
            LOG(warning) << "No account Id found for player id : " << player_id << endl;
        }

    } catch(sql::SQLException &e) {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
    return account_id;*/
}