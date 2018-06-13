//
// Created by Sunshine on 2018/5/27.
//

#ifndef CEF_SIMPLE_OTHER_APP_H
#define CEF_SIMPLE_OTHER_APP_H

#include "tests/cefsimple/common/simple_app.h"

namespace simple {

class SimpleOtherApp final : public SimpleApp {
 public:
    SimpleOtherApp() = default;

    ~SimpleOtherApp() = default;

 IMPLEMENT_REFCOUNTING(SimpleOtherApp);

};

} // namespce simple end


#endif //CEF_SIMPLE_OTHER_APP_H
