
#include "tests/cefsimple/browser/resource_util.h"

#import <Foundation/Foundation.h>
#include <mach-o/dyld.h>
#include <stdio.h>

#include "include/base/cef_logging.h"

namespace simple {

namespace {

// Implementation adapted from Chromium's base/mac/foundation_util.mm
bool UncachedAmIBundled() {
    return [[[NSBundle mainBundle] bundlePath] hasSuffix:@".app"];
}

bool AmIBundled() {
    static bool am_i_bundled = UncachedAmIBundled();
    return am_i_bundled;
}

}  // namespace

// Implementation adapted from Chromium's base/base_path_mac.mm
bool GetResourceDir(std::string& dir) {
    // Retrieve the executable directory.
    uint32_t pathSize = 0;
    _NSGetExecutablePath(NULL, &pathSize);
    if (pathSize > 0) {
        dir.resize(pathSize);
        _NSGetExecutablePath(const_cast<char*>(dir.c_str()), &pathSize);
    }

    if (AmIBundled()) {
        // Trim executable name up to the last separator.
        std::string::size_type last_separator = dir.find_last_of("/");
        dir.resize(last_separator);
        dir.append("/../Resources");
        return true;
    }

    dir.append("/Resources");
    return true;
}

}  // namespace client

