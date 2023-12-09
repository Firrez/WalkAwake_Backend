cmake_minimum_required(VERSION 3.22)
project(WalkAwake)
set(CMAKE_CXX_STANDARD 11)

add_library(waAlarmLib AlarmModule/AlarmManager.cpp AlarmModule/AlarmTrigger.cpp AlarmModule/SoundController.cpp)
set_target_properties(waAlarmLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(waCameraLib CameraModule/ComputerVisionManager.cpp CameraModule/ApiCaller.cpp CameraModule/Camera.cpp)
set_target_properties(waCameraLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(waSettingsLib SettingsModule/SettingsManager.cpp Utils/FileUtil.cpp)
set_target_properties(waSettingsLib PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(WalkAwake WA_binder.cpp)
target_link_libraries(WalkAwake PRIVATE waAlarmLib waCameraLib waSettingsLib curl ao mpg123 pthread)