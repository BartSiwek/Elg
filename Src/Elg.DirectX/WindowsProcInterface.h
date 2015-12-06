/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_WINDOWSPROCINTERFACE_H_
#define ELG_DIRECTX_WINDOWSPROCINTERFACE_H_

#include <windows.h>

namespace Elg {
namespace DirectX {

class WindowsProcInterface {
 public:
  WindowsProcInterface() {
  }

  virtual ~WindowsProcInterface() {
  }

  virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
};

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_WINDOWSPROCINTERFACE_H_
