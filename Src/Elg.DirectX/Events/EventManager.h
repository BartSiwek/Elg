/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_DIRECTX_EVENTS_EVENTMANAGER_H_
#define ELG_DIRECTX_EVENTS_EVENTMANAGER_H_

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/Events/Event.h"
#include "Elg.DirectX/Events/EventListenerInterface.h"

namespace Elg {
namespace DirectX {
namespace Events {

class EventManager {
 public:
  EventManager();
  virtual ~EventManager();

  bool AddEventListener(EventType event_id, EventListenerInterface* listener);
  bool RemoveEventListener(EventType event_id, EventListenerInterface* listener);

  bool FireEvent(Event* e) const;

 protected:
  static const elg_uint32 MAX_EVENT_LISTENERS = 32;

  elg_uint32 GetListenerIndex(EventType event_id, EventListenerInterface* listener);

  EventListenerInterface* m_event_listeners_[EVENT_TYPE_COUNT][MAX_EVENT_LISTENERS];
  elg_uint32 m_event_listener_count_[EVENT_TYPE_COUNT];
};

}  // namespace Events
}  // namespace DirectX
}  // namespace Elg

#endif  // ELG_DIRECTX_EVENTS_EVENTMANAGER_H_
