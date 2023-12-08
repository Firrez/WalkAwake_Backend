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

struct Alarm {
    Alarm(string day, string time, const string& enabled) {
        this->day = std::move(day);
        this->time = std::move(time);
        istringstream(enabled) >> boolalpha >> this->enabled;
    };
    string day;
    string time;
    bool enabled{};
};

namespace AlarmModule
{
    class AlarmManager {
    public:
        explicit AlarmManager(const function<void()>& CallBack);
        int UpdateAlarms(string m_strAlarms);
        string GetAlarms();
        virtual ~AlarmManager();

    private:
        ComputerVisionManager m_CameraManager;
        SoundController m_SoundController;
        AlarmTrigger m_AlarmTrigger;
        static function<void()> m_UICallBack;
        static void TriggerCallback();
        void SetTrigger();
        void ActivateAlarm();
    };
}