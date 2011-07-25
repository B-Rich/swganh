/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
 
#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/thread.hpp>

#include <glog/logging.h>

#include "anh/app/kernel_interface.h"
#include "anh/plugin/bindings.h"
#include "anh/plugin/plugin_manager.h"
#include "anh/service/service_manager.h"

#include "swganh/character/base_character_service.h"
#include "login/login_service.h"

#include "connection/connection_service.h"

using namespace anh;
using namespace app;
using namespace event_dispatcher;
using namespace connection;
using namespace plugin;
using namespace swganh::character;
using namespace std;
using boost::program_options::options_description;
using boost::program_options::variables_map;

extern "C" PLUGIN_API void ExitModule() {
    return;
}

extern "C" PLUGIN_API ExitFunc InitializePlugin(shared_ptr<KernelInterface> kernel) {

    ObjectRegistration registration;
    registration.version.major = 1;
    registration.version.minor = 0;

    // Register TestObj
    registration.CreateObject = [] (ObjectParams* params) -> void * {
        auto character_service = std::static_pointer_cast<BaseCharacterService>(params->kernel->GetServiceManager()->GetService("CharacterService"));
        auto login_service = std::static_pointer_cast<login::LoginService>(params->kernel->GetServiceManager()->GetService("LoginService"));

        auto connection_service = new ConnectionService(params->kernel);
        connection_service->character_service(character_service);
        connection_service->login_service(login_service);
        return connection_service;
    };

    registration.DestroyObject = [] (void * object) {
        if (object) {
            delete object;
        }
    };

    kernel->GetPluginManager()->RegisterObject("ConnectionService", &registration);

    return ExitModule;
}
