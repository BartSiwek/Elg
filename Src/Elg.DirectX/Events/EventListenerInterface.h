/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_EVENTS_EVENTLISTENERINTERFACE_H_
#define ELG_DIRECTX_EVENTS_EVENTLISTENERINTERFACE_H_

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/Events/Event.h"

namespace Elg {
namespace DirectX {
namespace Events {

class EventListenerInterface {
 public:
  EventListenerInterface() {
  }

  virtual ~EventListenerInterface() {
  }

  virtual const elg_char* GetEventListenerName() const = 0;
  virtual bool HandleEvent(Event* e) = 0;
};

}  // namespace Events
}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_EVENTS_EVENTLISTENERINTERFACE_H_
