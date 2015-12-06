/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#include "Elg.DirectX/Window.h"

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"
#include "Elg.DirectX/WindowRegistry.h"

namespace Elg {
namespace DirectX {

LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  if (msg != WM_CREATE) {
    // Messages other than WM_CREATE
    LONG_PTR ptr = GetWindowLongPtr(hwnd, 0);
    WindowsProcInterface* window_proc = reinterpret_cast<WindowsProcInterface*>(ptr);

    if (window_proc != NULL) {
      return window_proc->WindowProc(hwnd, msg, wparam, lparam);
    } else {
      return DefWindowProc(hwnd, msg, wparam, lparam);
    }
  } else {
    // WM_CREATE message
    LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lparam);
    WindowsProcInterface* window_proc = reinterpret_cast<WindowsProcInterface*>(create_struct->lpCreateParams);

    if (window_proc != NULL) {
      SetWindowLongPtr(hwnd, 0, reinterpret_cast<LONG_PTR>(window_proc));
      return window_proc->WindowProc(hwnd, msg, wparam, lparam);
    } else {
      return DefWindowProc(hwnd, msg, wparam, lparam);
    }
  }
}

Window::Window() : m_hwnd_(0), m_style_(WS_OVERLAPPEDWINDOW | WS_VISIBLE), m_caption_(""), m_width_(640),
                   m_height_(480), m_left_(100), m_top_(100) {
}

Window::~Window() {
  Shutdown();
}

void Window::Initialize(WindowsProcInterface* window_proc) {
  // Setup window class
  WNDCLASSEXA wc;
  memset(&wc, 0, sizeof(wc));

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = InternalWindowProc;
  wc.cbClsExtra = NULL;
  wc.cbWndExtra = sizeof(window_proc);
  wc.hInstance = 0;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "ElgWindow";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  // Rgister the class
  RegisterClassExA(&wc);

  // Calculate the size of the window
  RECT rc;
  rc.top = rc.left = 0;
  rc.right = m_width_;
  rc.bottom = m_height_;

  // Adjust the window size for style
  AdjustWindowRect(&rc, m_style_, FALSE);

  // Read back the adjusted values
  elg_int32 lwidth = rc.right - rc.left;
  elg_int32 lheight = rc.bottom - rc.top;

  elg_int32 lleft = (elg_int32)m_left_;
  elg_int32 ltop = (elg_int32)m_top_;

  // Create the window
  m_hwnd_ = CreateWindowExA(NULL, wc.lpszClassName, m_caption_, m_style_, lleft,
                            ltop, lwidth /* width */, lheight /* height */, NULL, NULL, NULL,
                            window_proc);  // Pass a pointer to this so we can register the WndProc on WM_CREATE
  ASSERT(m_hwnd_ != 0, "Error creating DirectX.Window");

  // Register the window
  WindowRegistry::RegisterWindow(this);

  // Show window
  ShowWindow(m_hwnd_, SW_SHOWNORMAL);
  UpdateWindow(m_hwnd_);
}

void Window::Shutdown() {
  if (m_hwnd_ != 0) {
    // Deregister the window
    WindowRegistry::UnregisterWindow(this);

    // Destoroy it
    DestroyWindow(m_hwnd_);
  }
  m_hwnd_ = 0;
}

HWND Window::GetHandle() {
  return m_hwnd_;
}

void Window::SetWidth(elg_uint32 width) {
  m_width_ = width;
  UpdateState();
}

void Window::SetHeight(elg_uint32 height) {
  m_height_ = height;
  UpdateState();
}

void Window::SetSize(elg_uint32 width, elg_uint32 height) {
  m_width_ = width;
  m_height_ = height;
  UpdateState();
}

void Window::SetPosition(elg_int32 left, elg_int32 top) {
  m_left_ = left;
  m_top_ = top;
  UpdateState();
}

elg_uint32 Window::GetWidth() {
  RECT rect;
  GetClientRect(m_hwnd_, &rect);
  return (rect.right - rect.left);
}

elg_uint32 Window::GetHeight() {
  RECT rect;
  GetClientRect(m_hwnd_, &rect);
  return (rect.bottom - rect.top);
}

elg_int32 Window::GetLeft() {
  POINT point;
  point.x = 0;
  point.y = 0;

  ClientToScreen(m_hwnd_, &point);

  return point.x;
}

int Window::GetTop() {
  POINT point;
  point.x = 0;
  point.y = 0;

  ClientToScreen(m_hwnd_, &point);

  return point.y;
}

void Window::ResizeWindow(elg_uint32 width, elg_uint32 height) {
  m_width_ = width;
  m_height_ = height;
}

void Window::SetCaption(const elg_char* caption) {
  m_caption_ = caption;

  if (m_hwnd_ != 0) {
    SetWindowTextA(m_hwnd_, m_caption_);
  }
}

const elg_char* Window::GetCaption() {
  return m_caption_;
}

void Window::UpdateState() {
  if (m_hwnd_ != 0) {
    RECT ClientRect;
    ClientRect.left = 0;
    ClientRect.top = 0;
    ClientRect.right = m_width_;
    ClientRect.bottom = m_height_;

    // Adjust the window size for correct device size
    RECT WindowRect = ClientRect;
    AdjustWindowRect(&WindowRect, m_style_, FALSE);

    elg_int32 delta_x = (WindowRect.right - ClientRect.right) / 2;
    elg_int32 delta_y = (WindowRect.bottom - ClientRect.right) / 2;

    MoveWindow(m_hwnd_, m_left_ - delta_x, m_top_ - delta_y,
               m_width_ + 2*delta_x, m_height_ + 2*delta_y, true);
  }
}

}  // namespace DirectX
}  // namespace Elg
