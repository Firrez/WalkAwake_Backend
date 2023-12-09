#pragma once

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class FileUtil {
public:
    static int WriteToFile(const string& m_strPath, const string& m_strFileName, const json& m_jsonContent);
    static json ReadFromFile(const string& m_strPath, const string& m_strFileName);
};
