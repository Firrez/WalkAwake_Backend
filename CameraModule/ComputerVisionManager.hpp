#pragma once

#include <string>
#include "ApiCaller.hpp"
#include "Camera.hpp"

using namespace std;

namespace CameraModule {

    class ComputerVisionManager {
    public:
        ComputerVisionManager();
        int VerifyImage(const string& m_strTarget, const string& m_strImagePath);
        bool Start(const string& feedPath);
        bool Stop();
        virtual ~ComputerVisionManager();

    private:
        ApiCaller apiCaller;
        Camera camera;
        static int CompareTargetResponse(const string& m_strTarget, const string& m_strApiResult);
    };
}