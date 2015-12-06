/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_ASSETS_MESH_H_
#define ELG_ASSETMANAGER_ASSETS_MESH_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace AssetManager {
namespace Assets {

struct VertexFormat {
};

struct SubMesh {
  elg_uint32 VertexCount;
  elg_uint32 VertexSize;
  float* VertexData;
  elg_uint32 IndexCount;
  elg_uint32* IndexData;
  VertexFormat format;
};

struct Mesh {
  elg_uint32 SubMeshCount;
  SubMesh* SubMeshes;
};

}  // namespace Assets
}  // namespace AssetManager
}  // namespace Elg

#endif  // ELG_ASSETMANAGER_ASSETS_MESH_H_
