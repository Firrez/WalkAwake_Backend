#pragma once

#include <functional>
#include <iostream>
#include <string>

using namespace std;

struct Alarm {
    Alarm(string day, string time, const string& enabled) {
        this->day = std::move(day);
        this->time = std::move(time);
        this->enabled = enabled == "enabled";
    };
    string day;
    string time;
    bool enabled{};
};

namespace AlarmModule {
    class AlarmTrigger {
    public:
        AlarmTrigger();
        int SetAlarm(const Alarm& m_NextAlarm);
        static int StopAlarm();
        int RegisterCallback(function<void()> CallBack);
        virtual ~AlarmTrigger();

    private:
        pthread_t m_pthAlarmThread{};
        static bool IsActive;
        static function<void()> m_ptrCallBack;
        static void *ClockTimer(void *arg1);
    };
}
