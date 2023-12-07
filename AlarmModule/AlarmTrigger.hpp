#pragma once

#include <functional>

namespace AlarmModule {
    class AlarmTrigger {
    public:
        AlarmTrigger();
        int SetAlarm();
        int RegisterCallback(std::function<void> CallBack);
        virtual ~AlarmTrigger();

    private:

    };
}
