//
// Created by Sunshine on 2018/5/30.
//

#ifndef CEF_SIMPLE_HANDLER_H
#define CEF_SIMPLE_HANDLER_H

#include <set>
#include <vector>

#include "include/wrapper/cef_message_router.h"
#include "include/wrapper/cef_resource_manager.h"
#include "include/cef_client.h"

namespace simple {

 class SimpleHandler final : public CefClient,
                             public CefContextMenuHandler,
                             public CefDisplayHandler,
                             public CefLoadHandler,
                             public CefLifeSpanHandler,
                             public CefDownloadHandler,
                             public CefDragHandler,
                             public CefFocusHandler,
                             public CefKeyboardHandler,
                             public CefRequestHandler {
  public:
     class Delegate;

     SimpleHandler(Delegate* delegate,
                   bool is_off_screen,
                   const std::string& startup_url);
     ~SimpleHandler() = default;

     class Delegate {
      protected:
         Delegate() = default;
         virtual ~Delegate() = default;
      public:
         // Called when the browser is created.
         virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) = 0;

         // Called when the browser is closing.
         virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser) = 0;

         // Called when the browser been closing.
         virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser) = 0;

         // Set the window URL adress.
         virtual void OnSetAdress(const CefString& url) = 0;

         // Set the window title.
         virtual void OnSetTitle(const CefString& title) = 0;

         // Set the Favicon image.
         virtual void OnSetFavicon(CefRefPtr<CefImage> image) = 0;

         // Set the fullscreen. fullscreen if true, otherwise no fullscreen.
         virtual void OnSetFullscreen(bool fullscreen) = 0;

         // auto-resize contents.
         virtual void OnAutoResize(const CefSize& new_size) = 0;

         // Set the loading state.
         virtual void OnSetLoadingState(bool is_loading, bool can_go_back,
                                      bool can_go_forward) = 0;

         // Set the draggable reginons.
         virtual void
         OnSetDraggableRegions(const std::vector<CefDraggableRegion>& regions) = 0;

         // Set focus to the next or previous control. [next] if true to next,
         // otherwise to previous.
         virtual void OnTakeFocus(bool next) = 0;

         // Calld on the UI thread before a context is a displayd.
         virtual void OnBeforeContextMenu(CefRefPtr<CefMenuModel> model) = 0;

     };

     typedef std::set<CefMessageRouterBrowserSide::Handler*> MessageHandlerSet;

     // This object may outlive the Delegate object so it's necessary for the
     // Delegate to detach itself before destruction.
     void DetachDelegate();

     // cefclient methods.
     CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() OVERRIDE{
         return this;
     }

     CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefDownloadHandler> GetDownloadHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefFocusHandler> GetFocusHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() OVERRIDE {
         return this;
     }

     CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE {
         return this;
     }

     // CefContextMenuHandler methods
     void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefContextMenuParams> params,
                              CefRefPtr<CefMenuModel> model) OVERRIDE;
     bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefContextMenuParams> params,
                               int command_id,
                               EventFlags event_flags) OVERRIDE;

     // CefDisPlayHandler methods.
     void OnAddressChange(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          const CefString& url) OVERRIDE;
     void OnTitleChange(CefRefPtr<CefBrowser> browser,
                        const CefString& title) OVERRIDE;
     void OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
                             const std::vector<CefString>& icon_urls) OVERRIDE;
     void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
                                 bool fullscreen) OVERRIDE;
     bool OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                           cef_log_severity_t level,
                           const CefString& message,
                           const CefString& source,
                           int line) OVERRIDE;
     bool OnAutoResize(CefRefPtr<CefBrowser> browser,
                       const CefSize& new_size) OVERRIDE;

     // CefLoadHandler methods
     void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                               bool isLoading,
                               bool canGoBack,
                               bool canGoForward) OVERRIDE;
     void OnLoadError(CefRefPtr<CefBrowser> browser,
                      CefRefPtr<CefFrame> frame,
                      ErrorCode errorCode,
                      const CefString& errorText,
                      const CefString& failedUrl) OVERRIDE;

     // CefLifeSpanHandler methods
     bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefFrame> frame,
                        const CefString& target_url,
                        const CefString& target_frame_name,
                        CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                        bool user_gesture,
                        const CefPopupFeatures& popupFeatures,
                        CefWindowInfo& windowInfo,
                        CefRefPtr<CefClient>& client,
                        CefBrowserSettings& settings,
                        bool* no_javascript_access) OVERRIDE;

     void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
     bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
     void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

     // CefDownloadHandler methods.
     void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefDownloadItem> download_item,
                           const CefString& suggested_name,
                           CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;
     void OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefDownloadItem> download_item,
                            CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

     // CefDragHandler methods
     bool OnDragEnter(CefRefPtr<CefBrowser> browser,
                      CefRefPtr<CefDragData> dragData,
                      CefDragHandler::DragOperationsMask mask) OVERRIDE;
     void OnDraggableRegionsChanged(
             CefRefPtr<CefBrowser> browser,
             const std::vector<CefDraggableRegion>& regions) OVERRIDE;

     // CefFocusHandler methods
     void OnTakeFocus(CefRefPtr<CefBrowser> browser, bool next) OVERRIDE;

     // CefKeyboardHandler methods
     bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                        const CefKeyEvent& event,
                        CefEventHandle os_event,
                        bool* is_keyboard_shortcut) OVERRIDE;

     // CefRequestHandler methods
     bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefFrame> frame,
                         CefRefPtr<CefRequest> request,
                         bool user_gesture,
                         bool is_redirect) OVERRIDE;

     bool
     OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
                      CefRefPtr<CefFrame> frame,
                      const CefString& target_url,
                      CefRequestHandler::WindowOpenDisposition target_disposition,
                      bool user_gesture) OVERRIDE;
     cef_return_value_t
     OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          CefRefPtr<CefRequest> request,
                          CefRefPtr<CefRequestCallback> callback) OVERRIDE;

     CefRefPtr<CefResourceHandler>
     GetResourceHandler(CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefFrame> frame,
                        CefRefPtr<CefRequest> request) OVERRIDE;

     CefRefPtr<CefResponseFilter>
     GetResourceResponseFilter(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefRequest> request,
                               CefRefPtr<CefResponse> response) OVERRIDE;

     bool OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                         const CefString& origin_url,
                         int64 new_size,
                         CefRefPtr<CefRequestCallback> callback) OVERRIDE;

     void OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                              const CefString& url,
                              bool& allow_os_execution) OVERRIDE;

     bool OnCertificateError(CefRefPtr<CefBrowser> browser,
                             ErrorCode cert_error,
                             const CefString& request_url,
                             CefRefPtr<CefSSLInfo> ssl_info,
                             CefRefPtr<CefRequestCallback> callback) OVERRIDE;

     bool
     OnSelectClientCertificate(CefRefPtr<CefBrowser> browser,
                               bool isProxy,
                               const CefString& host,
                               int port,
                               const X509CertificateList& certificates,
                               CefRefPtr<CefSelectClientCertificateCallback> callback) OVERRIDE;

     void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                    TerminationStatus status) OVERRIDE;

  public:
     // Returns the number of browser currently using this handler.
     // Can only be on the CEF UI thread.
     int GetBrowserCount() const noexcept;

     // Show a new DevTools popup window.
     void ShowDevTools(CefRefPtr<CefBrowser> browser,
                       const CefPoint& inspect_element_at) noexcept;

     // Close the existing DevTools popup window, if any.
     void CloseDevTools(CefRefPtr<CefBrowser> browser) noexcept ;

     // Test if the current site has SSL information available.
     bool HasSSLInformation(CefRefPtr<CefBrowser> browser) noexcept ;

     // Show SSL information for the current site.
     void ShowSSLInformation(CefRefPtr<CefBrowser> browser) noexcept;

     // Return the delegate
     Delegate* delegate() const noexcept { return delegate_; }

     //Return the startup url.
     std::string startup_url() const noexcept { return startup_url_; }

     // Return the off-screen.
     bool is_off_screen() const noexcept { return is_off_screen_; }

     // Return the download_favicon_images.
     bool download_favicon_images() const noexcept { return download_favicon_images_; }

     // Set the download_favicon_images, [allow] if true, download the favicon images.
     void SetDownloadFaviconImages(bool allow) noexcept {
         download_favicon_images_ = allow;
     }

  private:
     // Create a new popup window using the specified information. |is_devtools|
     // will be true if the window will be used for DevTools. Return true to
     // proceed with popup browser creation or false to cancel the popup browser.
     // May be called on any thead.
     bool CreatePopupWindow(CefRefPtr<CefBrowser> browser,
                            bool is_devtools,
                            const CefPopupFeatures& popupFeatures,
                            CefWindowInfo& windowInfo,
                            CefRefPtr<CefClient>& client,
                            CefBrowserSettings& settings);


     // Execute Delegate notifications on the main thread.
     void NotifyBrowserCreated(CefRefPtr<CefBrowser> browser);
     void NotifyBrowserClosing(CefRefPtr<CefBrowser> browser);
     void NotifyBrowserClosed(CefRefPtr<CefBrowser> browser);
     void NotifyAddress(const CefString& url);
     void NotifyTitle(const CefString& title);
     void NotifyFavicon(CefRefPtr<CefImage> image);
     void NotifyFullscreen(bool fullscreen);
     void NotifyAutoResize(const CefSize& new_size);
     void NotifyLoadingState(bool isLoading, bool canGoBack, bool canGoForward);
     void NotifyDraggableRegions(const std::vector<CefDraggableRegion>& regions);
     void NotifyTakeFocus(bool next);

     // Test context menu creation.
     void BuildTestMenu(CefRefPtr<CefMenuModel> model);
     bool ExecuteTestMenu(int command_id);

  private:
     // THREAD SAFE MEMBERS
     // The following members may be accessed from any thread.

     // true if this handler used off-screen rendering.
     const bool is_off_screen_;

     //startup url adress.
     const std::string startup_url_;

     // if true to this mouse cursor change is disable.
     bool mouse_cursor_change_disable_;

     // if true to download the favicon images.
     bool download_favicon_images_;

     // Handlers to browser side of query route.
     CefRefPtr<CefMessageRouterBrowserSide> message_router_;

     // Manages the registration and delivery of resources.
     CefRefPtr<CefResourceManager> resource_manager_;

     // MAIN THREAD MEMBERS
     // The following members will only be accessed on the main thread. This will
     // be the same as the CEF UI thread except when using multi-threaded message
     // loop mode on Windows.

     Delegate* delegate_;

     // UI THREAD MEMBERS
     // The following members will only be accessed on the CEF UI thread.

     // The current number of browsers using this handler.
     int browser_count_;

     // Set of Handlers registered with the message router.
     MessageHandlerSet message_handler_set_;

     DISALLOW_COPY_AND_ASSIGN(SimpleHandler);

};

}


#endif //CEF_SIMPLE_HANDLER_H
