#include "AlarmManager.hpp"

using namespace AlarmModule;
using namespace CameraModule;

AlarmManager::AlarmManager() {
    cameraManager = CameraManager();
}

int AlarmManager::UpdateAlarms(string m_strAlarms) {

    return 0;
}

string AlarmManager::GetAlarms() {
    return std::string();
}

int AlarmManager::TriggerCallback() {
    return 0;
}

void AlarmManager::SetTrigger() {

}

void AlarmManager::ActivateAlarm() {

}

AlarmManager::~AlarmManager() = default;
