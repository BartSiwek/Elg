/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_ASSETMANAGER_ASSETS_IMAGE_H_
#define ELG_ASSETMANAGER_ASSETS_IMAGE_H_

#include <cstring>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"
#include "Elg/Memory/MallocAllocator.h"
#include "Elg/Memory/Memory.h"

namespace Elg {
namespace AssetManager {
namespace Assets {

class Image {
 public:
  // Constants and enums
  enum ImageFormat {
    RGB,
    RGBA
  };

  static const elg_uint32 CHANNEL_COUNT = 4;

  // Constructors
  Image(elg_uint32 width, elg_uint32 height, ImageFormat format, unsigned char *data, unsigned char *storage)
      : m_width_(width), m_height_(height), m_data_(storage) {
    if (format == RGB) {
      // Add extra channel
      elg_uint32 pixel_count = width * height;
      elg_uint32 pixel_index = 0;
      elg_uint32 three_channel_offset = 0;
      elg_uint32 four_channel_offset = 0;
      while (pixel_index < pixel_count) {
        std::memcpy(m_data_ + four_channel_offset, data + three_channel_offset, 3);
        m_data_[four_channel_offset + 3] = 255;

        ++pixel_index;
        three_channel_offset += 3;
        four_channel_offset += 4;
      }
    } else {
      // Just copy
      elg_uint32 size = width * height * CHANNEL_COUNT;
      std::memcpy(m_data_, data, size);
    }
  }

  // Destructors
  ~Image() {
    m_data_ = NULL;
  }

  // Methods, including static methods
  elg_uint32 width() const {
    return m_width_;
  }

  elg_uint32 height() const {
    return m_height_;
  }

  elg_uint32 channel_count() const {
    return CHANNEL_COUNT;
  }

  unsigned char* data() const {
    return m_data_;
  }

  elg_uint32 pitch() {
    return width() * channel_count();
  }

 private:
  // Data members
  elg_uint32 m_width_;
  elg_uint32 m_height_;
  unsigned char *m_data_;

  // Disallow copy and assign
  Image(const Image& orig);
  void operator=(const Image&);
};

}  // namespace Assets
}  // namespace AssetManager
}  // namespace Elg

#endif  // ELG_ASSETMANAGER_ASSETS_IMAGE_H_
