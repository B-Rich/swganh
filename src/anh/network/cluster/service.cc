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
#include <iostream>
#include <anh/byte_buffer.h>

#include <anh/network/cluster/service.h>
#include <anh/network/cluster/socket.h>

#ifdef ERROR
#undef ERROR
#endif

#include <glog/logging.h>

namespace anh {
namespace network {
namespace cluster {

Service::Service(void)
{
	//incoming_pipeline_.add_filter();
}

Service::~Service(void)
{	
}

void Service::Start(void)
{
	
}

void Service::Update(void)
{
	io_service_.poll();
	outgoing_pipeline_.run(1000);
	incoming_pipeline_.run(1000);
}

void Service::Shutdown(void)
{
	outgoing_pipeline_.clear();
	incoming_pipeline_.clear();
	socket_.reset();
}

void Service::OnSocketRecv_(boost::asio::ip::tcp::endpoint& remote_endpoint, std::shared_ptr<anh::ByteBuffer> message)
{
	
}

} // namespace soe
} // namespace network
} // namespace anh