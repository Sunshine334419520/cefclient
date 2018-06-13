//
// Created by Sunshine on 2018/5/29.
//

#include "tests/cefsimple/browser/simple_browser_app.h"
#include "tests/cefsimple/browser/simple_browser.h"

namespace simple {

void SimpleBrowserApp::CreateDelegate(SimpleBrowserApp::DelegateSet &delegates) {
    browser::CreateDelegate(delegates);
}

} //namespace simple end
