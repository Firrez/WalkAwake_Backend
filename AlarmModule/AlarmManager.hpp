#pragma once

#include <string>

using namespace std;

namespace AlarmModule
{
    class AlarmManager {
    public:
        AlarmManager();
        int update_alarms(string);
        string get_alarms();

    private:
        void set_trigger();
    };
}