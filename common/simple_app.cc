// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"
#include "include/cef_command_line.h"

#include <string>


namespace simple {

namespace {
const char KProcessType[] = "type";
const char KRenderProcess[] = "renderer";
} //namespace

SimpleApp::ProcessType SimpleApp::GetProcessType(CefRefPtr<CefCommandLine> command_line) {
    if (!command_line->HasSwitch(KProcessType))
        return ProcessType::BrowserProcess;


    const std::string process_type = command_line->GetSwitchValue(KProcessType);
    if (process_type == KRenderProcess)
        return ProcessType::RenderProcess;
    else
        return ProcessType::OtherProcess;
}

void SimpleApp::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
    registrar->AddCustomScheme("simple", true, false, false, false, true, false);
}

} //namespace simple end
