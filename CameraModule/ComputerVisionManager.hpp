#pragma once

#include <string>
#include "ApiCaller.hpp"

using namespace std;

namespace CameraModule {

    class ComputerVisionManager {
    public:
        ComputerVisionManager();
        int VerifyImage(const string& m_strTarget, const string& m_strImagePath);
        virtual ~ComputerVisionManager();

    private:
        ApiCaller apiCaller;
        static int CompareTargetResponse(const string& m_strTarget, const string& m_strApiResult);
    };
}