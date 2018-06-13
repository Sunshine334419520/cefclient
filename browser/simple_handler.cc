//
// Created by Sunshine on 2018/5/30.
//

#include "simple_handler.h"

namespace simple {

SimpleHandler::SimpleHandler(SimpleHandler::Delegate *delegate,
                             bool is_off_screen,
                             const std::string& startup_url)
    : is_off_screen_(is_off_screen),
      startup_url_(startup_url),
      download_favicon_images_(false),
      delegate_(delegate),
      browser_count_(0){

}

void SimpleHandler::DetachDelegate() {

}

void
SimpleHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefContextMenuParams> params,
                                   CefRefPtr<CefMenuModel> model) {
    CefContextMenuHandler::OnBeforeContextMenu(browser, frame, params, model);
}

bool
SimpleHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefContextMenuParams> params,
                                    int command_id,
                                    CefContextMenuHandler::EventFlags event_flags) {
    return CefContextMenuHandler::OnContextMenuCommand(browser, frame, params, command_id, event_flags);
}

void SimpleHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    const CefString &url) {
    CefDisplayHandler::OnAddressChange(browser, frame, url);
}

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString &title) {
    CefDisplayHandler::OnTitleChange(browser, title);
}

void
SimpleHandler::OnFaviconURLChange(CefRefPtr<CefBrowser> browser,
                                  const std::vector<CefString> &icon_urls) {
    CefDisplayHandler::OnFaviconURLChange(browser, icon_urls);
}

void SimpleHandler::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser,
                                           bool fullscreen) {
    CefDisplayHandler::OnFullscreenModeChange(browser, fullscreen);
}

bool SimpleHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
                                     cef_log_severity_t level,
                                     const CefString &message,
                                     const CefString &source,
                                     int line) {
    return CefDisplayHandler::OnConsoleMessage(browser, level, message, source, line);
}

bool SimpleHandler::OnAutoResize(CefRefPtr<CefBrowser> browser,
                                 const CefSize &new_size) {
    return CefDisplayHandler::OnAutoResize(browser, new_size);
}

void
SimpleHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                    bool isLoading,
                                    bool canGoBack,
                                    bool canGoForward) {
    CefLoadHandler::OnLoadingStateChange(browser, isLoading, canGoBack, canGoForward);
}

void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                CefLoadHandler::ErrorCode errorCode,
                                const CefString &errorText,
                                const CefString &failedUrl) {
    CefLoadHandler::OnLoadError(browser, frame, errorCode, errorText, failedUrl);
}

bool SimpleHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  const CefString &target_url,
                                  const CefString &target_frame_name,
                                  CefLifeSpanHandler::WindowOpenDisposition target_disposition,
                                  bool user_gesture,
                                  const CefPopupFeatures &popupFeatures,
                                  CefWindowInfo &windowInfo,
                                  CefRefPtr<CefClient> &client,
                                  CefBrowserSettings &settings,
                                  bool *no_javascript_access) {
    return CefLifeSpanHandler::OnBeforePopup(browser, frame, target_url, target_frame_name, target_disposition,
                                             user_gesture, popupFeatures, windowInfo, client, settings,
                                             no_javascript_access);
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CefLifeSpanHandler::OnAfterCreated(browser);
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    return CefLifeSpanHandler::DoClose(browser);
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CefLifeSpanHandler::OnBeforeClose(browser);
}

void SimpleHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
                                     CefRefPtr<CefDownloadItem> download_item,
                                     const CefString &suggested_name,
                                     CefRefPtr<CefBeforeDownloadCallback> callback) {

}

void SimpleHandler::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefDownloadItem> download_item,
                                      CefRefPtr<CefDownloadItemCallback> callback) {
    CefDownloadHandler::OnDownloadUpdated(browser, download_item, callback);
}

bool SimpleHandler::OnDragEnter(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefDragData> dragData,
                                CefDragHandler::DragOperationsMask mask) {
    return CefDragHandler::OnDragEnter(browser, dragData, mask);
}

void SimpleHandler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser,
                                              const std::vector<CefDraggableRegion> &regions) {
    CefDragHandler::OnDraggableRegionsChanged(browser, regions);
}

void SimpleHandler::OnTakeFocus(CefRefPtr<CefBrowser> browser,
                                bool next) {
    CefFocusHandler::OnTakeFocus(browser, next);
}

bool SimpleHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                  const CefKeyEvent &event,
                                  NSEvent *os_event,
                                  bool *is_keyboard_shortcut) {
    return CefKeyboardHandler::OnPreKeyEvent(browser, event, os_event, is_keyboard_shortcut);
}

bool
SimpleHandler::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefRequest> request,
                              bool user_gesture, bool is_redirect) {
    return CefRequestHandler::OnBeforeBrowse(browser, frame, request, user_gesture, is_redirect);
}



