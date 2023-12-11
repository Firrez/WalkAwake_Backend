#include "../Utils/FileUtil.hpp"
#include "../Utils/DefaultCache.hpp"
#include "AlarmManager.hpp"
#include <functional>
#include <sys/stat.h>
#include <iterator>
#include <list>
#include <chrono>
#include <cstring>
#include <thread>

using namespace AlarmModule;
using namespace CameraModule;
using namespace std;
using json = nlohmann::json;

AlarmManager::AlarmManager() {
    m_bAlarmTriggered = false;
    m_bSnoozeUsed = false;
    m_SoundController = SoundController();
    m_AlarmTrigger = new AlarmTrigger();

    m_AlarmTrigger->RegisterCallback(bind(&AlarmManager::TriggerCallback,this));

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

void AlarmManager::StopAlarm() {
    m_SoundController.Stop();
    SetNextAlarm();
}

int AlarmManager::Snooze() {
    if (!m_bSnoozeUsed)
        thread snoozeThread(&AlarmManager::SnoozeWaiter, this);
}

void AlarmManager::RegisterCallback(const function<void(string)>& CallBack) {
    m_UICallBack = CallBack;
}

void AlarmManager::TriggerCallback() {
    m_bAlarmTriggered = true;
    m_bSnoozeUsed = false;
    m_UICallBack("trigger_alarm");
    m_SoundController.Play(); //TODO: Needs to run in a separate thread.
}

time_t AlarmManager::NextAlarmEpoch(const Alarm& m_NextAlarm) {
    struct tm m_tmAlarmTime{};
    memset(&m_tmAlarmTime, 0, sizeof(struct tm));
    strptime(m_NextAlarm.time.c_str(), "%R", &m_tmAlarmTime);
    time_t m_AlarmDay = GetDayEpoch(m_NextAlarm) + GetSeconds(m_tmAlarmTime.tm_hour, m_tmAlarmTime.tm_min);
    m_AlarmDay -= m_AlarmDay % 60;
    return m_AlarmDay;
}

time_t AlarmManager::GetDayEpoch(const Alarm& m_NextAlarm){
    struct tm m_tmNextAlarm{};
    memset(&m_tmNextAlarm, 0, sizeof(struct tm));
    string m_strNextAlarm = m_NextAlarm.day + " " + m_NextAlarm.time;
    strptime(m_strNextAlarm.c_str(), "%A %R", &m_tmNextAlarm);
    int m_iNextAlarmWeekDay = m_tmNextAlarm.tm_wday;
    int m_iNextAlarmHour = m_tmNextAlarm.tm_hour;
    int m_iNextAlarmMin = m_tmNextAlarm.tm_min;

    auto checkingDay = chrono::system_clock::now();
    time_t time_t_checkingDay;
    tm *tm_checkingDay;
    for (int offset = 0; offset <= 7; offset++)
    {

        time_t_checkingDay = chrono::system_clock::to_time_t(checkingDay);
        tm_checkingDay = localtime(&time_t_checkingDay);

        if (tm_checkingDay->tm_wday == m_iNextAlarmWeekDay)
        {
            if (offset == 0)
            {
                if (tm_checkingDay->tm_hour < m_iNextAlarmHour)
                {
                    time_t m_AlarmDay = time_t_checkingDay - GetSeconds(tm_checkingDay->tm_hour, tm_checkingDay->tm_min);
                    return m_AlarmDay;
                }
                else if (tm_checkingDay->tm_hour == m_iNextAlarmHour && tm_checkingDay->tm_min < m_iNextAlarmMin)
                {
                    time_t m_AlarmDay = time_t_checkingDay - GetSeconds(tm_checkingDay->tm_hour, tm_checkingDay->tm_min);
                    return m_AlarmDay;
                }
            }
            else
            {
                time_t m_AlarmDay = time_t_checkingDay - GetSeconds(tm_checkingDay->tm_hour, tm_checkingDay->tm_min);
                return m_AlarmDay;
            }
        }

        checkingDay += chrono::hours(24);
    }
}

int AlarmManager::GetSeconds(int hour, int min) {
    return ((hour * 60) + min) * 60;
}

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
            m_AlarmTrigger->SetAlarm(NextAlarmEpoch(m_Alarm));
            break;
        }
        m_iIndex = ++m_iIndex % 7;
    } while (m_iIndex != m_iEndIndex);

}

void AlarmManager::SnoozeWaiter() {
    m_bSnoozeUsed = true;
    m_SoundController.Stop();
    this_thread::sleep_for(chrono::minutes(5));
    if (m_bAlarmTriggered)
        m_SoundController.Play();
}

AlarmManager::~AlarmManager() = default;
