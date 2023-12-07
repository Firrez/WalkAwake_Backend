//
// Created by sande on 06/12/2023.
//

#ifndef WALKAWAKE_BACKEND_CAMERA_HPP
#define WALKAWAKE_BACKEND_CAMERA_HPP

#include <string>
#include <atomic>

using namespace std;

namespace CameraModule {

    class Camera {

    public:
        Camera();
        virtual ~Camera();
        string CaptureImage(const string& savePath);
        bool StartLiveFeed(const string& feedPath);
        bool StopLiveFeed();
        int GetLiveFeedFPS();

    private:
        atomic<bool> running;
        string liveFeedPath;
        void liveFeedLoop();

        int fps;
    };

}

#endif //WALKAWAKE_BACKEND_CAMERA_HPP
