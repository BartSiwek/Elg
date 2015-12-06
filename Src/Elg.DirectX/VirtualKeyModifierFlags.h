/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_VIRTUALKEYMODIFIERFLAGS_H_
#define ELG_DIRECTX_VIRTUALKEYMODIFIERFLAGS_H_

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace DirectX {

enum VirtualKeyModifierFlags {
  KEY_MODIFIER_NONE   = 0x0000,
  KEY_MODIFIER_SHIFT  = 0x0001,
  KEY_MODIFIER_CTRL   = 0x0002,
  KEY_MODIFIER_ALT    = 0x0004,
  KEY_MODIFIER_LWIN   = 0x0008,
  KEY_MODIFIER_RWIN   = 0x0010,
};

}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_VIRTUALKEYMODIFIERFLAGS_H_

