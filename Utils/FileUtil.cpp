#include "FileUtil.hpp"

int FileUtil::WriteToFile(const string& m_strPath, const string& m_strFileName, const json& m_jsonContent) {
    ofstream m_ostFile;
    m_ostFile.open(m_strPath + m_strFileName);
    m_ostFile << m_jsonContent;
    m_ostFile.close();
    return EXIT_SUCCESS;
}

json FileUtil::ReadFromFile(const string& m_strPath, const string& m_strFileName) {
    ifstream m_istFile;
    m_istFile.open(m_strPath + m_strFileName);
    json m_jsonContent = json::parse(m_istFile);
    m_istFile.close();
    return m_jsonContent;
}
