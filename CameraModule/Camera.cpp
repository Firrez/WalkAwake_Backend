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

atomic<bool> running;
atomic<int> currentFPS;

Camera::Camera() {
    running = false;
}

string Camera::CaptureImage(const string& savePath) {

    string fileName = "image_capture";
    string command = "libcamera-still";
    string parameters = "-0";
    string extension = ".jpg";

    stringstream formattedString;
    formattedString << command << " " << parameters << " " << savePath << fileName << extension;
    // test print
    cout << formattedString.str() << endl;

    system(formattedString.str().c_str());

    stringstream returnString;
    returnString << savePath << fileName << extension;
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

    thread myThread(&Camera::liveFeedLoop,this);

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
