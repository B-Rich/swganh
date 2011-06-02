/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2011 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,a
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/
#ifndef ANH_MODULE_MANAGER_MODULE_MAIN_H
#define ANH_MODULE_MANAGER_MODULE_MAIN_H

#include <anh/component/entity_builder.h>
#include <anh/component/entity_manager.h>
#include <anh/event_dispatcher/event_dispatcher_interface.h>
#include <anh/database/database_manager_interface.h>
#include <anh/scripting/scripting_manager_interface.h>
#include <anh/server_directory/server_directory_interface.h>

#ifdef _WIN32
    #include <windows.h>
    #ifdef DLL_EXPORTS
        #define API __declspec(dllexport)
    #else
        #define API __declspec(dllimport)
    #endif
#else
    #define API 
#endif

#endif // ANH_MODULE_MANAGER_MODULE_MAIN_H
