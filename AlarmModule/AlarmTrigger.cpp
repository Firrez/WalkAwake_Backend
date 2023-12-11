#include "AlarmTrigger.hpp"
#include <thread>
#include <chrono>
#include <utility>


using namespace AlarmModule;
using namespace std;

AlarmTrigger::AlarmTrigger() = default;

int AlarmTrigger::SetAlarm(const time_t& m_NextAlarmEpoch) {
    if (m_ptrCallBack == nullptr)
        return EXIT_FAILURE;

    thread clockCheckLoop(&AlarmTrigger::ClockTimer,this, m_NextAlarmEpoch);

    clockCheckLoop.detach();
    return EXIT_SUCCESS;
}

int AlarmTrigger::StopAlarm() {
    inactive = 1;
    cv.notify_all();
    return EXIT_SUCCESS;
}

int AlarmTrigger::RegisterCallback(function<void()> CallBack) {
    m_ptrCallBack = std::move(CallBack);
    return EXIT_SUCCESS;
}

void AlarmTrigger::ClockTimer(time_t epoch) {
    inactive = 0;
    unique_lock<mutex> lk(cv_m);
    auto m_WaitTime = chrono::system_clock::time_point(chrono::seconds(epoch));
    if (!cv.wait_until(lk, m_WaitTime, [this](){return inactive == 1;}))
        m_ptrCallBack();
}

AlarmTrigger::~AlarmTrigger() = default;
