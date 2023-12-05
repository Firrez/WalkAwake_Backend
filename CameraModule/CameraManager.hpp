#pragma once

#include <string>
#include "ApiCaller.hpp"

using namespace std;

namespace CameraModule {

    class CameraManager {
    public:
        CameraManager();


    private:
        ApiCaller apiCaller;
        int CompareTargetResponse(string m_strTarget, string m_strApiResult);
    };
}