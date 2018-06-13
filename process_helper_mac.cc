// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "include/cef_app.h"


#include "tests/cefsimple/common/simple_other_app.h"
#include "tests/cefsimple/render/simple_render_app.h"
#include "include/cef_command_line.h"

namespace simple {

    int RunMain(int argc, char* argv[]) {
      CefMainArgs main_args(argc, argv);

      // Parse command-line arguments.
      CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
      command_line->InitFromArgv(argc, argv);

      // Create a SimpleApp of the correct type.
      CefRefPtr<CefApp> app;
      SimpleApp::ProcessType process_type = SimpleApp::GetProcessType(command_line);
      if (process_type == SimpleApp::RenderProcess)
        app = new SimpleRenderApp();
      else if (process_type == SimpleApp::OtherProcess)
        app = new SimpleOtherApp();

      // Execute the secondary process.
      return CefExecuteProcess(main_args, app, NULL);
    }

}  // namespace client

// Entry point function for sub-processes.
int main(int argc, char* argv[]) {
    return simple::RunMain(argc, argv);
}
