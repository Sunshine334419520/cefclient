//
// Created by Sunshine on 2018/5/26.
//

#include "simple_render_app.h"
#include <iostream>

namespace simple {

SimpleRenderApp::SimpleRenderApp() {
    CreateDelegate(this->delegates_);
}

void SimpleRenderApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                       CefRefPtr<CefV8Context> context) {

   for (auto it : delegates_)
       it->OnContextCreated(this, browser, frame, context);
}

void SimpleRenderApp::OnWebKitInitialized() {

    for (auto it : delegates_)
        it->OnWebKitInitialized(this);
}

void SimpleRenderApp::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) {
    for (auto it : delegates_)
        it->OnRenderThreadCreated(this, extra_info);
}

void SimpleRenderApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
    for (auto it : delegates_)
        it->OnBrowserCreated(this, browser);
}

void SimpleRenderApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) {
    for (auto it : delegates_)
        it->OnBrowserDestroyed(this, browser);
}

CefRefPtr<CefLoadHandler> SimpleRenderApp::GetLoadHandler() {
    CefRefPtr<CefLoadHandler> load_handler;
    DelegateSet::iterator it = delegates_.begin();
    // return when load_handler no null.
    for ( ; it != delegates_.end() && !load_handler.get(); ++it)
        load_handler = (*it)->GetLoadHandler(this);

    return load_handler;
}

void SimpleRenderApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
                                        CefRefPtr<CefFrame> frame,
                                        CefRefPtr<CefV8Context> context) {

    for (auto it : delegates_)
        it->OnContextReleased(this, browser, frame, context);
}

void SimpleRenderApp::OnUncaughtException(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefV8Context> context,
                                          CefRefPtr<CefV8Exception> exception,
                                          CefRefPtr<CefV8StackTrace> stackTrace) {
    for (auto it : delegates_)
        it->OnUncaughtException(this, browser, frame, context,
                                exception, stackTrace);
}

void SimpleRenderApp::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
                                           CefRefPtr<CefFrame> frame,
                                           CefRefPtr<CefDOMNode> node) {
    for (auto it : delegates_)
        it->OnFocusedNodeChanged(this, browser, frame, node);
}

bool SimpleRenderApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                               CefProcessId source_process,
                                               CefRefPtr<CefProcessMessage> message) {

    DCHECK_EQ(source_process, PID_BROWSER);

    bool handled = false;
    DelegateSet::iterator it = delegates_.begin();

    // as long as have a Delegate manage that message of received.
    // handled value have ture, return
    for (; it != delegates_.end() && !handled; ++it)
        (*it)->OnProcessMessageReceived(this, browser, source_process, message);

    return handled;

}


}//namespace simple end;
