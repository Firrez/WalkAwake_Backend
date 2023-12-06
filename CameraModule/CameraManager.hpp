#pragma once

#include <string>
#include "ApiCaller.hpp"

using namespace std;

namespace CameraModule {

    class CameraManager {
    public:
        CameraManager();
        int VerifyImage(const string& m_strTarget);
        virtual ~CameraManager();

    private:
        ApiCaller apiCaller;
        static int CompareTargetResponse(const string& m_strTarget, const string& m_strApiResult);
    };
}