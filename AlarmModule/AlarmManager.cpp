#include "../Utils/FileUtil.hpp"
#include "../Utils/DefaultCache.hpp"
#include "AlarmManager.hpp"
#include <functional>
#include <sys/stat.h>
#include <iterator>
#include <list>
#include <chrono>

using namespace AlarmModule;
using namespace CameraModule;
using namespace std;
using json = nlohmann::json;

AlarmManager::AlarmManager() {
    m_CameraManager = ComputerVisionManager();
    m_SoundController = SoundController();
    m_AlarmTrigger = AlarmTrigger();

    m_AlarmTrigger.RegisterCallback(bind(&AlarmManager::TriggerCallback,this));

    SetNextAlarm();
}

int AlarmManager::UpdateAlarms(const string& m_strAlarms) {
    json m_jsonAlarms = json::parse(m_strAlarms);
    int m_iRetVal = FileUtil::WriteToFile(FILES_PATH, ALARM_FILE_NAME, m_jsonAlarms);
    SetNextAlarm();
    return m_iRetVal;
}

string AlarmManager::GetAlarms() {
    string m_strFullPath = FILES_PATH;
    m_strFullPath.append(ALARM_FILE_NAME);
    struct stat buffer{};
    if (stat(m_strFullPath.c_str(), &buffer) != 0)
        FileUtil::WriteToFile(FILES_PATH, ALARM_FILE_NAME, DEFAULT_ALARM_STRING);
    json m_jsonAlarms = FileUtil::ReadFromFile(FILES_PATH, ALARM_FILE_NAME);
    return m_jsonAlarms.dump();
}

void AlarmManager::RegisterCallback(const function<void()>& CallBack) {
    m_UICallBack = CallBack;
}

void AlarmManager::TriggerCallback() {
    m_UICallBack();
    m_SoundController.Play(); //TODO: Needs to run in a separate thread.
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
void AlarmManager::SetNextAlarm() {
    json m_jsonAlarms = json::parse(GetAlarms());
    auto m_Alarms = m_jsonAlarms["alarms"];
    list<Alarm> m_listAlarms;

    for (auto m_Alarm : m_Alarms)
    {
        Alarm temp {
                m_Alarm["Day"].template get<string>(),
                m_Alarm["Time"].template get<string>(),
                m_Alarm["Enabled"].template get<string>()
        };
        m_listAlarms.push_back(temp);
    }

    auto m_tpTime = chrono::system_clock::now();
    time_t m_ttTime = chrono::system_clock::to_time_t(m_tpTime);
    tm *m_tmCurrentTime = localtime(&m_ttTime);
    int m_iWeekDay = m_tmCurrentTime->tm_wday;

    int m_iIndex;
    if (m_iWeekDay == 0)
        m_iIndex = 6;
    else
        m_iIndex = m_iWeekDay - 1;

    int m_iEndIndex = m_iIndex;
    do {
        auto m_itrAlarmIterator = m_listAlarms.begin();
        advance(m_itrAlarmIterator, m_iIndex);
        Alarm m_Alarm = *m_itrAlarmIterator;
        if (m_Alarm.enabled)
        {
            m_AlarmTrigger.SetAlarm(m_Alarm);
            break;
        }
        m_iIndex = ++m_iIndex % 7;
    } while (m_iIndex != m_iEndIndex);

}

#pragma clang diagnostic pop

AlarmManager::~AlarmManager() = default;
