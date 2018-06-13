//
// Created by Sunshine on 2018/5/27.
//

#include "simple_v_8_handle.h"
#include <iostream>

namespace simple {
    namespace {
    const char KNativeLogin[] = "NativeLogin";
    const char KGetId[] = "GetId";
    }

    bool SimpleV8Handle::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                                 CefRefPtr<CefV8Value> &retval, CefString &exception)
    {
        if (name == KNativeLogin) {
            if (arguments.size() == 2 && arguments[0]->IsString()
                && arguments[1]->IsString()) {
                CefString user = arguments.at(0)->GetStringValue();
                CefString password = arguments.at(1)->GetStringValue();

                CefRefPtr<CefFrame> frame = CefV8Context::GetCurrentContext()
                                            ->GetBrowser()->GetMainFrame();
                frame->ExecuteJavaScript("alert(user, password, 'Hello, NativeLogin .')",
                                         frame->GetURL(), 0);

                CefRefPtr<CefProcessMessage> mesg = CefProcessMessage::Create("login_msg");
                CefRefPtr<CefListValue> args = mesg->GetArgumentList();

                args->SetSize(2);
                args->SetString(0, user);
                args->SetString(1, password);

                CefV8Context::GetCurrentContext()->GetBrowser()->SendProcessMessage(PID_BROWSER, mesg);

                retval = CefV8Value::CreateInt(0);
            } else {
                retval = CefV8Value::CreateInt(2);
            }
            return true;
        } else if (name == KGetId) {
            if (arguments.size() == 0) {
                CefRefPtr<CefFrame> frame = CefV8Context::GetCurrentContext()
                        ->GetBrowser()->GetMainFrame();
                frame->ExecuteJavaScript("alert('Hello, I came from native world.')",
                                         frame->GetURL(), 0);

                retval = CefV8Value::CreateString("YangGuang");
                return true;
            }
        }

        return false;
    }
}
