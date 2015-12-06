/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_FILESYSTEM_FILEHANDLE_H_
#define ELG_UTILITIES_FILESYSTEM_FILEHANDLE_H_
#ifdef _WIN32

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#pragma warning(pop)

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Filesystem/FileAccessMode.h"

namespace Elg {
namespace Utilities {
namespace Filesystem {

typedef HANDLE FileHandle;
}  // Elg
}  // Utilities
}  // Filesystem

#endif  // _WIN32
#endif  // ELG_UTILITIES_FILESYSTEM_FILEHANDLE_H_
