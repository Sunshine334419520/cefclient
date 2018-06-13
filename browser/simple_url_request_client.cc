//
// Created by Sunshine on 2018/6/7.
//

#include <iostream>
#include <fstream>

#include "simple_url_request_client.h"
#include "include/wrapper/cef_helpers.h"

namespace simple {

namespace {
const char kFileName[] = "url_request_result";
}

SimpleUrlRequestClient::SimpleUrlRequestClient(
        CefRefPtr<UrlRequestCompletionCallback> url_request_callback)
    : url_request_callback_(url_request_callback){
   CEF_REQUIRE_UI_THREAD();
}

void
SimpleUrlRequestClient::OnRequestComplete(CefRefPtr<CefURLRequest> request) {
    CEF_REQUIRE_UI_THREAD();

    if (url_request_callback_) {
        url_request_callback_->OnCompletion(request->GetRequestError(), data_.c_str());
    }
}

void
SimpleUrlRequestClient::OnUploadProgress(CefRefPtr<CefURLRequest> request,
                                         int64 current,
                                         int64 total) {

}

void
SimpleUrlRequestClient::OnDownloadProgress(CefRefPtr<CefURLRequest> request,
                                           int64 current,
                                           int64 total) {
    std::cout << "current = " << current << "total = " << total << std::endl;
}

void SimpleUrlRequestClient::OnDownloadData(CefRefPtr<CefURLRequest> request,
                                            const void *data,
                                            size_t data_length) {
    data_ += std::string(static_cast<const char*>(data), data_length);

}

void SimpleUrlRequestClient::Request(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefRequest> cef_request) {
    url_request_ = CefURLRequest::Create(cef_request, this, nullptr);
}

void SimpleUrlRequestClient::Get(CefRefPtr<CefBrowser> browser,
                                 const std::string &url,
                                 const CefRequest::HeaderMap &headers) {
    CefRefPtr<CefRequest> request = CefRequest::Create();
    request->SetMethod("GET");
    request->SetURL(url);
    request->SetHeaderMap(headers);

   // browser->GetMainFrame()->LoadRequest(request);

    Request(browser, request);
}

void SimpleUrlRequestClient::Post(CefRefPtr<CefBrowser> browser,
                                  const std::string &url,
                                  CefRefPtr<CefPostData> data,
                                  const CefRequest::HeaderMap &headers) {
    CefRefPtr<CefRequest> request = CefRequest::Create();
    request->SetMethod("POST");
    request->SetURL(url);
    request->SetPostData(data);
    request->SetHeaderMap(headers);

    browser->GetMainFrame()->LoadRequest(request);

    Request(browser, request);
}

void
PrintUrlResponseDataCallback::OnCompletion(CefURLRequest::ErrorCode error_code,
                                           const char *data) {

    std::ofstream out_file(kFileName, std::ios::out | std::ios::binary);

    out_file << data << std::endl;

    out_file.close();

    //std::cout << error_code << data << std::endl;
}

} // namespace simple
