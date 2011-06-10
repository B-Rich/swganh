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

#include <anh/network/cluster/outgoing_start_filter.h>
#include <anh/network/cluster/cluster_service.h>

namespace anh {
namespace network {
namespace cluster {

OutgoingStartFilter::OutgoingStartFilter(ClusterService* service)
	: tbb::filter(serial_in_order)
	, service_(service) 
{
}

OutgoingStartFilter::~OutgoingStartFilter(void)
{
}

void* OutgoingStartFilter::operator()(void* item)
{
	// Cut the pipeline loop if we run out of messages.
	if(service_->outgoing_messages_.empty())
		return NULL;

	TCPMessage* packet = service_->outgoing_messages_.front();
	service_->outgoing_messages_.pop_front();

	// make sure we have a valid client
	if(packet->client() == nullptr)
	{
		delete packet;
		return NULL;
	}

	return packet;
}

} // namespace cluster
} // namespace network
} // namespace anh