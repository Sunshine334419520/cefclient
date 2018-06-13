//
// Created by Sunshine on 2018/6/7.
//

#include "include/cef_task.h"
#include "tests/cefsimple/browser/simple_url_request_client.h"

namespace simple {

static void SendUrlRequest(CefRefPtr<CefBrowser> browser);

class UrlRequestTask final : public CefTask {
 public:
    explicit UrlRequestTask(CefRefPtr<CefBrowser> browser)
        : browser_(browser) {}
    ~UrlRequestTask() = default;

    void Execute() OVERRIDE {
        SendUrlRequest(browser_);
    }

 private:
    CefRefPtr<CefBrowser> browser_;
    IMPLEMENT_REFCOUNTING(UrlRequestTask);
};

static void SendUrlRequest(CefRefPtr<CefBrowser> browser) {
   CefRefPtr<SimpleUrlRequestClient> request_client(make_cef_refptr<SimpleUrlRequestClient>
           (make_cef_refptr<PrintUrlResponseDataCallback>()));
   //const std::string url = "simple://tests/handler.html";
   const std::string url = "http://www.baidu.com/s?linux";

   /*
   const std::string upload_data = "wd=linux";

   CefRefPtr<CefPostData> post_data = CefPostData::Create();
   CefRefPtr<CefPostDataElement> element = CefPostDataElement::Create();
   element->SetToBytes(upload_data.size(), upload_data.c_str());
   post_data->AddElement(element);

   request_client->Post(browser, url, post_data);
    */
   request_client->Get(browser, url);
}

void SimpleUrlRequestTask(CefRefPtr<CefBrowser> browser) {
    if (!CefCurrentlyOn(TID_UI)) {
        CefRefPtr<UrlRequestTask> task(make_cef_refptr<UrlRequestTask>(browser));
        CefPostTask(TID_UI, task);
    }
    else {
        SendUrlRequest(browser);
    }
}

}
