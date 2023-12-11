#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <condition_variable>

using namespace std;

struct Alarm {
    Alarm(string day, string time, const string& enabled) {
        this->day = std::move(day);
        this->time = std::move(time);
        this->enabled = enabled == "True" || enabled == "true";
    };
    string day;
    string time;
    bool enabled{};
};

namespace AlarmModule {
    class AlarmTrigger {
    public:
        AlarmTrigger();
        int SetAlarm(const time_t& m_NextAlarmEpoch);
        int StopAlarm();
        int RegisterCallback(function<void()> CallBack);
        virtual ~AlarmTrigger();

    private:
        condition_variable cv;
        mutex cv_m;
        atomic<int> inactive{0};
        function<void()> m_ptrCallBack;
        void ClockTimer(time_t epoch);

    };
}
