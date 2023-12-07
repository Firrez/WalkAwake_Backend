#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace CameraModule {

    class ApiCaller {
    public:
        ApiCaller();
        string PostImageOnline(const char *m_szImagePath);
        string PostImageLocal(char *m_szImagePath);
        virtual ~ApiCaller();

    private:
        static size_t WriteResponse(void *ptr, size_t size, size_t nmemb, string *s);
    };

} // CameraModule