/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Types.h"
#include "Elg.DirectX/Events/EventManager.h"

class TestListener : public Elg::DirectX::Events::EventListenerInterface {
 public:
  TestListener() : LastEventType(Elg::DirectX::Events::EVENT_TYPE_COUNT), CallCount(0) {
  }

  virtual const char* GetEventListenerName() const {
    return "TestListener";
  }

  virtual bool HandleEvent(Elg::DirectX::Events::Event* e) {
    LastEventType = e->EventType;
    ++CallCount;
    return true;
  }

  Elg::DirectX::Events::EventType LastEventType;
  elg_int32 CallCount;
};

TEST(Events_AddListener_Null) {
  Elg::DirectX::Events::EventManager em;

  CHECK(!em.AddEventListener(Elg::DirectX::Events::EventType(0), NULL));
}

TEST(Events_AddListener_Duplicate) {
  // This is just asserted - not testing
  /*
  Elg::DirectX::Events::EventManager em;
  TestListener listener;

  CHECK(em.AddEventListener(Elg::DirectX::Events::EventType(0), &listener));

  CHECK(!em.AddEventListener(Elg::DirectX::Events::EventType(0), &listener));

  CHECK(em.RemoveEventListener(Elg::DirectX::Events::EventType(0), &listener));
  */
}

TEST(Events_AddListener_InvalidEventType) {
  Elg::DirectX::Events::EventManager em;
  TestListener listener;

  CHECK(!em.AddEventListener(Elg::DirectX::Events::EVENT_TYPE_COUNT, &listener));
}

TEST(Events_RemoveListener_Null) {
  Elg::DirectX::Events::EventManager em;

  CHECK(!em.RemoveEventListener(Elg::DirectX::Events::EventType(0), NULL));
}

TEST(Events_RemoveListener_Duplicate) {
  // This is just asserted - not testing
  /*
  Elg::DirectX::Events::EventManager em;
  TestListener listener;

  CHECK(em.AddEventListener(Elg::DirectX::Events::EventType(0), &listener));

  CHECK(em.RemoveEventListener(Elg::DirectX::Events::EventType(0), &listener));

  CHECK(!em.RemoveEventListener(Elg::DirectX::Events::EventType(0), &listener));
  */
}

TEST(Events_RemoveListener_InvalidEventType) {
  Elg::DirectX::Events::EventManager em;
  TestListener listener;

  CHECK(!em.RemoveEventListener(Elg::DirectX::Events::EVENT_TYPE_COUNT, &listener));
}

TEST(Events_Usage) {
  Elg::DirectX::Events::EventManager em;

  TestListener listener1;
  TestListener listener2;
  CHECK(em.AddEventListener(Elg::DirectX::Events::EventType(0), &listener1));
  CHECK(em.AddEventListener(Elg::DirectX::Events::EventType(0), &listener2));

  Elg::DirectX::Events::Event e;
  e.EventType = Elg::DirectX::Events::EventType(0);

  CHECK(em.FireEvent(&e));

  CHECK_EQUAL(Elg::DirectX::Events::EventType(0), listener1.LastEventType);
  CHECK_EQUAL(1, listener1.CallCount);

  CHECK_EQUAL(Elg::DirectX::Events::EVENT_TYPE_COUNT, listener2.LastEventType);
  CHECK_EQUAL(0, listener2.CallCount);

  CHECK(em.RemoveEventListener(Elg::DirectX::Events::EventType(0), &listener1));
  CHECK(em.RemoveEventListener(Elg::DirectX::Events::EventType(0), &listener2));
};
