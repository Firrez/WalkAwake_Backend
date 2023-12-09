cmake_minimum_required(VERSION 3.22)
project(WalkAwake)
set(CMAKE_CXX_STANDARD 11)

add_library(waSettingsLib SettingsModule/SettingsManager.cpp Utils/FileUtil.cpp)
set_target_properties(waSettingsLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(waAlarmLib AlarmModule/SoundController.cpp AlarmModule/AlarmTrigger.cpp AlarmModule/AlarmManager.cpp)
set_target_properties(waAlarmLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(waCameraLib CameraModule/Camera.cpp CameraModule/ApiCaller.cpp CameraModule/ComputerVisionManager.cpp)
set_target_properties(waCameraLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(WalkAwake WA_binder.cpp)
target_link_libraries(WalkAwake PRIVATE waSettingsLib waAlarmLib waCameraLib curl ao mpg123 pthread)