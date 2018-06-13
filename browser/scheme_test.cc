//
// Created by Sunshine on 2018/6/11.
//

#include "tests/cefsimple/browser/scheme_test.h"
#include "tests/cefsimple/browser/resource_util.h"

#include <string>
#include <algorithm>

#include "include/cef_resource_handler.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_scheme.h"

namespace simple {
namespace scheme_test {

namespace {

class SimpleSchemeHandler final : public CefResourceHandler {
 public:
    SimpleSchemeHandler() : offset_(0) {}

    bool ProcessRequest(CefRefPtr<CefRequest> request,
                        CefRefPtr<CefCallback> callback) OVERRIDE {
       CEF_REQUIRE_IO_THREAD();

       bool handled = false;

       const std::string url = request->GetURL();
       if (strstr(url.c_str(), "handler.html") != nullptr) {
           data_ =
                   "<html><head><title>Client Scheme Handler</title></head>"
                   "<body bgcolor=\"white\">"
                   "This contents of this page page are served by the "
                   "ClientSchemeHandler class handling the client:// protocol."
                   "<br/>You should see an image:"
                   "<br/><img src=\"client://tests/logo.png\"><pre>";

           data_.append(
                   "</pre><br/>Try the test form:"
                   "<form method=\"POST\" action=\"handler.html\">"
                   "<input type=\"text\" name=\"field1\">"
                   "<input type=\"text\" name=\"field2\">"
                   "<input type=\"submit\">"
                   "</form></body></html>");

           handled = true;

           mine_type_ = "text/html";
       }
       else if (strstr(url.c_str(), "logo.png") != nullptr) {
          if (LoadBinaryResource("logo.png", data_)) {
              handled = true;

              mine_type_ = "image/png";
          }
       }


       if (handled) {
           callback->Continue();
           return true;
       }

       return false;
    }

    void GetResponseHeaders(CefRefPtr<CefResponse> response,
                             int64& response_lentgh,
                             CefString& redirectUrl) OVERRIDE {
        CEF_REQUIRE_IO_THREAD();

        DCHECK(!data_.empty());

        response->SetMimeType(mine_type_);
        response->SetStatus(200);

        response_lentgh = data_.length();
    }

    void Cancel() OVERRIDE { CEF_REQUIRE_IO_THREAD(); }

    bool ReadResponse(void* data_out,
                      int bytes_to_read,
                      int& bytes_read,
                      CefRefPtr<CefCallback> callback) OVERRIDE {
        CEF_REQUIRE_IO_THREAD();

        bool has_data = false;

        bytes_read = 0;

        if (offset_ < data_.length()) {
            size_t transfer_size =
                    (size_t) std::min(static_cast<int>(data_.length() - offset_), bytes_to_read);

            memcpy(data_out, data_.c_str() + offset_, transfer_size);
            offset_ += transfer_size;
            bytes_read = transfer_size;

            has_data = true;
        }

        return has_data;
    }

 private:
    std::string data_;
    std::string mine_type_;
    std::size_t offset_;

    IMPLEMENT_REFCOUNTING(SimpleSchemeHandler);
};


class SimpleSchemeHandlerFactory final : public CefSchemeHandlerFactory {
 public:
    // Return a new scheme handler instance to handle the request.
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         const CefString& scheme_name,
                                         CefRefPtr<CefRequest> request) OVERRIDE {
        CEF_REQUIRE_IO_THREAD();
        return make_cef_refptr<SimpleSchemeHandler>();
    }

    IMPLEMENT_REFCOUNTING(SimpleSchemeHandlerFactory);
};
}   //namespace

void RegisterSchemeHandlers() {
    CefRegisterSchemeHandlerFactory("simple", "tests",
                                    make_cef_refptr<SimpleSchemeHandlerFactory>());
}

}   // namespace scheme_test
}   // namespace simple

