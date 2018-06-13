//
// Created by Sunshine on 2018/5/26.
//

#ifndef CEF_SIMPLE_BROWSER_APP_H
#define CEF_SIMPLE_BROWSER_APP_H

#include "tests/cefsimple/common/simple_app.h"
#include <set>

namespace simple {

class SimpleBrowserApp final : public SimpleApp, public CefBrowserProcessHandler {
 public:
    SimpleBrowserApp();

    ~SimpleBrowserApp() = default;

    class Delegate : public virtual CefBaseRefCounted {
     protected:
        // forbid Create a new implement, unless inheritance that.
        Delegate() = default;

        ~Delegate() = default;

     public:
        virtual void OnContextInitialized(CefRefPtr<SimpleBrowserApp> app) {}

        virtual void OnBeforeCommandLineProcessing(CefRefPtr<SimpleBrowserApp> app,
                                                   CefRefPtr<CefCommandLine> command_line) {}

        virtual void OnBeforeChildProcessLaunch(CefRefPtr<SimpleBrowserApp> app,
                                                CefRefPtr<CefCommandLine> command_line) {}

        virtual void OnRenderProcessThreadCreated(CefRefPtr<SimpleBrowserApp> app,
                                                  CefRefPtr<CefListValue> extra_info) {}
    };

    typedef std::set<CefRefPtr<SimpleBrowserApp::Delegate>> DelegateSet;


 private:
    // SimpleApp method and CefBrowserProcessHandler method to override.
    virtual void OnContextInitialized() OVERRIDE;

    virtual void OnBeforeCommandLineProcessing(const CefString &process_type,
                                               CefRefPtr<CefCommandLine> command_line) OVERRIDE;


    virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

    virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) OVERRIDE;

    virtual void OnScheduleMessagePumpWork(int64 delay_ms) OVERRIDE;

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
        return this;
    }

    // Create a Delegate to delegates
    static void CreateDelegate(DelegateSet &delegates);


 private:
    DelegateSet delegates_;

    // Let the SimpleBrowserApp class can using Smart point(CefRefPrt)
    IMPLEMENT_REFCOUNTING(SimpleBrowserApp);
    // Set for the SimpleBrowserApp class no no allow copy and assign
    DISALLOW_COPY_AND_ASSIGN(SimpleBrowserApp);

};

} //namespace simple end

#endif //CEF_SIMPLE_BROWSER_APP_H
