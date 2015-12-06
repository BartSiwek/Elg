/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_ASSETDESCRIPTOR_H_
#define ELG_ASSETMANAGER_ASSETDESCRIPTOR_H_

#include <string>

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace AssetManager {

class AssetDescriptor {
 public:
  AssetDescriptor()
      : m_id_hash_(0), m_type_id_hash_(0), m_filename_() {
  }

  AssetDescriptor(elg_uint32 id_hash, elg_uint32 type_id_hash, std::string filename)
      : m_id_hash_(id_hash), m_type_id_hash_(type_id_hash), m_filename_(filename) {
  }

  ~AssetDescriptor() {
  }

  elg_uint32 id_hash() const {
    return m_id_hash_;
  }

  void set_id_hash(elg_uint32 id_hash) {
    m_id_hash_ = id_hash;
  }

  elg_uint32 type_id_hash() const {
    return m_type_id_hash_;
  }

  void set_type_id_hash(elg_uint32 type_id_hash) {
    m_type_id_hash_ = type_id_hash;
  }

  std::string filename() const {
    return m_filename_;
  }

  void set_filename(const std::string& filename) {
    m_filename_ = filename;
  }

 private:
  elg_uint32 m_id_hash_;
  elg_uint32 m_type_id_hash_;
  std::string m_filename_;
};

}  // namespace AssetManager
}  // namespace Elg

#endif  // ELG_ASSETMANAGER_ASSETDESCRIPTOR_H_
