#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

using namespace std;

struct Alarm {
    Alarm(string day, string time, const string& enabled) {
        this->day = std::move(day);
        this->time = std::move(time);
        this->enabled = enabled == "True";
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
        int StopAlarm();
        int RegisterCallback(function<void()> CallBack);
        virtual ~AlarmTrigger();

    private:
        pthread_t m_pthAlarmThread{};
        bool IsActive;
        function<void()> m_ptrCallBack;
        void ClockTimer(void *arg1);
    };
}
