/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_EVENTS_EVENT_H_
#define ELG_DIRECTX_EVENTS_EVENT_H_

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/MouseButton.h"
#include "Elg.DirectX/MouseButtonAction.h"
#include "Elg.DirectX/VirtualKeyCode.h"
#include "Elg.DirectX/VirtualKeyModifierFlags.h"
#include "Elg.DirectX/VirtualKeyState.h"

namespace Elg { namespace DirectX { class Window; } }


namespace Elg {
namespace DirectX {
namespace Events {

enum EventType {
  MOUSE_BUTTON_EVENT,
  MOUSE_MOVE_EVENT,
  MOUSE_WHEEL_EVENT,
  KEYBOARD_EVENT,
  EVENT_TYPE_COUNT  // Must be last entry
};

struct Event {
  EventType EventType;
  union {
    struct {
      Window* Window;
      VirtualKeyCode KeyCode;
      VirtualKeyModifierFlags ModifierFlags;
      VirtualKeyState State;
      VirtualKeyState PreviousState;
    } KeyboardEvent;
    struct {
      Window* Window;
      MouseButton Button;
      MouseButtonAction Action;
      elg_int32 X;
      elg_int32 Y;
    } MouseButtonEvent;
    struct {
      Window* Window;
      elg_int32 X;
      elg_int32 Y;
    } MouseMoveEvent;
    struct {
      Window* Window;
      elg_int32 X;
      elg_int32 Y;
      elg_int32 Delta;
    } MouseWheelEvent;
  };
};

}  // namespace Events
}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_EVENTS_EVENT_H_
