//
// Created by Sunshine on 2018/5/29.
//

#include "tests/cefsimple/browser/simple_browser.h"

namespace simple {
namespace browser {

 class SimpleBrowserDelegate : public SimpleBrowserApp::Delegate {
  public:
     SimpleBrowserDelegate() = default;
     ~SimpleBrowserDelegate() = default;

  private:
     IMPLEMENT_REFCOUNTING(SimpleBrowserDelegate);
     DISALLOW_COPY_AND_ASSIGN(SimpleBrowserDelegate);
 };

 void CreateDelegate(SimpleBrowserApp::DelegateSet& delegates) {
     delegates.insert(make_cef_refptr<SimpleBrowserDelegate>());
 }

}
}

