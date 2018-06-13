//
// Created by Sunshine on 2018/6/5.
//

#ifndef CEF_BROWSER_SIDE_JS_HANDLER_H
#define CEF_BROWSER_SIDE_JS_HANDLER_H

#include "include/wrapper/cef_message_router.h"

namespace simple {

 class BrowserSideJsHandler
         : public CefMessageRouterBrowserSide::Handler{
  public:
     BrowserSideJsHandler() = default;
     ~BrowserSideJsHandler() = default;

     bool OnQuery(CefRefPtr<CefBrowser> browser,
                  CefRefPtr<CefFrame> frame,
                  int64 query_id,
                  const CefString& request,
                  bool persistent,
                  CefRefPtr<Callback> callback) OVERRIDE;

     void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          int64 query_id) OVERRIDE;


};

}


#endif //CEF_BROWSER_SIDE_JS_HANDLER_H
