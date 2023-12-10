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
        void RegisterCallback(const function<void()>&);
        int UpdateAlarms(const string& m_strAlarms);
        string GetAlarms();
        virtual ~AlarmManager();

    private:
        ComputerVisionManager m_CameraManager;
        SoundController m_SoundController;
        AlarmTrigger m_AlarmTrigger;
        function<void()> m_UICallBack;
        void TriggerCallback();
        void SetNextAlarm();
    };
}