/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Elg.DirectX/WindowRegistry.h"

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#pragma warning(pop)

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"
#include "Elg.DirectX/Window.h"

namespace Elg {
namespace DirectX {
namespace WindowRegistry {

static const elg_uint32 MAX_WINDOWS = 64;

Window* g_windows_[MAX_WINDOWS];
elg_uint32 g_window_count_ = 0;

void RegisterWindow(Window* window) {
  ASSERT(g_window_count_ < MAX_WINDOWS, "Window registry is full");
  g_windows_[g_window_count_++] = window;
}

elg_uint32 GetWindowCount() {
  return g_window_count_;
}

Window* GetWindow(HWND hwnd) {
  elg_uint32 window_index = 0;
  while (window_index < g_window_count_) {
    if (g_windows_[window_index]->GetHandle() == hwnd) {
      break;
    }
    ++window_index;
  }

  if (window_index < g_window_count_) {
    return g_windows_[window_index];
  } else {
    return NULL;
  }
}

void UnregisterWindow(Window* window) {
  elg_uint32 window_index = 0;
  while (window_index < g_window_count_) {
    if (g_windows_[window_index] == window) {
      break;
    }
    ++window_index;
  }

  while (window_index+1 < g_window_count_) {
    g_windows_[window_index] = g_windows_[window_index+1];
    ++window_index;
  }

  g_window_count_ = window_index;
}

}  // namespace WindowRegistry
}  // namespace DirectX
}  // namespace Elg
