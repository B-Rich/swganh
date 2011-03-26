/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2011 ANH Studios

 SWGANH is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 SWGANH is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with SWGANH.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <gtest/gtest.h>
#include <anh/module_manager/mock_module_loader.h>
#include <iostream>
#include <fstream>

using namespace testing;
using namespace anh::module_manager;
using namespace anh;
using namespace std;

namespace {

class ModuleManagerTests : public testing::Test
{
public:
    shared_ptr<ModuleManager> module_manager;
    shared_ptr<MockModuleLoader> loader;
protected:
    virtual void SetUp();
    virtual void TearDown(){}
};
void ModuleManagerTests::SetUp() 
{
    module_manager = make_shared<ModuleManager>(loader);
    // create test files
    ofstream of("modules.txt");
    of << "test1" << endl;
    of << "test2" << endl;
    of << "test3" << endl;
    of << "test4" << endl;
    of << "test5" << endl;
    of.flush();
    of.close();
}
TEST_F(ModuleManagerTests, LoadModuleSuccess) {
    EXPECT_TRUE(module_manager->LoadModule("testModule", 0));
    EXPECT_CALL(*loader, Load("testModule", 0));
}

TEST_F(ModuleManagerTests, LoadModuleNotFound) {
    EXPECT_FALSE(module_manager->LoadModule("notFound", 0));
}

TEST_F(ModuleManagerTests, LoadModuleFromMap) {
    ModulesMap modules;
    modules.insert(ModulesPair(HashString("test1"), nullptr));
    modules.insert(ModulesPair(HashString("test2"), nullptr));
    modules.insert(ModulesPair(HashString("test3"), nullptr));
    modules.insert(ModulesPair(HashString("test4"), nullptr));
    modules.insert(ModulesPair(HashString("test5"), nullptr));

    module_manager->LoadModules(modules);
    EXPECT_CALL(*loader,  Load(_, nullptr))
        .Times(5);
    
}
TEST_F(ModuleManagerTests, LoadModuleFromPlainTextFile_Success)
{  
    module_manager->LoadModules("modules.txt");
}
TEST_F(ModuleManagerTests, LoadModuleFromPlainTextFile_NotExists)
{
    EXPECT_DEATH(module_manager->LoadModules("notfound.txt"), "Could not load file");
}
} // anon namespace