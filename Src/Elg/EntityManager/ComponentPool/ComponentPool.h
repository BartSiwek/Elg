/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ENTITYMANAGER_COMPONENTPOOL_COMPONENTPOOL_H_
#define ELG_ENTITYMANAGER_COMPONENTPOOL_COMPONENTPOOL_H_

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace EntityManager {

template<typename ComponentType, elg_uint16 MaxInstances, elg_uint16 MaxEntities>
class ComponentPool {
 public:
  // Asserts
  STATIC_ASSERT(MaxInstances < 0xFFFFFFFE, "The maximum number of component instances is limited to 2^16-1");

  // Consts
  static const elg_uint16 InstanceCount = MaxInstances;

  // Typedefs
  typedef ComponentType component_type;

  // Constructor
  ComponentPool();

  // Destructor
  ~ComponentPool();

  // Methods, including static methods
  elg_uint32 CreateComponent(elg_uint32 entity_id_index, elg_uint32 entity_id);
  inline elg_uint32 GetComponent(elg_uint32 entity_id_index) const;
  void DestroyComponent(elg_uint32 entity_id_index);

  inline elg_uint32 GetDataCount() const;
  inline const elg_uint32* GetDataEntities() const;
  inline ComponentType* GetData();
  inline const ComponentType* GetData() const;

  void Serialize(FILE* out) const;
  void Deserialize(FILE* in);

 private:
  // Consts
  static const elg_uint32 ComponentSize = sizeof(ComponentType);
  static const elg_uint32 ComponentAlignment = std::alignment_of<ComponentType>::value;

  // Typedefs
  typedef typename std::aligned_storage<ComponentSize, ComponentAlignment>::type ComponentStorageType;

  // Methods, including static methods [Data access helpers]
  inline ComponentType* GetStorage(elg_uint32 index);
  inline const ComponentType* GetStorage(elg_uint32 index) const;

  // Data members
  ComponentStorageType m_storage_[MaxInstances];
  elg_uint32 m_entity_ids_[MaxEntities];
  elg_uint32 m_active_entity_ids_[MaxInstances];
  elg_uint32 m_top_;

  // Disallow copy and assign
  ComponentPool(const ComponentPool&);
  void operator=(const ComponentPool&);
};

}  // namespace EntityManager
}  // namespace Elg

#include "Elg/EntityManager/ComponentPool/ComponentPool-inl.h"

#endif  // ELG_ENTITYMANAGER_COMPONENTPOOL_COMPONENTPOOL_H_
