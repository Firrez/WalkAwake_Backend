#include <curl/curl.h>
#include "ApiCaller.hpp"

#define API_ADDR "https://imagerecognize.com/api/v3/"
#define API_KEY "5Ta7P48b06S91a03caO815U324K01fcB"
#define IMAGE_PATH "path/to/file"

using namespace CameraModule;

ApiCaller::ApiCaller() = default;

string ApiCaller::VerifyImageOnline() {
    CURL *m_curlClient;
    CURLcode m_ccRes;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    m_curlClient = curl_easy_init();
    if (!m_curlClient)
    {
        return "Failed to initialize CURL";
    }

    struct curl_httppost *m_pPost = nullptr;
    struct curl_httppost *m_pLast = nullptr;
    string m_strResponse;

    // POST request setup
    curl_easy_setopt(m_curlClient, CURLOPT_URL, API_ADDR);
    curl_easy_setopt(m_curlClient, CURLOPT_POST, 1L);

    // Form-Data setup
    curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, "apikey", CURLFORM_COPYCONTENTS, API_KEY, CURLFORM_END);
    curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, "type", CURLFORM_COPYCONTENTS, "objects", CURLFORM_END);
    curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, "max_labels", CURLFORM_COPYCONTENTS, "5", CURLFORM_END);
    curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, "min_confidence", CURLFORM_COPYCONTENTS, "80", CURLFORM_END);
    curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, "file", CURLFORM_FILE, IMAGE_PATH, CURLFORM_END);
    curl_easy_setopt(m_curlClient, CURLOPT_HTTPPOST, m_pPost);

    // Response setup
    curl_easy_setopt(m_curlClient, CURLOPT_WRITEFUNCTION, WriteResponse);
    curl_easy_setopt(m_curlClient, CURLOPT_WRITEDATA, &m_strResponse);

    // Make POST request
    m_ccRes = curl_easy_perform(m_curlClient);
    if (m_ccRes != CURLE_OK)
    {
        return "Failed to perform POST request";
    }

    curl_easy_cleanup(m_curlClient);
    curl_formfree(m_pPost);
    curl_global_cleanup();

    return m_strResponse;
}

string ApiCaller::VerifyImageLocal() {
    return {};
}

size_t ApiCaller::WriteResponse(void *ptr, size_t size, size_t nmemb, string *s) {
    size_t m_lResponseSize = size * nmemb;
    s->append(static_cast<char *>(ptr), m_lResponseSize);
    return m_lResponseSize;
}

ApiCaller::~ApiCaller() = default;