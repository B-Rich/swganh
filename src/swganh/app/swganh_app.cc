// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef WIN32
#include <Python.h>
#endif

#include "swganh/app/swganh_app.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

#ifdef WIN32
#include <regex>
#else
#include <boost/regex.hpp>
#endif

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>

#include "anh/logger.h"
#include "anh/database/database_manager_interface.h"
#include "anh/event_dispatcher.h"
#include "anh/plugin/plugin_manager.h"
#include "anh/service/datastore.h"
#include "anh/service/service_manager.h"

#include "swganh/app/swganh_kernel.h"

#include "swganh/chat/chat_service.h"
#include "swganh/character/character_service.h"
#include "swganh/connection/connection_service.h"
#include "swganh/login/login_service.h"
#include "swganh/simulation/simulation_service.h"
#include "swganh/galaxy/galaxy_service.h"
#include "swganh/combat/combat_service.h"
#include "swganh/social/social_service.h"
#include "swganh/scripting/utilities.h"

using namespace anh;
using namespace anh::app;
using namespace boost::asio;
using namespace boost::program_options;
using namespace std;
using namespace swganh::app;
using namespace swganh::chat;
using namespace swganh::command;
using namespace swganh::login;
using namespace swganh::character;
using namespace swganh::connection;
using namespace swganh::combat;
using namespace swganh::simulation;
using namespace swganh::galaxy;

using anh::plugin::RegistrationMap;

#ifdef WIN32
using std::regex;
using std::smatch;
using std::regex_match;
#else
using boost::regex;
using boost::smatch;
using boost::regex_match;
#endif


options_description AppConfig::BuildConfigDescription() {
    options_description desc;

    desc.add_options()
        ("help,h", "Display help message and config options")

		("server_mode", boost::program_options::value<std::string>(&server_mode)->default_value("all"),
			"Specifies the service configuration mode to run the server in.")

        ("plugin,p", boost::program_options::value<std::vector<std::string>>(&plugins),
            "Only used when single_server_mode is disabled, loads a module of the specified name")
        ("plugin_directory", value<string>(&plugin_directory)->default_value("plugins/"),
            "Directory containing the application plugins")

        ("script_directory", value<string>(&script_directory)->default_value("scripts"),
            "Directory containing the application scripts")

        ("tre_config", boost::program_options::value<std::string>(&tre_config),
            "File containing the tre configuration (live.cfg)")

        ("galaxy_name", boost::program_options::value<std::string>(&galaxy_name),
            "Name of the galaxy (cluster) to this process should run")

        ("db.galaxy_manager.host", boost::program_options::value<std::string>(&galaxy_manager_db.host),
            "Host address for the galaxy_manager datastore")
        ("db.galaxy_manager.schema", boost::program_options::value<std::string>(&galaxy_manager_db.schema),
            "Schema name for the galaxy_manager datastore")
        ("db.galaxy_manager.username", boost::program_options::value<std::string>(&galaxy_manager_db.username),
            "Username for authentication with the galaxy_manager datastore")
        ("db.galaxy_manager.password", boost::program_options::value<std::string>(&galaxy_manager_db.password),
            "Password for authentication with the galaxy_manager datastore")

        ("db.galaxy.host", boost::program_options::value<std::string>(&galaxy_db.host),
            "Host address for the galaxy datastore")
        ("db.galaxy.schema", boost::program_options::value<std::string>(&galaxy_db.schema),
            "Schema name for the galaxy datastore")
        ("db.galaxy.username", boost::program_options::value<std::string>(&galaxy_db.username),
            "Username for authentication with the galaxy datastore")
        ("db.galaxy.password", boost::program_options::value<std::string>(&galaxy_db.password),
            "Password for authentication with the galaxy datastore")
            
        ("service.login.udp_port", 
            boost::program_options::value<uint16_t>(&login_config.listen_port),
            "The port the login service will listen for incoming client connections on")
        ("service.login.address", 
            boost::program_options::value<string>(&login_config.listen_address),
            "The public address the login service will listen for incoming client connections on")
        ("service.login.status_check_duration_secs", 
            boost::program_options::value<int>(&login_config.galaxy_status_check_duration_secs),
            "The amount of time between checks for updated galaxy status")
        ("service.login.login_error_timeout_secs", 
            boost::program_options::value<int>(&login_config.login_error_timeout_secs)->default_value(5),
            "The number of seconds to wait before disconnecting a client after failed login attempt")
        ("service.login.auto_registration",
            boost::program_options::value<bool>(&login_config.login_auto_registration)->default_value(false),
            "Auto Registration flag")
            
        ("service.connection.ping_port", boost::program_options::value<uint16_t>(&connection_config.ping_port),
            "The port the connection service will listen for incoming client ping requests on")
        ("service.connection.udp_port", boost::program_options::value<uint16_t>(&connection_config.listen_port),
            "The port the connection service will listen for incoming client connections on")
        ("service.connection.address", boost::program_options::value<string>(&connection_config.listen_address),
            "The public address the connection service will listen for incoming client connections on")
    ;

    return desc;
}

