//
// Created by sande on 06/12/2023.
//

#include "Camera.hpp"

CameraModule::Camera::Camera() {

}

void CameraModule::Camera::CaptureImage() {

}

bool CameraModule::Camera::StartLiveFeed() {
    return false;
}

bool CameraModule::Camera::StopLiveFeed() {
    return false;
}


int CameraModule::Camera::GetLiveFeedFPS() {
    return 0;
}


CameraModule::Camera::~Camera() = default;
