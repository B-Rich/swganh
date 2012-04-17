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
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE ANH Test

#include <boost/test/unit_test.hpp>

#include <map>

#include "anh/hash_string.h"

using namespace anh;
using namespace std;



BOOST_AUTO_TEST_SUITE(ANHHashString)

/// This test shows how to create a hash string and check it's generated identifier.
BOOST_AUTO_TEST_CASE(CreatingEventTypeFromStringGeneratesUniqueIdentifier) {
    HashString hash_string("test_hash_string");
    
    BOOST_CHECK_MESSAGE(uint32_t(0x107D0089) == hash_string.ident(), "HashString did not create the expected identifier");
}

/// This test shows how to compare two hash strings.
BOOST_AUTO_TEST_CASE(CanCompareTwoHashStrings) {
    HashString hash_string1("test_string1");
    HashString hash_string2("another_hash_string");
    HashString hash_string3("another_hash_string");

    BOOST_CHECK_MESSAGE(hash_string1 != hash_string2, "hash_string1 and hash_string2 should not match."); 
    BOOST_CHECK_MESSAGE(hash_string2 == hash_string3, "hash_string2 and hash_string3 should match");
}

/// This test shows how to use HashString as a key in std containers.
BOOST_AUTO_TEST_CASE(CanUseHashStringAsContainerKey) {
    // Create a simple std::map<HashString, int> map.
    map<HashString, int> hash_string_map;

    // Seed the map with some entries for testing.
    hash_string_map.insert(make_pair(HashString("my_key1"), 2000));
    hash_string_map.insert(make_pair(HashString("my_key2"), 9001));
    hash_string_map.insert(make_pair(HashString("my_key3"), 400));

    // Now make sure we can access the map appropriately.
    BOOST_CHECK_EQUAL(2000, hash_string_map[HashString("my_key1")]);
    BOOST_CHECK_EQUAL(9001, hash_string_map[HashString("my_key2")]);
    BOOST_CHECK_EQUAL(400, hash_string_map[HashString("my_key3")]);

    // Try searching the map by the key and make sure it returns the correct result.
    auto it = hash_string_map.find(HashString("my_key1"));
    BOOST_CHECK_MESSAGE(2000 == it->second, "Cannot find a map entry by a HashString");
}
BOOST_AUTO_TEST_SUITE_END()