bool
SimpleHandler::OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                const CefString &target_url,
                                CefRequestHandler::WindowOpenDisposition \
                                target_disposition,
                                bool user_gesture) {
    return CefRequestHandler::OnOpenURLFromTab(browser, frame, target_url, target_disposition, user_gesture);
}

cef_return_value_t
SimpleHandler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefRequest> request,
                                    CefRefPtr<CefRequestCallback> callback) {
    return CefRequestHandler::OnBeforeResourceLoad(browser, frame, request, callback);
}

CefRefPtr<CefResourceHandler>
SimpleHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                  CefRefPtr<CefFrame> frame,
                                  CefRefPtr<CefRequest> request) {
    return CefRequestHandler::GetResourceHandler(browser, frame, request);
}

CefRefPtr<CefResponseFilter>
SimpleHandler::GetResourceResponseFilter(CefRefPtr<CefBrowser> browser,
                                         CefRefPtr<CefFrame> frame,
                                         CefRefPtr<CefRequest> request,
                                         CefRefPtr<CefResponse> response) {
    return CefRequestHandler::GetResourceResponseFilter(browser, frame, request, response);
}

bool SimpleHandler::OnQuotaRequest(CefRefPtr<CefBrowser> browser,
                                   const CefString &origin_url,
                                   int64 new_size,
                                   CefRefPtr<CefRequestCallback> callback) {
    return CefRequestHandler::OnQuotaRequest(browser, origin_url, new_size, callback);
}

void SimpleHandler::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
                                        const CefString &url,
                                        bool &allow_os_execution) {
    CefRequestHandler::OnProtocolExecution(browser, url, allow_os_execution);
}

bool SimpleHandler::OnCertificateError(CefRefPtr<CefBrowser> browser,
                                       CefLoadHandler::ErrorCode cert_error,
                                       const CefString &request_url,
                                       CefRefPtr<CefSSLInfo> ssl_info,
                                       CefRefPtr<CefRequestCallback> callback) {
    return CefRequestHandler::OnCertificateError(browser, cert_error, request_url, ssl_info, callback);
}

bool
SimpleHandler::OnSelectClientCertificate(CefRefPtr<CefBrowser> browser,
                                         bool isProxy,
                                         const CefString &host,
                                         int port,
                                         const CefRequestHandler::X509CertificateList &certificates,
                                         CefRefPtr<CefSelectClientCertificateCallback> callback) {
    return CefRequestHandler::OnSelectClientCertificate(browser, isProxy, host, port, certificates, callback);
}

void
SimpleHandler::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                         CefRequestHandler::TerminationStatus status) {
    CefRequestHandler::OnRenderProcessTerminated(browser, status);
}

int SimpleHandler::GetBrowserCount() const noexcept {
    return 0;
}

void SimpleHandler::ShowDevTools(CefRefPtr<CefBrowser> browser,
                                 const CefPoint &inspect_element_at) noexcept{

}

void SimpleHandler::CloseDevTools(CefRefPtr<CefBrowser> browser) noexcept {

}

bool SimpleHandler::HasSSLInformation(CefRefPtr<CefBrowser> browser) noexcept {
    return false;
}

void SimpleHandler::ShowSSLInformation(CefRefPtr<CefBrowser> browser) noexcept {

}

bool
SimpleHandler::CreatePopupWindow(CefRefPtr<CefBrowser> browser,
                                 bool is_devtools,
                                 const CefPopupFeatures &popupFeatures,
                                 CefWindowInfo &windowInfo,
                                 CefRefPtr<CefClient> &client,
                                 CefBrowserSettings &settings) {
    return false;
}

void
SimpleHandler::NotifyBrowserCreated(CefRefPtr<CefBrowser> browser) {

}

void
SimpleHandler::NotifyBrowserClosing(CefRefPtr<CefBrowser> browser) {

}

void
SimpleHandler::NotifyBrowserClosed(CefRefPtr<CefBrowser> browser) {

}

void SimpleHandler::NotifyAddress(const CefString& url) {

}

void SimpleHandler::NotifyTitle(const CefString& title) {

}

void SimpleHandler::NotifyFavicon(CefRefPtr<CefImage> image) {

}

void SimpleHandler::NotifyFullscreen(bool fullscreen) {

}

void SimpleHandler::NotifyAutoResize(const CefSize& new_size) {

}

void SimpleHandler::NotifyLoadingState(bool isLoading,
                                       bool canGoBack,
                                       bool canGoForward) {

}

void
SimpleHandler::NotifyDraggableRegions(const std::vector<CefDraggableRegion>& regions) {

}

void SimpleHandler::NotifyTakeFocus(bool next) {

}

void SimpleHandler::BuildTestMenu(CefRefPtr<CefMenuModel> model) {

}

bool SimpleHandler::ExecuteTestMenu(int command_id) {
    return false;
}



} //namespace simple end.
