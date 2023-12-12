#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

#include "CameraModule/ComputerVisionManager.hpp"
#include "AlarmModule/AlarmManager.hpp"

namespace py = pybind11;


PYBIND11_MODULE(WalkAwake, m){
    py::module_ cam_module = m.def_submodule("CameraModule", "CameraModule");
    py::class_<CameraModule::ComputerVisionManager>(cam_module, "ComputerVisionManager")
            .def(py::init<>())

            .def("VerifyImage", &CameraModule::ComputerVisionManager::VerifyImage,
                 "Target: Find target",
                 py::arg("target"))

            .def("Start",&CameraModule::ComputerVisionManager::Start,
                 "Start the camera live feed [NOT WORKING]", py::arg("image_feed_path"))

            .def("Stop", &CameraModule::ComputerVisionManager::Stop,
                 "Stop the camera live feed [NOT WORKING]");

    py::module_ alarm_module = m.def_submodule("AlarmModule", "AlarmModule");
    py::class_<AlarmModule::AlarmManager>(alarm_module, "AlarmManager")
            .def(py::init<>())

            .def("UpdateAlarms",&AlarmModule::AlarmManager::UpdateAlarms,
                 "Update alarms from json", py::arg("alarms_json"))

            .def("GetAlarms", &AlarmModule::AlarmManager::GetAlarms)

            .def("RegisterCallback", &AlarmModule::AlarmManager::RegisterCallback)

            .def("StopAlarm", &AlarmModule::AlarmManager::StopAlarm,
                 "Stops alarm, and set next if any.")

             .def("Snooze", &AlarmModule::AlarmManager::Snooze,
                  "Snooze alarm for 5 minutes. Works once per alarm.");

}