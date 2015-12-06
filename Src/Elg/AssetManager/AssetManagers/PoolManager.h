/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_ASSETMANAGERS_POOLMANAGER_H_
#define ELG_ASSETMANAGER_ASSETMANAGERS_POOLMANAGER_H_

#include <string>

#include "Elg/Utilities/Types.h"
#include "Elg/Clock/TimePoint.h"
#include "Elg/Clock/GameClock.h"

// Forward declarations
namespace Elg { namespace AssetManager { class AssetDescriptor; } }

// Class declaration
namespace Elg {
namespace AssetManager {
namespace AssetManagers {

template<typename Loader, elg_uint32 PoolSize>
class PoolManager {
 public:
  // Typedefs
  typedef typename Loader::loaded_type asset_type;

  // Constructors
  explicit PoolManager(const Elg::AssetManager::AssetDescriptor *asset_descriptors, elg_uint32 asset_descriptor_count);

  // Destructors
  virtual ~PoolManager();

  // Methods, including static methods
  elg_uint32 Get(elg_uint32 id_hash);
  typename Loader::loaded_type* GetData(elg_uint32 internal_id);

 private:
  // Typedefs
  class AssetDescriptorComparator {
   public:
    // Methods, including static methods
    bool operator()(const AssetDescriptor* lhs, const AssetDescriptor* rhs);
  };

  // Methods, including static methods
  elg_uint32 FreeSlot();
  void LoadIntoSlot(elg_uint32 internal_id, elg_uint32 slot);
  void UpdateUsageTime(elg_uint32 internal_id);

  static bool HasNoDuplicates(const AssetDescriptor** descriptors, elg_uint32 count);

  // Data Members [constant after construction]
  elg_uint32 m_asset_id_count_;
  elg_uint32* m_asset_id_hashes_;
  std::string* m_filenames_;

  // Data Members [Internal id <-> pool mapping]
  elg_uint32* m_internal_id_to_pool_slot_;
  elg_uint32 m_pool_slot_to_internal_id_[PoolSize];

  // Data Members [Asset managment]
  typename Elg::Clock::GameClock::TimePoint m_pool_usage_[PoolSize];
  typename Loader::loaded_type* m_pool_[PoolSize];

  // Data Members [Loader]
  Loader m_loader_;

  // Disallow copy and assign
  PoolManager(const PoolManager& orig);
  void operator=(const PoolManager&);
};

}  // namespace AssetManagers
}  // namespace AssetManager
}  // namespace Elg

#include "Elg/AssetManager/AssetManagers/PoolManager-inl.h"

#endif  // ELG_ASSETMANAGER_ASSETMANAGERS_POOLMANAGER_H_