SwganhApp::SwganhApp(int argc, char* argv[])
    : io_service_()
    , io_work_(new boost::asio::io_service::work(io_service_))
{
    kernel_ = make_shared<SwganhKernel>(io_service_);
    running_ = false;
    initialized_ = false;

    Initialize(argc, argv);
    Start();
}

SwganhApp::~SwganhApp() 
{
    Stop();

    kernel_.reset();
    io_work_.reset();
    
    // join the threadpool threads until each one has exited.
    for_each(io_threads_.begin(), io_threads_.end(), std::mem_fn(&boost::thread::join));
}

void SwganhApp::Initialize(int argc, char* argv[]) {
    // Init Logging
    SetupLogging_();
    
    // Load the configuration    
    LoadAppConfig_(argc, argv);

    auto app_config = kernel_->GetAppConfig();

    // Initialize kernel resources    
    kernel_->GetDatabaseManager()->registerStorageType(
        "galaxy_manager",
        app_config.galaxy_manager_db.schema,
        app_config.galaxy_manager_db.host,
        app_config.galaxy_manager_db.username,
        app_config.galaxy_manager_db.password);

    kernel_->GetDatabaseManager()->registerStorageType(
        "galaxy",
        app_config.galaxy_db.schema,
        app_config.galaxy_db.host,
        app_config.galaxy_db.username,
        app_config.galaxy_db.password);
    
    CleanupServices_();
    
    // append command dir
    std::string py_path = "import sys; sys.path.append('.'); sys.path.append('" + app_config.script_directory + "');";
    {
        swganh::scripting::ScopedGilLock lock;
        PyRun_SimpleString(py_path.c_str());
    }

    // Load the plugin configuration.
    LoadPlugins_(app_config.plugins);

    // Load core services
    LoadCoreServices_();
    
    initialized_ = true;
}

void SwganhApp::Start() {
    if (!initialized_) {
        throw std::runtime_error("Called application Start before Initialize");
    }

    running_ = true;

    // Start up a threadpool for running io_service based tasks/active objects
    // The increment starts at 2 because the main thread of execution already counts
    // as thread in use as does the console thread.
    for (uint32_t i = 1; i < boost::thread::hardware_concurrency(); ++i) {
        boost::thread t([this] () {
            io_service_.run();
        });
        
#ifdef _WIN32
        SetPriorityClass(t.native_handle(), REALTIME_PRIORITY_CLASS);
#endif

        io_threads_.push_back(move(t));
    }
    
    kernel_->GetServiceManager()->Start();
}

void SwganhApp::Stop() {
    running_ = false;
}

bool SwganhApp::IsRunning() {
    return running_;
}

SwganhKernel* SwganhApp::GetAppKernel() const {
    return kernel_.get();
}

void SwganhApp::LoadAppConfig_(int argc, char* argv[]) {
    auto config_description = kernel_->GetAppConfig().BuildConfigDescription();

    variables_map vm;
    store(parse_command_line(argc, argv, config_description), vm);

    ifstream config_file("config/swganh.cfg");

    if (!config_file.is_open()) {
        throw runtime_error("Unable to open the configuration file at: config/swganh.cfg");
    }

    try {
        store(parse_config_file(config_file, config_description, true), vm);
    } catch(...) {
        throw runtime_error("Unable to parse the configuration file at: config/swganh.cfg");
    }

    notify(vm);
    config_file.close();

    if (vm.count("help")) {
        std::cout << config_description << "\n\n";
        exit(0);
    }
}

