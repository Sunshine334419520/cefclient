//
// Created by Sunshine on 2018/5/27.
//

#ifndef CEF_SIMPLE_V_8_HANDLE_H
#define CEF_SIMPLE_V_8_HANDLE_H

#include "include/cef_v8.h"

namespace simple {

    class SimpleV8Handle : public CefV8Handler {
    public:
        SimpleV8Handle() = default;
        ~SimpleV8Handle() = default;

        virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval,
                             CefString& exception) OVERRIDE;

        IMPLEMENT_REFCOUNTING(SimpleV8Handle);
    };

} //namespace simple end

#endif //CEF_SIMPLE_V_8_HANDLE_H
