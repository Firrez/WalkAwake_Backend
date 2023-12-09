#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "CameraModule/ComputerVisionManager.hpp"

using namespace CameraModule;
namespace py = pybind11;


PYBIND11_MODULE(WalkAwake, m){
    py::class_<ComputerVisionManager>(m, "ComputerVisionManager")
            .def(py::init<>())

            .def("VerifyImage", &ComputerVisionManager::VerifyImage,
                 "Target: Find target, ImagePath: path of image to detect",
                 py::arg("target"),py::arg("image_path"))

            .def("Start",&ComputerVisionManager::Start,
                 "Start the camera live feed", py::arg("image_feed_path"))

            .def("Stop", &ComputerVisionManager::Stop);
}