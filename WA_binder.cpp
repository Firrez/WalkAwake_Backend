#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "CameraModule/ComputerVisionManager.hpp"
#include "AlarmModule/AlarmManager.hpp"

using namespace CameraModule;
using namespace AlarmModule;

namespace py = pybind11;


PYBIND11_MODULE(WalkAwake, m){
    py::class_<ComputerVisionManager>(m, "ComputerVisionManager")
            .def(py::init<>())

            .def("VerifyImage", &ComputerVisionManager::VerifyImage,
                 "Target: Find target, ImagePath: to save image captured",
                 py::arg("target"),py::arg("image_path"))

            .def("Start",&ComputerVisionManager::Start,
                 "Start the camera live feed", py::arg("image_feed_path"))

            .def("Stop", &ComputerVisionManager::Stop);

    py::class_<AlarmManager>(m, "AlarmManager")
            .def(py::init<const std::function<void()> &>())

            .def("UpdateAlarms",&AlarmManager::UpdateAlarms,
                 "Update alarms from json", py::arg("alarms_json"))

            .def("GetAlarms", &AlarmManager::GetAlarms);

}