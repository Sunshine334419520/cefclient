//
// Created by Sunshine on 2018/5/26.
//

#include "simple_browser_app.h"
#include "scheme_test.h"

#include <string>
//#include <memory>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "handler.h"
namespace simple {

SimpleBrowserApp::SimpleBrowserApp() {
    //CreateDelegate(delegates_);
}

class SimpleWindowDelegate : public CefWindowDelegate {
 public:
    explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
            : browser_view_(browser_view) {}

    void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE {
        // Add the browser view and show the window.
        window->AddChildView(browser_view_);
        window->Show();

        // Give keyboard focus to the browser view.
        browser_view_->RequestFocus();
    }

    void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE {
        browser_view_ = nullptr;
    }

    bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE {
        // Allow the window to close if the browser says it's OK.
        CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
        if (browser)
            return browser->GetHost()->TryCloseBrowser();
        return true;
    }

 private:
    CefRefPtr<CefBrowserView> browser_view_;

 IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
};



    void SimpleBrowserApp::OnContextInitialized() {
        CEF_REQUIRE_UI_THREAD();
        
        scheme_test::RegisterSchemeHandlers();

        CefRefPtr<CefCommandLine> command_line =
                CefCommandLine::GetGlobalCommandLine();

#if defined(OS_WIN) || defined(OS_LINUX)
        // Create the browser using the Views framework if "--use-views" is specified
  // via the command-line. Otherwise, create the browser using the native
  // platform framework. The Views framework is currently only supported on
  // Windows and Linux.
  const bool use_views = command_line->HasSwitch("use-views");
#else
        const bool use_views = false;
#endif

        // SimpleHandler implements browser-level callbacks.
        CefRefPtr<SimpleHandler> handler(make_cef_refptr<SimpleHandler>(use_views));


        // Specify CEF browser settings here.
        CefBrowserSettings browser_settings;

        std::string url;

        // Check if a "--url=" value was provided via the command-line. If so, use
        // that instead of the default URL.
        url = command_line->GetSwitchValue("url");
        if (url.empty())
            url = "file:///Users/sunshine/Other/cef_binary_3.3359.1772.gd1df190_macosx64/tests/cefsimple/cefsimple.html";

        if (use_views) {
            // Create the BrowserView.
            CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
                    handler, url, browser_settings, nullptr, nullptr);

            // Create the Window. It will show itself after creation.
            CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
        } else {
            // Information used when creating the native window.
            CefWindowInfo window_info;

#if defined(OS_WIN)
            // On Windows we need to specify certain flags that will be passed to
            // CreateWindowEx().
            window_info.SetAsPopup(NULL, "cefsimple");
#endif

            // Create the first browser window.
            CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
                                          nullptr);
        }
    }



void SimpleBrowserApp::OnBeforeCommandLineProcessing(const CefString &process_type,
                                                     CefRefPtr<CefCommandLine> command_line) {
    for (auto it : delegates_)
        it->OnBeforeCommandLineProcessing(this, command_line);

}

/*
void SimpleBrowserApp::OnContextInitialized() {
    for (auto it : delegates_)
        it->OnContextInitialized(this);
}
 */

void SimpleBrowserApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) {
    for (auto it : delegates_)
        it->OnBeforeChildProcessLaunch(this, command_line);

}

void SimpleBrowserApp::OnScheduleMessagePumpWork(int64 delay_ms) {

}

void SimpleBrowserApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) {
    for (auto it : delegates_)
        it->OnRenderProcessThreadCreated(this, extra_info);

}

}//namespace simple
