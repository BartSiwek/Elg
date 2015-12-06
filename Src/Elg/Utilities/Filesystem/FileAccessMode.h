/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_FILESYSTEM_FILEACCESSMODE_H_
#define ELG_UTILITIES_FILESYSTEM_FILEACCESSMODE_H_

namespace Elg {
namespace Utilities {
namespace Filesystem {

enum FileAccessMode {
  FILE_ACCESS_MODE_NONE = 0x00,
  FILE_ACCESS_MODE_READ = 0x01,
  FILE_ACCESS_MODE_WRITE = 0x02,
  FILE_ACCESS_MODE_READ_WRITE = 0x03
};
}  // Elg
}  // Utilities
}  // Filesystem

#endif  // ELG_UTILITIES_FILESYSTEM_FILEACCESSMODE_H_
