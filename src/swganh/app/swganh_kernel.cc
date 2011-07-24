
#include "swganh/app/swganh_kernel.h"

#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/driver.h>

#include "anh/database/database_manager.h"
#include "anh/event_dispatcher/event_dispatcher.h"
#include "anh/plugin/plugin_manager.h"
#include "anh/service/service_manager.h"

#include "version.h"

using namespace swganh::app;

using anh::app::Version;
using anh::database::DatabaseManagerInterface;
using anh::database::DatabaseManager;
using anh::event_dispatcher::EventDispatcherInterface;
using anh::event_dispatcher::EventDispatcher;
using anh::plugin::PluginManager;
using anh::service::ServiceManager;

using std::make_shared;
using std::shared_ptr;

SwganhKernel::SwganhKernel() {
    version_.major = VERSION_MAJOR;
    version_.minor = VERSION_MINOR;

    event_dispatcher_ = nullptr;
    plugin_manager_ = nullptr;
    service_manager_ = nullptr;
}

const Version& SwganhKernel::GetVersion() {
    return version_;
}

AppConfig& SwganhKernel::GetAppConfig() {
    return app_config_;
}

shared_ptr<DatabaseManagerInterface> SwganhKernel::GetDatabaseManager() {
    if (!database_manager_) {
        database_manager_ = make_shared<DatabaseManager>(sql::mysql::get_driver_instance());
    }

    return database_manager_;
}

shared_ptr<EventDispatcherInterface> SwganhKernel::GetEventDispatcher() {
    if (!event_dispatcher_) {
        event_dispatcher_ = make_shared<EventDispatcher>();
    }

    return event_dispatcher_;
}

shared_ptr<PluginManager> SwganhKernel::GetPluginManager() {
    if (!plugin_manager_) {
        plugin_manager_ = make_shared<PluginManager>(shared_from_this());
    }

    return plugin_manager_;
}

shared_ptr<ServiceManager> SwganhKernel::GetServiceManager() {
    if (!service_manager_) {
        service_manager_ = make_shared<ServiceManager>(GetPluginManager());
    }

    return service_manager_;
}

boost::asio::io_service& SwganhKernel::GetIoService() {
    return io_service_;
}

