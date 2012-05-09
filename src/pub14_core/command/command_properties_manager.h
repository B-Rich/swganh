// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef PUB14_CORE_COMMAND_COMMAND_PROPERTIES_MANAGER_H_
#define PUB14_CORE_COMMAND_COMMAND_PROPERTIES_MANAGER_H_

#include <cstdint>
#include <vector>

#include <boost/optional.hpp>

#include "swganh/command/command_properties_manager_interface.h"
#include "swganh/tre/readers/datatable_reader.h"

namespace swganh {
namespace tre {
    class TreArchive;
}}  // namespace swganh::tre

namespace pub14_core {
namespace command {

    /**
     * Utility class used to load command properties from a SWG .tre archive.
     */
    class CommandPropertiesManager : public swganh::command::CommandPropertiesManagerInterface
    {
    public:
        /**
         * Creates a loader with a valid TreArchive instance.
         *
         * This loader finds the command_table.iff in the client files managed by
         * the given archive and loads all the relevant command properties from it. 
         
         * The caller is responsible for ensuring the TreArchive instance is properly
         * initialized before passing it in.
         *
         * @param archive Valid TreArchive instance.
         */
        explicit CommandPropertiesManager(swganh::tre::TreArchive* archive);
                
        boost::optional<const swganh::command::CommandProperties&> FindPropertiesForCommand(anh::HashString command);

        /**
         * Loads a map of all of the commands listed in the client files.
         */
        swganh::command::CommandPropertiesMap LoadCommandPropertiesMap();

    private:
        CommandPropertiesManager();

        uint64_t BuildAllowInLocomotion(swganh::tre::readers::DatatableRow* row);
        uint64_t BuildAllowInState(swganh::tre::readers::DatatableRow* row);
        uint64_t BuildBitmask(const std::vector<int>& bits);

        swganh::tre::TreArchive* archive_;
        swganh::command::CommandPropertiesMap command_properties_map_;
    };

}}  // namespace pub14_core::command

#endif  // PUB14_CORE_COMMAND_COMMAND_PROPERTIES_MANAGER_H_
