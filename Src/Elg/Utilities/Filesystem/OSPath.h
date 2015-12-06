/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_FILESYSTEM_OSPATH_H_
#define ELG_UTILITIES_FILESYSTEM_OSPATH_H_

// Forward declarations
namespace Elg { namespace Utilities { namespace Filesystem { class Path; } } }

namespace Elg {
namespace Utilities {
namespace Filesystem {

Path GetWorkingDirectoryPath();
Path GetExecutablePath();

bool IsPathAFile(const Path& path);
bool IsPathADirectory(const Path& path);
}  // Filesystem
}  // Utilities
}  // Elg

#endif  // ELG_UTILITIES_FILESYSTEM_OSPATH_H_
