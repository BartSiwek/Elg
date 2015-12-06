/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_KEYBOARD_H_
#define ELG_DIRECTX_KEYBOARD_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#include "Elg/Utilities/Types.h"

#include "Elg.DirectX/VirtualKeyCode.h"
#include "Elg.DirectX/VirtualKeyModifierFlags.h"
#include "Elg.DirectX/VirtualKeyState.h"

namespace Elg {
namespace DirectX {

void RegisterKeyUp(VirtualKeyCode key_code);
void RegisterKeyDown(VirtualKeyCode key_code);

void ResetKeyboardState();

VirtualKeyState GetState(VirtualKeyCode key_code);
VirtualKeyState GetPreviousState(VirtualKeyCode key_code);

VirtualKeyCode GetKeyCode(USHORT windows_key_code);
VirtualKeyModifierFlags GetModifierFlags();

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_KEYBOARD_H_
