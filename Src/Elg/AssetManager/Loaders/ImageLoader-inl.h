/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_LOADERS_IMAGELOADER_INL_H_
#define ELG_ASSETMANAGER_LOADERS_IMAGELOADER_INL_H_

#include "Elg/AssetManager/Loaders/ImageLoader.h"

#include <cstring>
#include <cstdio>

// Include STBI library
#define STBI_HEADER_FILE_ONLY
#include "Elg/External/stb_image/stb_image.c"
#undef STBI_HEADER_FILE_ONLY

#include "Elg/Utilities/StringHash/Hash.h"
#include "Elg/Memory/Memory.h"
#include "Elg/AssetManager/Assets/Image.h"

namespace Elg {
namespace AssetManager {
namespace Loaders {

// Constants
template<bool IsBigEndian>
const elg_uint32 ImageLoader<IsBigEndian>::ASSET_TYPE_ID_HASH = ELG_STRING_HASH("Image");

// Constructors
template<bool IsBigEndian>
ImageLoader<IsBigEndian>::ImageLoader() {
}

// Destructors
template<bool IsBigEndian>
ImageLoader<IsBigEndian>::~ImageLoader() {
}

template<bool IsBigEndian>
template<typename AllocatorType>
Elg::AssetManager::Assets::Image* ImageLoader<IsBigEndian>::Load(const elg_char* filename, AllocatorType* allocator) {
  // Open files
  FILE *file;
  fopen_s(&file, filename, "rb");
  ASSERT(file != 0, "Unable to open asset file [%s]", filename);

  // Read the data (data is read in a RGBA order - i.e. big endian)
  elg_int32 width, height, component_count;
  unsigned char *data = stbi_load_from_file(file, &width, &height, &component_count, 0);
  fclose(file);

  ASSERT(component_count == 4 || component_count == 3, "Unable to read image data from file [%s]", filename);

  // Allocate the memory for storage
  unsigned char *storage = ElgNewArray(unsigned char,
                                       width * height * Elg::AssetManager::Assets::Image::CHANNEL_COUNT,
                                       allocator);

  // Store the data into Image
  Elg::AssetManager::Assets::Image* result = NULL;
  if (component_count == 4) {
    AdjustByteOrder(data, width * height, 4);
    result = ElgNew(Elg::AssetManager::Assets::Image, allocator)(width,
                                                                 height,
                                                                 Elg::AssetManager::Assets::Image::RGBA,
                                                                 data,
                                                                 storage);
    ASSERT(result != NULL, "Memory allocation for new Image failed");
    stbi_image_free(data);
  } else if (component_count == 3) {
    AdjustByteOrder(data, width * height, 3);
    result = ElgNew(Elg::AssetManager::Assets::Image, allocator)(width,
                                                                 height,
                                                                 Elg::AssetManager::Assets::Image::RGB,
                                                                 data,
                                                                 storage);
    ASSERT(result != NULL, "Memory allocation for new Image failed");
    stbi_image_free(data);
  }

  return result;
}

template<bool IsBigEndian>
template<typename AllocatorType>
void ImageLoader<IsBigEndian>::Unload(Elg::AssetManager::Assets::Image* image, AllocatorType* allocator) {
  ElgDeleteArray(image.data(), allocator);
  ElgDelete(image, allocator);
}

}  // namespace Loaders
}  // namespace AssetManager
}  // namespace Elg

#endif  // ELG_ASSETMANAGER_LOADERS_IMAGELOADER_INL_H_
