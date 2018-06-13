//
// Created by Sunshine on 2018/5/26.
//

#ifndef CEF_SIMPLE_RENDER_APP_H
#define CEF_SIMPLE_RENDER_APP_H

#include <set>

#include "tests/cefsimple/common/simple_app.h"
#include "simple_v_8_handle.h"
#include "include/wrapper/cef_message_router.h"

namespace simple {

class SimpleRenderApp final : public SimpleApp, public CefRenderProcessHandler {
 public:
    SimpleRenderApp();

    ~SimpleRenderApp() = default;

    class Delegate : public virtual CefBaseRefCounted {
     protected:
        Delegate() = default;
        ~Delegate() = default;

     public:
        virtual void OnRenderThreadCreated(CefRefPtr<SimpleRenderApp> app,
                                           CefRefPtr<CefListValue> extra_info) { }

        virtual void OnWebKitInitialized(CefRefPtr<SimpleRenderApp> app) { }

        virtual void OnBrowserCreated(CefRefPtr<SimpleRenderApp> app,
                                      CefRefPtr<CefBrowser> browser) { }

        virtual void OnBrowserDestroyed(CefRefPtr<SimpleRenderApp> app,
                                        CefRefPtr<CefBrowser> browser) { }

        virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<SimpleRenderApp> app) {
            return nullptr;
        }


        virtual void OnContextCreated(CefRefPtr<SimpleRenderApp> app,
                                      CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefV8Context> context) { }

        virtual void OnContextReleased(CefRefPtr<SimpleRenderApp> app,
                                       CefRefPtr<CefBrowser> browser,
                                       CefRefPtr<CefFrame> frame,
                                       CefRefPtr<CefV8Context> context) { }

        virtual void OnUncaughtException(CefRefPtr<SimpleRenderApp> app,
                                         CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefV8Context> context,
                                         CefRefPtr<CefV8Exception> exception,
                                         CefRefPtr<CefV8StackTrace> stackTrace) { }

        virtual void OnFocusedNodeChanged(CefRefPtr<SimpleRenderApp> app,
                                          CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefDOMNode> node) { }

        virtual bool OnProcessMessageReceived(CefRefPtr<SimpleRenderApp> app,
                                              CefRefPtr<CefBrowser> browser,
                                              CefProcessId source_process,
                                              CefRefPtr<CefProcessMessage> message) {
            return false;
        }

     private:
        IMPLEMENT_REFCOUNTING(Delegate);
        DISALLOW_COPY_AND_ASSIGN(Delegate);


    };

    typedef std::set<CefRefPtr<SimpleRenderApp::Delegate>> DelegateSet;

 private:

    static void CreateDelegate(DelegateSet& delegates);

    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {
        return this;
    };

    virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) OVERRIDE;

    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefRefPtr<CefV8Context> context) OVERRIDE;

    virtual void OnWebKitInitialized() OVERRIDE;

    virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) OVERRIDE;

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

    virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) OVERRIDE;

    virtual void OnUncaughtException(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefFrame> frame,
                                     CefRefPtr<CefV8Context> context,
                                     CefRefPtr<CefV8Exception> exception,
                                     CefRefPtr<CefV8StackTrace> stackTrace) OVERRIDE;

    virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefDOMNode> node) OVERRIDE;

    virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                          CefProcessId source_process,
                                          CefRefPtr<CefProcessMessage> message) OVERRIDE;



 private:
    DelegateSet delegates_;     //save

    CefRefPtr<SimpleV8Handle> v8_handler_;



    IMPLEMENT_REFCOUNTING(SimpleRenderApp);
    DISALLOW_COPY_AND_ASSIGN(SimpleRenderApp);

};

} // namespace simple end


#endif //CEF_SIMPLE_RENDER_APP_H
