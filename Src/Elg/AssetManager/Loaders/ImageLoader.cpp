/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */
#include "Elg/AssetManager/Loaders/ImageLoader.h"

#include <algorithm>

namespace Elg {
namespace AssetManager {
namespace Loaders {

template<>
void ImageLoader<true>::AdjustByteOrder(unsigned char * /* data */, elg_uint32 /* pixel_count */,
                                        elg_uint32 /* channel_count */) {
}

template<>
void ImageLoader<false>::AdjustByteOrder(unsigned char *data, elg_uint32 pixel_count, elg_uint32 channel_count) {
  elg_uint32 data_size = pixel_count * channel_count;
  elg_uint32 pixel_offset = 0;
  while (pixel_offset < data_size) {
    std::reverse(data + pixel_offset, data + pixel_offset + channel_count);
    pixel_offset += channel_count;
  }
}

}  // namespace Loaders
}  // namespace AssetManager
}  // namespace Elg
