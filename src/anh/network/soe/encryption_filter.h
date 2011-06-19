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

#ifndef ANH_NETWORK_SOE_ENCRYPTION_FILTER_H_
#define ANH_NETWORK_SOE_ENCRYPTION_FILTER_H_

#include <cstdint>
#include <memory>
#include <tbb/pipeline.h>

namespace anh {
namespace network {
namespace soe {

// FORWARD DECLARATIONS
class Service;
class OutgoingPacket;

class EncryptionFilter
{
public:
	EncryptionFilter(Service* service);
	~EncryptionFilter(void);

	std::shared_ptr<OutgoingPacket> operator()(std::shared_ptr<OutgoingPacket> item) const;

private:
	void Encrypt_(char* buffer, uint32_t len, uint32_t seed) const;

	Service*	service_;
};

} // namespace soe
} // namespace network
} // namespace anh

#endif // ANH_NETWORK_SOE_DECOMPRESSION_FILTER_H_