/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_WINDOWREGISTRY_H_
#define ELG_DIRECTX_WINDOWREGISTRY_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#pragma warning(pop)

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/Window.h"

namespace Elg {
namespace DirectX {
namespace WindowRegistry {

void RegisterWindow(Window* window);
elg_uint32 GetWindowCount();
Window* GetWindow(HWND hwnd);
void UnregisterWindow(Window* window);

}  // namespace WindowRegistry
}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_WINDOWREGISTRY_H_
