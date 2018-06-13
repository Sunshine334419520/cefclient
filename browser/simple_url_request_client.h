//
// Created by Sunshine on 2018/6/7.
//

#ifndef CEF_SIMPLE_URL_REQUEST_CLIENT_H
#define CEF_SIMPLE_URL_REQUEST_CLIENT_H

#include <string>

#include "include/cef_urlrequest.h"
#include "include/cef_base.h"

namespace simple {



class UrlRequestCompletionCallback : public virtual CefBaseRefCounted {
 protected:
    UrlRequestCompletionCallback() = default;
    ~UrlRequestCompletionCallback() = default;
 public:
    virtual void OnCompletion(CefURLRequest::ErrorCode error_code,
                              const char* data) = 0;

 private:
    IMPLEMENT_REFCOUNTING(UrlRequestCompletionCallback);
    DISALLOW_COPY_AND_ASSIGN(UrlRequestCompletionCallback);
};

class SimpleUrlRequestClient : public CefURLRequestClient {
 public:
    explicit SimpleUrlRequestClient(CefRefPtr<UrlRequestCompletionCallback>
                                    url_request_callback = nullptr);

    // CefURLRequestClient methods.
    void OnRequestComplete(CefRefPtr<CefURLRequest> request) OVERRIDE;

    void OnUploadProgress(CefRefPtr<CefURLRequest> request,
                          int64 current,
                          int64 total) OVERRIDE;

    void OnDownloadProgress(CefRefPtr<CefURLRequest> request,
                            int64 current,
                            int64 total) OVERRIDE;

    void OnDownloadData(CefRefPtr<CefURLRequest> request,
                        const void* data,
                        size_t data_length) OVERRIDE;

    bool GetAuthCredentials(bool isProxy,
                            const CefString& host,
                            int port,
                            const CefString& realm,
                            const CefString& scheme,
                            CefRefPtr<CefAuthCallback> callback) OVERRIDE{
        return false;
    }

    void Request(CefRefPtr<CefBrowser> browser, CefRefPtr<CefRequest> cef_request);
    void Get(CefRefPtr<CefBrowser> browser,
             const std::string& url,
             const CefRequest::HeaderMap& headers = CefRequest::HeaderMap());
    void Post(CefRefPtr<CefBrowser> browser,
              const std::string& url,
              CefRefPtr<CefPostData> data,
              const CefRequest::HeaderMap& headers = CefRequest::HeaderMap());


 private:
    CefRefPtr<CefURLRequest> url_request_;
    CefRefPtr<UrlRequestCompletionCallback> url_request_callback_;
    std::string data_;

    IMPLEMENT_REFCOUNTING(SimpleUrlRequestClient);
    DISALLOW_COPY_AND_ASSIGN(SimpleUrlRequestClient);
};

class PrintUrlResponseDataCallback final : public UrlRequestCompletionCallback {
 public:
    PrintUrlResponseDataCallback() = default;
    ~PrintUrlResponseDataCallback() final = default;
    void OnCompletion(CefURLRequest::ErrorCode error_code,
                      const char* data) OVERRIDE;

 private:
    IMPLEMENT_REFCOUNTING(PrintUrlResponseDataCallback);
    DISALLOW_COPY_AND_ASSIGN(PrintUrlResponseDataCallback);
};

}


#endif //CEF_SIMPLE_URL_REQUEST_CLIENT_H
