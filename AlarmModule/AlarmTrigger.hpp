#pragma once

#include <functional>
#include <string>

using namespace std;

namespace AlarmModule {
    class AlarmTrigger {
    public:
        AlarmTrigger();
        int SetAlarm(const string& m_strNextAlarm);
        int StopAlarm();
        int RegisterCallback(function<void()> CallBack);
        virtual ~AlarmTrigger();

    private:
        pthread_t m_pthAlarmThread{};
        static bool IsActive;
        static function<void()> m_ptrCallBack;
        static void *ClockTimer(void *arg1);
    };
}
