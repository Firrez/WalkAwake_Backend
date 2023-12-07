#include "ComputerVisionManager.hpp"
#include <nlohmann/json.hpp>
#include <utility>
#include <vector>

using namespace CameraModule;
using json = nlohmann::json;

struct ApiObject {
    explicit ApiObject(string name) {
        this->name = std::move(name);
    }
    string name;
};

ComputerVisionManager::ComputerVisionManager() {
    apiCaller = ApiCaller();
}


int ComputerVisionManager::VerifyImage(const string& m_strTarget, const string& m_strImagePath) {
    string m_strApiResult = apiCaller.PostImageOnline(m_strImagePath.c_str());
    return CompareTargetResponse(m_strTarget, m_strApiResult);
}

int ComputerVisionManager::CompareTargetResponse(const string& m_strTarget, const string& m_strApiResult) {
    json m_jsonApiResult = json::parse(m_strApiResult);
    auto m_jsonData = m_jsonApiResult["data"];
    auto m_jsonObjects = m_jsonData["objects"];

    vector<ApiObject> m_vecObjects;
    for (auto m_jsonObject : m_jsonObjects)
    {
        ApiObject m_aobTempObject {
            m_jsonObject["name"].template get<string>()
        };
        m_vecObjects.push_back(m_aobTempObject);
    }

    for (const ApiObject& m_aobObj : m_vecObjects)
    {
        if (m_strTarget == m_aobObj.name)
            return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

ComputerVisionManager::~ComputerVisionManager() = default;
