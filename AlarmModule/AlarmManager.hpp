#pragma once

#include <string>
#include "../CameraModule/CameraManager.hpp"

using namespace std;


struct alarm {
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
        string get_alarms();
        int trigger_callback();

    private:
        void set_trigger();
        void activate_alarm();
    };
}