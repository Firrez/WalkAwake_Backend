#pragma once

#include <string>
#include "../CameraModule/ComputerVisionManager.hpp"

using namespace std;


struct Alarm {
    string day;
    string time;
    bool enabled;
};

namespace AlarmModule
{
    class AlarmManager {
    public:
        AlarmManager();
        int UpdateAlarms(string m_strAlarms);
        string GetAlarms();
        int TriggerCallback();
        virtual ~AlarmManager();

    private:
        CameraModule::ComputerVisionManager cameraManager;
        void SetTrigger();
        void ActivateAlarm();
    };
}