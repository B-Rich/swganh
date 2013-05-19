// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include <set>
#include <queue>
#include <functional>

#include "detault_serializer.h"

namespace swganh
{
namespace containers
{

template<typename T, Serializer=DefaultSerializer<T>>
class NetworkSet
{
public:

	void remove(T& data, bool update=true)
	{
		auto itr = data_.find(data);
		if(itr != data_.end())
		{
			data_.erase(itr);
			if(update)
			{
				deltas_.push_back([=] (swganh::messages::DeltasMessage& message) {
					message.data.write<uint8_t>(0);
					Serializer::SerializeDelta(message, data);
				});
			}
		}
	}
	
	void add(T& data, bool update=true)
	{
		auto pair = data_.insert(data);
		if(pair.second)
		{
			if(update)
			{
				deltas_.push_back([=] (swganh::messages::DeltasMessage& message) {
					message.data.write<uint8_t>(1);
					Serializer::SerializeDelta(message, pair.first);
				});
			}
		}
	}
	
	void clear(bool update=true)
	{
		data_.clear();
		if(update)
		{
			deltas_.push_back([=] (swganh::messages::DeltasMessage& message) {
				message.data.write<uint8_t>(2);
			});
		}
	}
	
	std::set<T> data()
	{
		return data_;
	}
	
	std::set<T>& raw()
	{
		return data_;
	}

	void Serialize(swganh::messages::BaseSwgMessage* message)
	{
		if(message->Opcode() == swganh::messages::BaselinesMessage::opcode)
		{
			Serialize(*((swganh::messages::BaselinesMessage*)message));
		}
		else if(message->Opcode() == swganh::messages::DeltasMessage::opcode)
		{
			Serialize(*((swganh::messages::DeltasMessage*)message));
		}
	}
	
	void Serialize(swganh::messages::BaselinesMessage& message)
	{
		message.data.write<uint32_t>(data_.size());
        message.data.write<uint32_t>(0);
		for(auto& item : data_)
		{
			Serializer::SerializeBaseline(message, item);
		}
	}
	
	void Serialize(swganh::messages::DeltasMessage& message)
	{
		message.data.write<uint32_t>(deltas_.size());
		message.data.write<uint32_t>(++update_counter_);
		
		while(!deltas_.empty())
		{
			deltas_.top()(message.data);
			deltas_.pop();
		}
	}
	
private:
	std::set<T> data_;
	
	uint32_t update_counter_;
	std::queue<std::function<void(swganh::messages::DeltasMessage&)>> deltas_;
};

}
}