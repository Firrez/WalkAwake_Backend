#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace CameraModule {

    class ApiCaller {
    public:
        ApiCaller();
        string VerifyImageOnline();
        string VerifyImageLocal();
        virtual ~ApiCaller();

    private:
        static size_t WriteResponse(void *ptr, size_t size, size_t nmemb, string *s);
    };

} // CameraModule