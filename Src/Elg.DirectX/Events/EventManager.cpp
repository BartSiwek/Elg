/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include "Elg.DirectX/Events/EventManager.h"

#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace DirectX {
namespace Events {

EventManager::EventManager() {
  // Initialize
  for (elg_uint32 event_type = 0; event_type < EVENT_TYPE_COUNT; ++event_type) {
    for (elg_uint32 listener_index = 0; listener_index < MAX_EVENT_LISTENERS; ++listener_index) {
      m_event_listeners_[event_type][listener_index] = NULL;
    }
    m_event_listener_count_[event_type] = 0;
  }
}

EventManager::~EventManager() {
}

bool EventManager::AddEventListener(EventType event_id, EventListenerInterface* listener) {
  if (event_id < EVENT_TYPE_COUNT && listener != NULL) {
    ASSERT(GetListenerIndex(event_id, listener) == MAX_EVENT_LISTENERS, "The listener is already added");

    if (m_event_listener_count_[event_id] < MAX_EVENT_LISTENERS) {
      m_event_listeners_[event_id][m_event_listener_count_[event_id]] = listener;
      ++m_event_listener_count_[event_id];

      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool EventManager::RemoveEventListener(EventType event_id, EventListenerInterface* listener) {
  if (event_id < EVENT_TYPE_COUNT && listener != NULL) {
    elg_uint32 deleted_listener_index = GetListenerIndex(event_id, listener);

    elg_uint32 listener_count = m_event_listener_count_[event_id];

    if (deleted_listener_index < listener_count) {
      ASSERT(listener_count < MAX_EVENT_LISTENERS, "The listener count exceeds MAX_EVENT_LISTENERS");

      for (elg_uint32 handler_index = deleted_listener_index + 1;handler_index < listener_count; ++handler_index) {
        m_event_listeners_[event_id][handler_index-1] = m_event_listeners_[event_id][handler_index];
      }

      --m_event_listener_count_[event_id];

      return true;
    } else {
      return false;
    }
  } else {
    return false;  // Invalid event id
  }
}

bool EventManager::FireEvent(Event* e) const {
  // Check for null
  if (e != NULL) {
    // Find out the event type
    EventType event_type = e->EventType;

    // Iterate over handlers
    bool handled = false;
    for (elg_uint32 listener_index = 0; listener_index < m_event_listener_count_[event_type]; ++listener_index) {
      handled = m_event_listeners_[event_type][listener_index]->HandleEvent(e);
      if (handled) {
        break;
      }
    }

    // Return the result
    return handled;
  } else {
    return false;
  }
}

elg_uint32 EventManager::GetListenerIndex(EventType event_id, EventListenerInterface* listener) {
  elg_uint32 listener_index = 0;
  elg_uint32 listener_count = m_event_listener_count_[event_id];
  while (listener_index < listener_count) {
    if (m_event_listeners_[event_id][listener_index] == listener) {
      return listener_index;
    }
    ++listener_index;
  }
  return MAX_EVENT_LISTENERS;
}

}  // namespace Events
}  // namespace DirectX
}  // namespace Elg
