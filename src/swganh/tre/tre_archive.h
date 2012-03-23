// This file is part of SWGANH which is released under GPL v2.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_TRE_TRE_ARCHIVE_H_
#define SWGANH_TRE_TRE_ARCHIVE_H_

#include <cstdint>
#include <algorithm>
#include <future>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "tre_reader.h"

namespace swganh {
namespace tre {
    
    class TreArchive
    {
    public:
        explicit TreArchive(std::vector<TreReader>&& readers);

        explicit TreArchive(std::vector<std::string>&& resource_files);

        uint32_t GetResourceSize(const std::string& resource_name) const;

        std::vector<char> GetResource(const std::string& resource_name);
        
        std::string GetMd5Hash(const std::string& resource_name) const;
        
        std::vector<std::string> GetTreFilenames() const;
        
        std::vector<std::string> GetAvailableResources() const;

    private:
        typedef std::vector<TreReader> ReaderList;
        ReaderList readers_;
    };
}}  // namespace swganh::tre

#endif  // SWGANH_TRE_TRE_ARCHIVE_H_
