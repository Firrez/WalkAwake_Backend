#include "AlarmManager.hpp"
#include <sys/stat.h>

#define ALARMSPATH "path/to/file"

using namespace AlarmModule;
using namespace CameraModule;

AlarmManager::AlarmManager(const function<void()>& CallBack) {
    m_CameraManager = ComputerVisionManager();
    m_SoundController = SoundController();
    m_AlarmTrigger = AlarmTrigger();

    m_AlarmTrigger.RegisterCallback(TriggerCallback);
    m_UICallBack = CallBack;
}

int AlarmManager::UpdateAlarms(string m_strAlarms) {

    return 0;
}

string AlarmManager::GetAlarms() {
    struct stat buffer{};
    if (stat(ALARMSPATH, &buffer) != 0)
        return "err";
    return std::string();
}

void AlarmManager::TriggerCallback() {
    m_UICallBack();
}

void AlarmManager::SetTrigger() {

}

void AlarmManager::ActivateAlarm() {

}

AlarmManager::~AlarmManager() = default;
