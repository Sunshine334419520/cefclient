//
// Created by Sunshine on 2018/5/29.
//

#include "tests/cefsimple/render/simple_render.h"
#include "tests/cefsimple/render/simple_v_8_handle.h"

namespace simple {
namespace render {

 class RenderDelegate : public SimpleRenderApp::Delegate {
  public:
     RenderDelegate()
             : v8_handler_(make_cef_refptr<SimpleV8Handle>()) {}
     ~RenderDelegate() = default;

     virtual void OnContextCreated(CefRefPtr<SimpleRenderApp> app,
                                                    CefRefPtr<CefBrowser> browser,
                                                    CefRefPtr<CefFrame> frame,
                                                    CefRefPtr<CefV8Context> context) OVERRIDE {
         message_router_->OnContextCreated(browser, frame, context);

         CefRefPtr<CefV8Value> object = context->GetGlobal();

         CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("NativeLogin", v8_handler_);


         object->SetValue("NativeLogin", func, V8_PROPERTY_ATTRIBUTE_NONE);
     }

     void OnWebKitInitialized(CefRefPtr<SimpleRenderApp> app) OVERRIDE{

         CefMessageRouterConfig config;
         message_router_ = CefMessageRouterRendererSide::Create(config);

         std::string app_code =
                 "var app;"
                 "if (!app)"
                 "    app = {};"
                 "(function() {"
                 "    app.GetId = function() {"
                 "        native function GetId();"
                 "        return GetId();"
                 "    };"
                 "})();";
         CefRegisterExtension("v8/app", app_code, v8_handler_);
     }

     virtual void OnContextReleased(CefRefPtr<SimpleRenderApp> app,
                                   CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefV8Context> context) OVERRIDE {
         message_router_->OnContextReleased(browser, frame, context);

         if (v8_handler_.get())
             v8_handler_->Release();
     }

     bool OnProcessMessageReceived(CefRefPtr<SimpleRenderApp> app,
                                   CefRefPtr<CefBrowser> browser,
                                   CefProcessId source_process,
                                   CefRefPtr<CefProcessMessage> message)  OVERRIDE{
         const std::string message_name = message->GetName();
         if (message_name == "login_reply") {
             CefRefPtr<CefListValue> args = message->GetArgumentList();

             const int status =  args->GetInt(0);

             if (status == 0) {
                 CefRefPtr<CefFrame> frame = browser->GetMainFrame();
                 frame->ExecuteJavaScript("alert('Got Login Reply from Browser process')", frame->GetURL(), 0);
             }
         }
        return message_router_->OnProcessMessageReceived(browser,
                                                         source_process,
                                                         message);
     }
  private:
     CefRefPtr<SimpleV8Handle> v8_handler_;

     CefRefPtr<CefMessageRouterRendererSide> message_router_;
     IMPLEMENT_REFCOUNTING(RenderDelegate);

 };

 void CreateDelegate(SimpleRenderApp::DelegateSet &delegates) {
     delegates.insert(make_cef_refptr<RenderDelegate>());
 }

}
}

