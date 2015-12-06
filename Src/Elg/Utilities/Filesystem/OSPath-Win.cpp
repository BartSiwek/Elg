/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#ifdef _WIN32

#include "Elg/Utilities/Filesystem/OSPath.h"

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#include <direct.h>
#pragma warning(pop)

#include <sys/types.h>
#include <sys/stat.h>

#include "Elg/Utilities/Asserts.h"
#include "Elg/Utilities/Filesystem/Path.h"

namespace Elg {
namespace Utilities {
namespace Filesystem {

Path GetWorkingDirectoryPath() {
  elg_char buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];
  elg_char* result = _getcwd(buffer, Elg::Utilities::Filesystem::Path::PATH_MAX);

  VERIFY_TRUE(result != NULL, "Cannot fetch the working directory");

  return Path(buffer);
}

Path GetExecutablePath() {
  elg_char buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];
  VERIFY_TRUE(GetModuleFileNameA(NULL, buffer, Elg::Utilities::Filesystem::Path::PATH_MAX) != 0,
              "Cannot fetch the executbale path");

  return Path(buffer);
}

bool IsPathAFile(const Path& path) {
  struct _stat stat_buffer;
  VERIFY_TRUE(_stat(path.AsNullTerminatedString(), &stat_buffer) == 0,
              "Cannot retrieve the file attributes for [%s]", path.AsNullTerminatedString());

  return ((stat_buffer.st_mode & S_IFREG) != 0);
}

bool IsPathADirectory(const Path& path) {
  struct _stat stat_buffer;
  VERIFY_TRUE(_stat(path.AsNullTerminatedString(), &stat_buffer) == 0,
              "Cannot retrieve the file attributes for [%s]", path.AsNullTerminatedString());

  return ((stat_buffer.st_mode & S_IFDIR) != 0);
}
}  // Elg
}  // Utilities
}  // Filesystem

#endif  // _WIN32
