#include "AlarmTrigger.hpp"
#include <thread>
#include <chrono>
#include <utility>

using namespace AlarmModule;
using namespace std;
AlarmTrigger::AlarmTrigger() = default;


int AlarmTrigger::SetAlarm(const Alarm &m_NextAlarm) {
    if (m_ptrCallBack == nullptr)
        return EXIT_FAILURE;

    string m_strNextAlarm = m_NextAlarm.day + " " + m_NextAlarm.time;
    struct tm *m_ptrNextAlarm; //TODO: Find exact date and time & use sleep_until.
    strptime(m_strNextAlarm.c_str(), "%A %R", m_ptrNextAlarm);

    thread clockCheckLoop(&AlarmTrigger::ClockTimer,this, m_ptrNextAlarm);

    clockCheckLoop.detach();

    //pthread_create(&m_pthAlarmThread, nullptr, &AlarmTrigger::ClockTimer,this, m_ptrNextAlarm);
    //pthread_detach(m_pthAlarmThread);
    return EXIT_SUCCESS;
}

int AlarmTrigger::StopAlarm() {
    IsActive = false;
    return EXIT_SUCCESS;
}

int AlarmTrigger::RegisterCallback(function<void()> CallBack) {
    m_ptrCallBack = std::move(CallBack);
    return EXIT_SUCCESS;
}

void AlarmTrigger::ClockTimer(void *arg1) {
    IsActive = true;
    tm *m_tmAlarm = (tm *) arg1;
    do {
        auto m_tpTime = chrono::system_clock::now();
        time_t m_ttTime = chrono::system_clock::to_time_t(m_tpTime);
        tm *m_tmCurrentTime = localtime(&m_ttTime);

        if (m_tmAlarm->tm_wday == m_tmCurrentTime->tm_wday) {
            if (m_tmAlarm->tm_hour <= m_tmCurrentTime->tm_hour) {
                if (m_tmAlarm->tm_min <= m_tmCurrentTime->tm_min) {
                    m_ptrCallBack();
                    IsActive = false;
                } else {
                    this_thread::sleep_for(chrono::seconds(1));
                }
            } else {
                this_thread::sleep_for(chrono::minutes(1));
            }
        } else {
            this_thread::sleep_for(chrono::hours(1));
        }

    } while (IsActive);
}

AlarmTrigger::~AlarmTrigger() = default;
