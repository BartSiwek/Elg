/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>

#include "Elg/EntityManager/EntityPool/EntityPool.h"

#include "Elg/EntityManager/ComponentPool/ComponentPool.h"

// Test components should have a move semantics
struct TestComponent {
  TestComponent()
      : Data(1), DestructionCounter(NULL) {
  }

  TestComponent(const TestComponent &other)
      : Data(other.Data), DestructionCounter(other.DestructionCounter) {
    if (DestructionCounter != NULL) {
      *DestructionCounter += 1;
    }
  }

  TestComponent& operator=(const TestComponent& other) {
    if (this != &other) {
      // Destroy current object
      if (DestructionCounter != NULL) {
        *DestructionCounter -= 1;
      }

      // Copy
      Data = other.Data;
      DestructionCounter = other.DestructionCounter;

      // Create a new object
      if (DestructionCounter != NULL) {
        *DestructionCounter += 1;
      }
    }
    return *this;
  }

  ~TestComponent() {
    if (DestructionCounter != NULL) {
      *DestructionCounter -= 1;
    }
  }

  elg_uint32 Data;
  elg_int32* DestructionCounter;
};

TEST(ComponentPool_DefaultState) {
  // Setup & execute the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;

  // Check that all entity indices don't have components
  for (elg_uint32 entity_id_index = 0;entity_id_index < EntityCount;++entity_id_index) {
    CHECK_EQUAL(ELG_ENTITY_MANAGER_INVALID_ID, pool.GetComponent(entity_id_index));
  }

  // Check that count is equal to zero
  CHECK_EQUAL(static_cast<elg_uint32>(0), pool.GetDataCount());
}

TEST(ComponentPool_SimpleCreate) {
  // Setup
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;

  // Execute
  elg_uint32 entity_id = entity_pool.CreateEntity();
  elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

  elg_uint32 offset = pool.CreateComponent(entity_id_index, entity_id);
  TestComponent* data = pool.GetData();
  data[offset].Data = 123;

  // Assert
  CHECK_EQUAL(static_cast<elg_uint32>(1), pool.GetDataCount());
  CHECK_EQUAL(entity_id, pool.GetDataEntities()[0]);
  CHECK(pool.GetComponent(entity_id_index) != ELG_ENTITY_MANAGER_INVALID_ID);
  CHECK_EQUAL(static_cast<elg_uint32>(123), pool.GetData()[pool.GetComponent(entity_id_index)].Data);
}

TEST(ComponentPool_SimpleCreateDestroy) {
  // Setup
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;
  elg_int32 destruction_counter = 0;

  // Execute
  elg_uint32 entity_id = entity_pool.CreateEntity();
  elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

  elg_uint32 offset = pool.CreateComponent(entity_id_index, entity_id);
  TestComponent* data = pool.GetData();
  data[offset].DestructionCounter = &destruction_counter;
  *data[offset].DestructionCounter += 1;

  pool.DestroyComponent(entity_id_index);

  // Assert
  CHECK_EQUAL(static_cast<elg_uint32>(0), pool.GetDataCount());
  CHECK_EQUAL(ELG_ENTITY_MANAGER_INVALID_ID, pool.GetComponent(entity_id_index));
  CHECK_EQUAL(0, destruction_counter);
}

TEST(ComponentPool_FillCreate) {
  // Setup the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;

  // Execute
  elg_uint32 created_entity_ids[ComponentCount];
  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    created_entity_ids[i] = entity_pool.CreateEntity();
    elg_uint32 entity_id_index = entity_pool.GetEntityIndex(created_entity_ids[i]);

    elg_uint32 offset = pool.CreateComponent(entity_id_index, created_entity_ids[i]);
    TestComponent* data = pool.GetData();
    data[offset].Data = 100 + i;
  }

  // Check that count and active entities make sense
  CHECK_EQUAL(ComponentCount, pool.GetDataCount());

  const elg_uint32* data_entities = pool.GetDataEntities();
  const elg_uint32* data_entities_end = pool.GetDataEntities()+pool.GetDataCount();

  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    elg_uint32 entity_id = created_entity_ids[i];

    CHECK(std::find(data_entities, data_entities_end, entity_id) != data_entities_end);

    elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

    CHECK(pool.GetComponent(entity_id_index) != ELG_ENTITY_MANAGER_INVALID_ID);

    elg_uint32 offset = pool.GetComponent(entity_id_index);
    TestComponent* data = pool.GetData();
    CHECK_EQUAL(100 + i, data[offset].Data);
  }
}

