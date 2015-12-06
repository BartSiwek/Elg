/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ENTITYMANAGER_ENTITYMANAGER_H_
#define ELG_ENTITYMANAGER_ENTITYMANAGER_H_

#include "Elg/Utilities/Types.h"
#include "Elg/EntityManager/IdMacros.h"
#include "Elg/EntityManager/EntitySet.h"

namespace Elg {
namespace EntityManager {

// Entity manager type
template<typename EntityManagerDescriptionType>
class EntityManager {
 public:
  // Consts & typedefs
  static const elg_uint32 InvalidOffset = ELG_ENTITY_MANAGER_INVALID_ID;
  static const elg_uint32 MaxEntityCount = EntityManagerDescriptionType::MaxEntityCount;

  template<typename CompoentType>
  struct ComponentMaxCount {
    enum { value = EntityManagerDescriptionType::ComponentMaxCount<CompoentType>::value };
  };

  // Constructors
  EntityManager();

  // Destructor
  ~EntityManager();

  // Methods, including static methods [Entity managment]
  inline elg_uint32 CreateEntity();
  inline elg_uint32 GetActiveEntityCount() const;
  inline const elg_uint32* GetActiveEntities() const;
  inline bool IsEntityActive(elg_uint32 entity_id) const;
  inline void DestroyEntity(elg_uint32 entity_id);

  // Methods, including static methods [Component managment]
  template<typename T> inline elg_uint32 CreateComponent(elg_uint32 entity_id);
  template<typename T> inline elg_uint32 GetComponent(elg_uint32 entity_id) const;
  template<typename T> inline bool HasComponent(elg_uint32 entity_id) const;
  template<typename T> inline void DestroyComponent(elg_uint32 entity_id);

  // Methods, including static methods [Component data]
  template<typename T> inline elg_uint32 GetDataCount() const;
  template<typename T> inline const elg_uint32* GetDataEntities() const;
  template<typename T> inline const T* GetData() const;
  template<typename T> inline T* GetData();

  // Methods, including static methods [Serialisation]
  inline void Serialize(FILE* out) const;
  inline void Deserialize(FILE* in);

 private:
  // Data Members [instance]
  EntityManagerDescriptionType m_description_;

  // Disallow copy and assign
  EntityManager(const EntityManager&);
  void operator=(const EntityManager&);
};

}  // namespace Elg
}  // namespace EntityManager

#include "Elg/EntityManager/EntityManager-inl.h"

#endif  // ELG_ENTITYMANAGER_ENTITYMANAGER_H_
