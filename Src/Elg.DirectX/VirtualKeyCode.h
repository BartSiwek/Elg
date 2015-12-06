/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_VIRTUALKEYCODE_H_
#define ELG_DIRECTX_VIRTUALKEYCODE_H_

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace DirectX {

// The codes should have linear indices - makes it easier to create arrays of key states
enum VirtualKeyCode {
  KEY_NONE,

  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,

  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,

  KEY_ESCAPE,

  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,

  KEY_TILDE,
  KEY_MINUS,
  KEY_EQUALS,
  KEY_BACKSPACE,
  KEY_TAB,
  KEY_OPENBRACE,
  KEY_CLOSEBRACE,
  KEY_ENTER,
  KEY_SEMICOLON,
  KEY_QUOTE,
  KEY_BACKSLASH,
  KEY_COMMA,
  KEY_DOT,
  KEY_SLASH,
  KEY_SPACE,

  KEY_INSERT,
  KEY_DELETE,
  KEY_HOME,
  KEY_END,
  KEY_PGUP,
  KEY_PGDN,

  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,

  KEY_NUMPAD_0,
  KEY_NUMPAD_1,
  KEY_NUMPAD_2,
  KEY_NUMPAD_3,
  KEY_NUMPAD_4,
  KEY_NUMPAD_5,
  KEY_NUMPAD_6,
  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9,

  KEY_NUMPAD_SLASH,
  KEY_NUMPAD_ASTERISK,
  KEY_NUMPAD_MINUS,
  KEY_NUMPAD_PLUS,
  KEY_NUMPAD_DECIMAL,
  KEY_NUMPAD_ENTER,

  KEY_LSHIFT,
  KEY_RSHIFT,
  KEY_LCTRL,
  KEY_RCTRL,
  KEY_ALT,
  KEY_LWIN,
  KEY_RWIN,

  KEY_PRINTSCREEN,
  KEY_SCROLLLOCK,
  KEY_PAUSE,
  KEY_NUMLOCK,
  KEY_CAPSLOCK,

  KEY_COUNT,
};

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_VIRTUALKEYCODE_H_

