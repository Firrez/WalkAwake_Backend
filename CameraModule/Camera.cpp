//
// Created by sande on 06/12/2023.
//

#include "Camera.hpp"
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;
using namespace CameraModule;


atomic<int> currentFPS;
atomic<bool> running;

Camera::Camera() {
    running = false;
}

string Camera::CaptureImage(const string& savePath) {


    stringstream formattedString;
    formattedString << "libcamera-still --width 800 --height 480 -o " << savePath << "/image_capture.jpg -n -t 1";
    // test print
    cout << formattedString.str() << endl;

    system(formattedString.str().c_str());

    stringstream returnString;
    returnString << savePath << "/image_capture.jpg";
    return returnString.str();
}

void Camera::liveFeedLoop() {
    int targetFPS = 15;
    int millisecondsDelay = 1000/targetFPS;
    while (running){
        auto startTime = chrono::steady_clock::now();

        CaptureImage(liveFeedPath);

        // some sleep needed to not take up all cpu
        this_thread::sleep_for(chrono::milliseconds(millisecondsDelay));

        auto endTime = chrono::steady_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        //calculate fps
        currentFPS = 1000 / (duration.count());

        // adjust delay to get target fps
        millisecondsDelay += (currentFPS - targetFPS);
    }
}


bool Camera::StartLiveFeed(const string& savePath) {

    liveFeedPath = savePath;
    // Get the start time
    auto startTime = chrono::steady_clock::now();

    thread loopThread(&Camera::liveFeedLoop,this);
    loopThread.detach();

    return true;
}


bool Camera::StopLiveFeed() {
    running = false;
    return !running;
}


int Camera::GetLiveFeedFPS() {
    return currentFPS;
}



Camera::~Camera() = default;
