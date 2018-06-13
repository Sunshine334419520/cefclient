//
// Created by Sunshine on 2018/6/5.
//

#include "browser_side_js_handler.h"

namespace simple {

namespace {

const char kHelloCefQuery[] = "HelloCefQuery";
const char kGiveMemoney[] = "GiveMemoney";

}

bool BrowserSideJsHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   int64 query_id,
                                   const CefString &request,
                                   bool persistent,
                                   CefRefPtr<CefMessageRouterBrowserSide::Callback> callback) {
    if (request == kHelloCefQuery) {
        callback->Success("HelloCefQuery OK!");
        return true;
    }
    else if (request == kGiveMemoney) {
        callback->Failure(404, "There are none thus query!");
        return true;
    }

    return false;
}

void BrowserSideJsHandler::OnQueryCanceled(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           int64 query_id) {
}

}
