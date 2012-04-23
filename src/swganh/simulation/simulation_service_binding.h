// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_SIMULATION_SIMULATION_SERVICE_BINDING_H_
#define SWGANH_SIMULATION_SIMULATION_SERVICE_BINDING_H_

#ifndef WIN32
#include <Python.h>
#endif

#include "anh/python_shared_ptr.h"
#include "simulation_service.h"

#include <boost/python.hpp>

using namespace swganh::simulation;
using namespace boost::python;
using namespace std;

void exportSimulationService()
{
    typedef std::shared_ptr<swganh::object::Object> (SimulationService::*GetObjectByIdBinding)(uint64_t);

    class_<SimulationService, std::shared_ptr<SimulationService>, boost::noncopyable>("SimulationService", "The simulation service handles the current scenes aka planets", no_init)
        .def("persist", &SimulationService::PersistObject, "persists the specified object and it's containing objects")
        .def("findObjectById", GetObjectByIdBinding(&SimulationService::GetObjectById), "Finds an object by its id")
        ;
}

#endif //SWGANH_SIMULATION_SIMULATION_SERVICE_BINDING_H_