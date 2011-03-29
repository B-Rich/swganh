/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2010 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

#ifndef ANH_MODULE_MANAGER_WIN32_MODULE_H_
#define ANH_MODULE_MANAGER_WIN32_MODULE_H_
#ifdef WIN32

#include <Windows.h>
#include <anh/module_manager/module_interface.h>

namespace anh {
namespace module_manager {

class Win32Module : public ModuleInterface
{
public:
	Win32Module(void);
	~Win32Module(void);

	bool Load(const std::string& filename, std::shared_ptr<PlatformServices> services);
	void Unload(std::shared_ptr<PlatformServices> services);

	const std::string name(void) { return get_name_func_(); }
	const ModuleApiVersion version(void) { return get_version_func_(); }
	const std::string description(void) { return get_description_func_(); }

private:
	HMODULE					handle_;
	LoadFunc				load_func_;
	UnloadFunc				unload_func_;
	GetNameFunc				get_name_func_;
	GetVersionFunc			get_version_func_;
	GetDescriptionFunc		get_description_func_;
};

} // namespace module_manager
} // namespace anh

#endif
#endif