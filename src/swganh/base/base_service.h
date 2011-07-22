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

#ifndef SWGANH_BASE_BASE_SERVICE_H_
#define SWGANH_BASE_BASE_SERVICE_H_

#include <memory>
#include <tbb/atomic.h>

#include "anh/service/service_interface.h"

namespace anh {
namespace app {
class KernelInterface;
}}  // namespace anh::app

namespace anh {
namespace event_dispatcher {
class EventDispatcherInterface;
}}  // namespace anh::event_dispatcher

namespace swganh {
namespace base {

class BaseService : public anh::service::ServiceInterface {
public:    
    BaseService(std::shared_ptr<anh::app::KernelInterface> kernel);

    void Start();
    void Stop();

    bool IsRunning() const;

    void DescribeConfigOptions(boost::program_options::options_description& description);

    std::shared_ptr<anh::app::KernelInterface> kernel();

    /*
    *  @brief used to subscribe to events on a serivce
    */
    virtual void subscribe() = 0;
    /*
    *  @brief used to perform any startup specific tasks for the service
    */
    virtual void onStart() = 0;
    /*
    *  @brief used to perform any shutdown specific tasks for the service
    */
    virtual void onStop() = 0;

    /*
    *  @brief gets the event_dispatcher
    */
    std::shared_ptr<anh::event_dispatcher::EventDispatcherInterface> event_dispatcher();
    

private:
    BaseService();
    std::shared_ptr<anh::app::KernelInterface> kernel_;
        
    tbb::atomic<bool> running_;
};

}}  // swganh::base
#endif // SWGANH_BASE_BASE_SERVICE_H_