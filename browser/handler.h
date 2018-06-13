// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"

#include <list>
#include <set>

namespace simple {

void SimpleUrlRequestTask(CefRefPtr<CefBrowser>);

class SimpleHandler : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
                      public CefRequestHandler {
 public:
    explicit SimpleHandler(bool use_views);

    ~SimpleHandler();

    // Provide access to the single global instance of this object.
    static SimpleHandler *GetInstance();

    // CefClient methods:
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
      return this;
    }

    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
      return this;
    }

    CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }

    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) OVERRIDE;


    // CefDisplayHandler methods:
    void OnTitleChange(CefRefPtr<CefBrowser> browser,
                       const CefString &title) OVERRIDE;

    // CefLifeSpanHandler methods:


    void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

    bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods:
    void OnLoadError(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     ErrorCode errorCode,
                     const CefString &errorText,
                     const CefString &failedUrl) OVERRIDE;

    // CefRequestHandler methods.
    bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefFrame> frame,
                        CefRefPtr<CefRequest> request,
                        bool user_gesture,
                        bool is_redirect) OVERRIDE;

    void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                   TerminationStatus status) OVERRIDE;

    // Request that all existing browser windows close.
    void CloseAllBrowsers(bool force_close);

    bool IsClosing() const { return is_closing_; }

    typedef std::set<CefMessageRouterBrowserSide::Handler *> MessageHandlerSet;

 private:
    // Platform-specific implementation.
    void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString &title);

    void CreateMessageHandlers(MessageHandlerSet &message_handler_set);

    // True if the application is using the Views framework.
    const bool use_views_;

    // List of existing browser windows. Only accessed on the CEF UI thread.
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;

    CefRefPtr<CefMessageRouterBrowserSide> message_router_;


    MessageHandlerSet message_handler_set_;

    bool is_closing_;

    // Include the default reference counting implementation.
 IMPLEMENT_REFCOUNTING(SimpleHandler);
};

} // namespace simple

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