void SwganhApp::LoadPlugins_(vector<string> plugins) {    
    LOG(info) << "Loading plugins";

    if (!plugins.empty()) {
        auto plugin_manager = kernel_->GetPluginManager();
        auto plugin_directory = kernel_->GetAppConfig().plugin_directory;

        for_each(plugins.begin(), plugins.end(), [plugin_manager, plugin_directory] (const string& plugin) {
            plugin_manager->LoadPlugin(plugin, plugin_directory);
        });
    }
}

void SwganhApp::CleanupServices_() {

    auto service_directory = kernel_->GetServiceDirectory();

    auto services = service_directory->getServiceSnapshot(service_directory->galaxy());

    if (services.empty()) {
        return;
    }

    LOG(warning) << "Services were not shutdown properly";

    for_each(services.begin(), services.end(), [this, &service_directory] (anh::service::ServiceDescription& service) {
        service_directory->removeService(service);
    });
}

void SwganhApp::LoadCoreServices_() 
{
    
    auto plugin_manager = kernel_->GetPluginManager();
    auto registration_map = plugin_manager->registration_map();

    regex rx("(?:.*\\:\\:)(.*Service)");
    smatch m;
    
    for_each(registration_map.begin(), registration_map.end(), [this, &rx, &m] (RegistrationMap::value_type& entry) {
        std::string name = entry.first;

        if (entry.first.length() > 7 && regex_match(name, m, rx)) {
            auto service_name = m[1].str();

            auto service = kernel_->GetPluginManager()->CreateObject<anh::service::ServiceInterface>(name);

            kernel_->GetServiceManager()->AddService(service_name, service);
        }
    });

    auto app_config = kernel_->GetAppConfig();

	if(strcmp("login", app_config.server_mode.c_str()) == 0 || strcmp("all", app_config.server_mode.c_str()) == 0)
	{
        auto login_service = std::make_shared<LoginService>(
		    app_config.login_config.listen_address, 
		    app_config.login_config.listen_port, 
		    kernel_.get());

		login_service->galaxy_status_check_duration_secs(app_config.login_config.galaxy_status_check_duration_secs);
		login_service->login_error_timeout_secs(app_config.login_config.login_error_timeout_secs);
        login_service->login_auto_registration(app_config.login_config.login_auto_registration);
    
		kernel_->GetServiceManager()->AddService("LoginService", login_service);
	}

	if(strcmp("connection", app_config.server_mode.c_str()) == 0 || strcmp("all", app_config.server_mode.c_str()) == 0)
	{
		auto connection_service = std::make_shared<ConnectionService>(
			app_config.connection_config.listen_address, 
			app_config.connection_config.listen_port, 
			app_config.connection_config.ping_port, 
			kernel_.get());
    
		kernel_->GetServiceManager()->AddService("ConnectionService", connection_service);
	}

	if(strcmp("simulation", app_config.server_mode.c_str()) == 0 || strcmp("all", app_config.server_mode.c_str()) == 0)
	{
		// These will be loaded in alphabetical order because of how std::map generates its keys
		kernel_->GetServiceManager()->AddService(
			"CombatService",
			std::make_shared<CombatService>(kernel_.get()));
		
		kernel_->GetServiceManager()->AddService(
            "CharacterService", 
            std::make_shared<CharacterService>(kernel_.get()));
        
		kernel_->GetServiceManager()->AddService(
            "ChatService", 
            std::make_shared<ChatService>(kernel_.get()));
    
		auto simulation_service = std::make_shared<SimulationService>(kernel_.get());
		simulation_service->StartScene("corellia");
    
		kernel_->GetServiceManager()->AddService("SimulationService", simulation_service);
    
        kernel_->GetServiceManager()->AddService(
            "SocialService", 
            std::make_shared<social::SocialService>(kernel_.get()));
    
	}

	// always need a galaxy service running
	kernel_->GetServiceManager()->AddService("GalaxyService", 
        std::make_shared<GalaxyService>(kernel_.get()));
}

void SwganhApp::SetupLogging_()
{
    anh::Logger::getInstance().init("swganh");    
}