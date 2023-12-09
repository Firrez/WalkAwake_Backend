#include "../Utils/FileUtil.hpp"
#include "AlarmManager.hpp"
#include <functional>
#include <sys/stat.h>
#include <vector>
#include <chrono>

#define FILES_PATH "data/"
#define ALARM_FILE_NAME "Alarms.json"

using namespace AlarmModule;
using namespace CameraModule;
using namespace std;
using json = nlohmann::json;

AlarmManager::AlarmManager(const function<void()>& CallBack) {
    m_CameraManager = ComputerVisionManager();
    m_SoundController = SoundController();
    m_AlarmTrigger = AlarmTrigger();

    m_AlarmTrigger.RegisterCallback(bind(&AlarmManager::TriggerCallback,this));
    m_UICallBack = CallBack;

    SetNextAlarm();
}

int AlarmManager::UpdateAlarms(const string& m_strAlarms) {
    json m_jsonAlarms = json::parse(m_strAlarms);
    int m_iRetVal = FileUtil::WriteToFile(FILES_PATH, ALARM_FILE_NAME, m_jsonAlarms);
    SetNextAlarm();
    return m_iRetVal;
}

string AlarmManager::GetAlarms() {
    struct stat buffer{};
    if (stat(FILES_PATH, &buffer) != 0)
        return "err";
    json m_jsonAlarms = FileUtil::ReadFromFile(FILES_PATH, ALARM_FILE_NAME);
    return m_jsonAlarms;
}

void AlarmManager::TriggerCallback() {
    m_UICallBack();
    m_SoundController.Play(); //TODO: Needs to run in a separate thread.
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
void AlarmManager::SetNextAlarm() {
    json m_jsonAlarms = GetAlarms();
    auto m_Alarms = m_jsonAlarms["alarms"];
    vector<Alarm> m_vecAlarmList;

    for (auto m_Alarm : m_Alarms)
    {
        Alarm temp {
                m_Alarm["Day"].template get<string>(),
                m_Alarm["Time"].template get<string>(),
                m_Alarm["Enabled"].template get<string>()
        };
        m_vecAlarmList.push_back(temp);
    }

    auto m_tpTime = chrono::system_clock::now();
    time_t m_ttTime = chrono::system_clock::to_time_t(m_tpTime);
    tm *m_tmCurrentTime = localtime(&m_ttTime);
    int m_iWeekDay = m_tmCurrentTime->tm_wday;

    Alarm *m_NextAlarm = nullptr;
    int m_iIndex = m_iWeekDay - 1;
    do {
        if (m_vecAlarmList.at(m_iIndex).enabled)
        {
            *m_NextAlarm = m_vecAlarmList.at(m_iIndex);
            break;
        }
        m_iIndex = ++m_iIndex % 7;
    } while (m_iIndex != m_iWeekDay - 1);

    if (m_NextAlarm != nullptr)
    {
        m_AlarmTrigger.SetAlarm(*m_NextAlarm);
    }
}
#pragma clang diagnostic pop

AlarmManager::~AlarmManager() = default;
