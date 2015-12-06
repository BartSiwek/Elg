/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ENTITYMANAGER_ENTITYPOOL_ENTITYPOOL_H_
#define ELG_ENTITYMANAGER_ENTITYPOOL_ENTITYPOOL_H_

#include "Elg/Utilities/Asserts.h"
#include "Elg/Utilities/Types.h"

namespace Elg {
namespace EntityManager {

template<elg_uint16 MaxEntities>
class EntityPool {
 public:
  // Consts
  static const elg_uint16 MaxEntityCount = MaxEntities;

  // Asserts
  STATIC_ASSERT(MaxEntities < 0xFFFFFFFE, "The maximum number of entities is limited to 2^16-1");

  // Constructors
  EntityPool();

  // Destructor
  ~EntityPool();

  // Methods, including static methods
  elg_uint32 CreateEntity();
  inline elg_uint32 GetActiveEntityCount() const;
  inline const elg_uint32* GetActiveEntities() const;
  inline elg_uint32 GetEntityIndex(elg_uint32 entity_id) const;
  void DestroyEntity(elg_uint32 entity_id_index);

 private:
  // Data members
  elg_uint32 m_entity_ids_[MaxEntities];
  elg_uint32 m_active_[MaxEntities];
  elg_uint32 m_head_;
  elg_uint32 m_top_;

  // Disallow copy and assign
  EntityPool(const EntityPool&);
  void operator=(const EntityPool&);
};

}  // namespace EntityManager
}  // namespace Elg

#include "Elg/EntityManager/EntityPool/EntityPool-inl.h"

#endif  // ELG_ENTITYMANAGER_ENTITYPOOL_ENTITYPOOL_H_