TEST(ComponentPool_FillCreateDestroy) {
  // Setup the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;
  elg_int32 destruction_counters[ComponentCount];

  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    destruction_counters[i] = 0;
  }

  // Execute
  elg_uint32 created_entity_ids[ComponentCount];
  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    created_entity_ids[i] = entity_pool.CreateEntity();
    elg_uint32 entity_id_index = entity_pool.GetEntityIndex(created_entity_ids[i]);

    elg_uint32 offset = pool.CreateComponent(entity_id_index, created_entity_ids[i]);
    TestComponent* data = pool.GetData();
    data[offset].Data = 100 + i;
    data[offset].DestructionCounter = &destruction_counters[i];
    *data[offset].DestructionCounter += 1;
  }

  // Check that count and active entities make sense
  CHECK_EQUAL(ComponentCount, pool.GetDataCount());

  const elg_uint32* data_entities = pool.GetDataEntities();
  const elg_uint32* data_entities_end = pool.GetDataEntities()+pool.GetDataCount();

  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    elg_uint32 entity_id = created_entity_ids[i];

    CHECK(std::find(data_entities, data_entities_end, entity_id) != data_entities_end);

    elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

    elg_uint32 offset = pool.GetComponent(entity_id_index);
    TestComponent* data = pool.GetData();
    CHECK_EQUAL(100 + i, data[offset].Data);

    pool.DestroyComponent(entity_id_index);
  }

  // Check after deleteion
  CHECK_EQUAL(static_cast<elg_uint32>(0), pool.GetDataCount());
  for (elg_uint32 i = 0;i < ComponentCount;++i) {
    elg_uint32 entity_id_index = entity_pool.GetEntityIndex(created_entity_ids[i]);
    CHECK_EQUAL(ELG_ENTITY_MANAGER_INVALID_ID, pool.GetComponent(entity_id_index));
    CHECK_EQUAL(0, destruction_counters[i]);
  }
}

TEST(ComponentPool_FillCreateDestroyRandom) {
  // Setup the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  elg_int32 destruction_counters[ComponentCount];

  std::srand(static_cast<unsigned int>(std::time(NULL)));

  // Execute
  for (elg_uint32 iteration_index = 0;iteration_index < 10;++iteration_index) {
    Elg::EntityManager::EntityPool<EntityCount> entity_pool;

    for (elg_uint32 i = 0;i < ComponentCount;++i) {
      destruction_counters[i] = 0;
    }

    elg_uint32 created_entity_ids[ComponentCount];
    for (elg_uint32 i = 0;i < ComponentCount;++i) {
      created_entity_ids[i] = entity_pool.CreateEntity();
      elg_uint32 entity_id_index = entity_pool.GetEntityIndex(created_entity_ids[i]);

      elg_uint32 offset = pool.CreateComponent(entity_id_index, created_entity_ids[i]);
      TestComponent* data = pool.GetData();
      data[offset].Data = 100 + i;
      data[offset].DestructionCounter = &destruction_counters[i];
      *data[offset].DestructionCounter += 1;
    }

    // Check that count and active entities make sense
    CHECK_EQUAL(ComponentCount, pool.GetDataCount());
    for (elg_uint32 current_count = ComponentCount;current_count > 0;--current_count) {
      elg_uint32 value = (rand() % current_count);  // NOLINT(runtime/threadsafe_fn) - thread safe according to MSDN

      elg_uint32 entity_id = created_entity_ids[value];
      created_entity_ids[value] = created_entity_ids[current_count-1];
      created_entity_ids[current_count-1] = entity_id;

      elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);
      pool.DestroyComponent(entity_id_index);
    }

    // Check after deletion
    CHECK_EQUAL(static_cast<elg_uint32>(0), pool.GetDataCount());
    for (elg_uint32 i = 0;i < ComponentCount;++i) {
      elg_uint32 entity_id_index = entity_pool.GetEntityIndex(created_entity_ids[i]);
      CHECK_EQUAL(ELG_ENTITY_MANAGER_INVALID_ID, pool.GetComponent(entity_id_index));
      CHECK_EQUAL(0, destruction_counters[i]);
    }
  }
}

TEST(ComponentPool_Destructor) {
  // Setup
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  elg_int32 destruction_counters[ComponentCount];

  for (elg_uint32 flag_index = 0;flag_index < ComponentCount;++flag_index) {
    destruction_counters[flag_index] = 0;
  }

  // Execute
  {
    Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
    Elg::EntityManager::EntityPool<EntityCount> entity_pool;

    for (elg_uint32 flag_index = 0;flag_index < ComponentCount;++flag_index) {
      elg_uint32 entity_id = entity_pool.CreateEntity();
      elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

      elg_uint32 offset = pool.CreateComponent(entity_id_index, entity_id);
      TestComponent* data = pool.GetData();
      data[offset].DestructionCounter = &destruction_counters[flag_index];
      *data[offset].DestructionCounter += 1;
    }

    // Destructor gets called here...
  }

  // Check
  for (elg_uint32 flag_index = 0;flag_index < ComponentCount;++flag_index) {
    CHECK_EQUAL(0, destruction_counters[flag_index]);
  }
}

