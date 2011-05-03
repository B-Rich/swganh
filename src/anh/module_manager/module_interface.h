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

#ifndef ANH_MODULE_MANAGER_MODULE_H_
#define ANH_MODULE_MANAGER_MODULE_H_

#include <string>
#include <cstdint>
#include <anh/memory.h>

namespace anh {
namespace module_manager {

// FORWARD DELCARES
class PlatformServices;

/**
 *
 */
typedef struct ModuleApiVersion
{
	ModuleApiVersion(uint32_t major_ver_ = 0, uint32_t minor_ver_ = 0, std::string version_string_ ="0.0")
		: major_ver(major_ver_)
		, minor_ver(minor_ver_)
		, version_string(version_string_) { }

	~ModuleApiVersion(void) { }

	bool operator ==(const ModuleApiVersion& other)
	{
		if((major_ver == other.major_ver) && (minor_ver == other.minor_ver))
			return true;
		else
			return false;
	}
	bool operator !=(const ModuleApiVersion& other)
	{
		if((major_ver != other.major_ver) || (minor_ver != other.minor_ver))
			return true;
		else
			return false;
	}

	uint32_t major_ver;
	uint32_t minor_ver;
	std::string version_string;
} ModuleApiVersion;

/**
 * 
 */
class ModuleInterface
{
public:
	/**
	 * Default constructor.
	 */
	ModuleInterface() { }

	/**
	 * Default destructor.
	 */
	virtual ~ModuleInterface() { }

	/**
	 * 
	 */
	virtual bool Load(const std::string& filename, std::shared_ptr<PlatformServices> services, std::shared_ptr<ModuleApiVersion> api_version) = 0;

	/**
	 *
	 */
	virtual void Unload(std::shared_ptr<PlatformServices> services) = 0;

	/**
	 *
	 */
	virtual const std::string name() = 0;

	/**
	 *
	 */
	virtual const ModuleApiVersion version() = 0;

	/**
	 *
	 */
	virtual const std::string description() = 0;

protected:
	typedef bool (*LoadFunc)(std::shared_ptr<PlatformServices>);
	typedef void (*UnloadFunc)(std::shared_ptr<PlatformServices>);
	typedef const std::string (*GetNameFunc)(void);
	typedef const ModuleApiVersion (*GetVersionFunc)(void);
	typedef const std::string (*GetDescriptionFunc)(void);


};

} // namespace module_manager
} // namespace anh

#endif
