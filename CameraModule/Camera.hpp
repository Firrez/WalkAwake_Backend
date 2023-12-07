//
// Created by sande on 06/12/2023.
//

#ifndef WALKAWAKE_BACKEND_CAMERA_HPP
#define WALKAWAKE_BACKEND_CAMERA_HPP


using namespace std;

namespace CameraModule {

    class Camera {

    public:
        Camera();
        virtual ~Camera();
        void CaptureImage();
        bool StartLiveFeed();
        bool StopLiveFeed();
        int GetLiveFeedFPS();

    private:

    };

}

#endif //WALKAWAKE_BACKEND_CAMERA_HPP
