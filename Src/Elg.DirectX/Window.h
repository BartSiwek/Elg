/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_WINDOW_H_
#define ELG_DIRECTX_WINDOW_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning(push)
#pragma warning(disable : 6540)
#include <intrin.h>
#include <windows.h>
#pragma warning(pop)

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/WindowsProcInterface.h"

namespace Elg {
namespace DirectX {

class Window {
 public:
  Window();
  virtual ~Window();

  virtual void Initialize(WindowsProcInterface* window_proc);
  virtual void Shutdown();

  HWND GetHandle();

  void SetWidth(elg_uint32 width);
  void SetHeight(elg_uint32 height);
  void SetSize(elg_uint32 width, elg_uint32 height);
  void SetPosition(elg_int32 left, elg_int32 top);

  elg_uint32 GetWidth();
  elg_uint32 GetHeight();
  elg_int32 GetLeft();
  elg_int32 GetTop();

  void ResizeWindow(elg_uint32 width, elg_uint32 height);

  void SetCaption(const elg_char* caption);
  const elg_char* GetCaption();

 protected:
  void UpdateState();

  HWND m_hwnd_;
  DWORD m_style_;
  const elg_char* m_caption_;
  elg_uint32 m_width_;
  elg_uint32 m_height_;
  elg_int32 m_left_;
  elg_int32 m_top_;
};

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_WINDOW_H_
