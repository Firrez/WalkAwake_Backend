#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <nlohmann/json.hpp>
#include "../CameraModule/ComputerVisionManager.hpp"
#include "SoundController.hpp"
#include "AlarmTrigger.hpp"

using namespace std;
using namespace CameraModule;

namespace AlarmModule
{
    class AlarmManager {
    public:
        AlarmManager();
        void RegisterCallback(const function<void(string)>&);
        int UpdateAlarms(const string& m_strAlarms);
        string GetAlarms();
        void StopAlarm();
        int Snooze();
        virtual ~AlarmManager();

    private:
        bool m_bAlarmTriggered;
        bool m_bSnoozeUsed;
        SoundController m_SoundController;
        AlarmTrigger *m_AlarmTrigger;
        function<void(string)> m_UICallBack;
        void TriggerCallback();
        void SetNextAlarm();
        time_t NextAlarmEpoch(const Alarm& m_NextAlarm);
        time_t GetDayEpoch(const Alarm& m_NextAlarm);
        int GetSeconds(int hour, int min);
        void SnoozeWaiter();
    };
}