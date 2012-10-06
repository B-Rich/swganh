// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <atomic>
#include <map>
#include <set>
#include <boost/thread/mutex.hpp>
#include <swganh/event_dispatcher.h>

namespace boost
{
class thread;
}

namespace swganh
{
namespace object
{
	class Object;
}

namespace spawn
{
	class FsmBundleInterface;
	class FsmStateInterface;
	class FsmController;

	typedef std::function<std::shared_ptr<FsmBundleInterface>(std::shared_ptr<FsmStateInterface>)> BundleGenerator;

	class FiniteStateMachine
	{
	public:
	
		FiniteStateMachine(uint32_t threads_required, std::shared_ptr<FsmStateInterface> initial_state,
			BundleGenerator bundle_factory);

		~FiniteStateMachine();

		void StartManagingObject(std::shared_ptr<swganh::object::Object> object);
		void StopManagingObject(std::shared_ptr<swganh::object::Object> object);

		void MarkDirty(std::shared_ptr<FsmController> controller_);

	private:
		std::atomic<bool> shutdown_;
		std::vector<boost::thread> threads_;
		boost::mutex mutex_;

		std::set<std::shared_ptr<FsmController>> controllers_, dirty_controllers_;

		BundleGenerator bundle_factory_;
		std::shared_ptr<FsmStateInterface> initial_state_;
	};
}
}