TEST(ComponentPool_RandomOperations) {
  // Setup the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;

  elg_uint32 current_count = 0;
  elg_uint32 entity_ids[ComponentCount];
  std::map<elg_uint32, elg_uint32> entity_to_index;
  elg_uint32 payload[ComponentCount];
  elg_int32 destruction_counters[ComponentCount];

  for (elg_uint32 current_index = 0;current_index < ComponentCount;++current_index) {
    entity_ids[current_index] = entity_pool.CreateEntity();
    entity_to_index[entity_ids[current_index]] = current_index;
    payload[current_index] = 0;
    destruction_counters[current_index] = 0;
  }

  // Run the test and check as we go
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  for (elg_uint32 operation_index = 0;operation_index < 100000;++operation_index) {
    elg_uint32 value = (rand() % 10);  // NOLINT(runtime/threadsafe_fn) - thread safe according to MSDN
    if (value < current_count) {
      // Get or delete
      elg_uint32 change_or_delete = (rand() % 2);  // NOLINT(runtime/threadsafe_fn) - thread safe according to MSDN
      if (change_or_delete == 0) {
        // Get the entity id whose component we want to change (and its index)
        elg_uint32 entity_id = entity_ids[value];

        const elg_uint32* data_entities = pool.GetDataEntities();
        const elg_uint32* data_entities_end = pool.GetDataEntities()+pool.GetDataCount();

        CHECK(std::find(data_entities, data_entities_end, entity_id) != data_entities_end);

        elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);
        elg_uint32 global_index = entity_to_index[entity_id];

        // Get the offset of that component
        elg_uint32 offset = pool.GetComponent(entity_id_index);
        TestComponent* data = pool.GetData();

        // Do a check and change
        CHECK_EQUAL(payload[global_index], data[offset].Data);
        data[offset].Data = ++payload[global_index];
      } else {
        // Get the entity id to be deleted, its index and its global index
        elg_uint32 entity_id = entity_ids[value];
        elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);
        elg_uint32 global_index = entity_to_index[entity_id];

        // Delete & check
        pool.DestroyComponent(entity_id_index);
        CHECK_EQUAL(0, destruction_counters[global_index]);

        // Get the new spot for the deleted entity
        elg_uint32 top_global_index = --current_count;

        entity_ids[value] = entity_ids[top_global_index];
        entity_ids[top_global_index] = entity_id;
      }
    } else {
      // Get the entity id for new component
      elg_uint32 entity_id = entity_ids[current_count++];
      elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);
      elg_uint32 global_index = entity_to_index[entity_id];

      // Create the component and get the data
      elg_uint32 offset = pool.CreateComponent(entity_id_index, entity_id);
      TestComponent* data = pool.GetData();

      // Assign the values
      data[offset].DestructionCounter = &destruction_counters[global_index];
      *data[offset].DestructionCounter += 1;
      data[offset].Data = ++payload[global_index];
    }
  }
}

TEST(CreateComponentOverflow) {
  // This is just asserted - not testing

  /*
  // Setup the test
  const uint16 ComponentCount = 128;
  const uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;

  // Execute
  for(uint32 component_index = 0;component_index < ComponentCount;++component_index) {
    uint32 entity_id = entity_pool.CreateEntity();
    uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

    pool.CreateComponent(entity_id_index, entity_id);
  }

  // Check
  uint32 final_entity_id = entity_pool.CreateEntity();
  uint32 final_entity_id_index = entity_pool.GetEntityIndex(final_entity_id);

  CHECK_THROW(pool.CreateComponent(final_entity_id_index, final_entity_id), Elg::EntityManager::EntityManagerException);
  */
}

TEST(GetNonexistentComponent) {
  // Setup the test
  const elg_uint16 ComponentCount = 128;
  const elg_uint16 EntityCount = 1024;
  Elg::EntityManager::ComponentPool<TestComponent, ComponentCount, EntityCount> pool;
  Elg::EntityManager::EntityPool<EntityCount> entity_pool;

  // Execute
  elg_uint32 entity_id = entity_pool.CreateEntity();
  elg_uint32 entity_id_index = entity_pool.GetEntityIndex(entity_id);

  // Check
  CHECK_EQUAL(ELG_ENTITY_MANAGER_INVALID_ID, pool.GetComponent(entity_id_index));
}
