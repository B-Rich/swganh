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

#include <anh/network/soe/session_request_filter.h>
#include <anh/byte_buffer.h>
#include <anh/network/soe/protocol_packets.h>
#include <anh/network/soe/session.h>
#include <anh/network/soe/session_manager.h>
#include <anh/network/soe/service.h>
#include <anh/network/soe/incoming_sessionless_packet.h>
#include <anh/utilities.h>

#ifdef ERROR
#undef ERROR
#endif

#include <glog/logging.h>

namespace anh {
namespace network {
namespace soe {

SessionRequestFilter::SessionRequestFilter(Service* service)
	: tbb::filter(serial_in_order)
	, service_(service)
{
}

SessionRequestFilter::~SessionRequestFilter(void)
{
}

void* SessionRequestFilter::operator()(void* item)
{
	// No more packets to process.
	if(service_->sessionless_messages_.empty())
	{
		return NULL;
	}

	IncomingSessionlessPacket* sessionless_message = service_->sessionless_messages_.front();
	service_->sessionless_messages_.pop_front();

	if(sessionless_message->message()->peek<uint16_t>(true) == SESSION_REQUEST && sessionless_message->message()->size() == 14)
	{
		LOG(WARNING) << "Creating Session... [" << sessionless_message->remote_endpoint().address().to_string() << ":" << sessionless_message->remote_endpoint().port() << "]";
		
		// Create Session
		auto session = std::make_shared<Session>(sessionless_message->remote_endpoint(), service_);

		SessionRequest request(*sessionless_message->message());
		session->handleSessionRequest_(request);
	}

	delete sessionless_message;
	return 0;
}

} // namespace soe
} // namespace network
} // namespace anh