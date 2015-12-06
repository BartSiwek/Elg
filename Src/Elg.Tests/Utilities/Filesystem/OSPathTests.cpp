/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include <cstdio>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Filesystem/Path.h"
#include "Elg/Utilities/Filesystem/OSPath.h"

TEST(Path_GetWorkingDirectoryPath) {
  Elg::Utilities::Filesystem::Path working_direcotry = Elg::Utilities::Filesystem::GetWorkingDirectoryPath();
  printf("Working directory length = %d\n", working_direcotry.Length());
  printf("Working directory [%s]\n", working_direcotry.AsNullTerminatedString());
}

TEST(Path_GetExecutablePath) {
  Elg::Utilities::Filesystem::Path executable_path = Elg::Utilities::Filesystem::GetExecutablePath();
  printf("Executable path length = %d\n", executable_path.Length());
  printf("Executable path [%s]\n", executable_path.AsNullTerminatedString());
}

TEST(Path_IsPathAFile) {
  Elg::Utilities::Filesystem::Path working_direcotry = Elg::Utilities::Filesystem::GetWorkingDirectoryPath();
  Elg::Utilities::Filesystem::Path executable_path = Elg::Utilities::Filesystem::GetExecutablePath();
  CHECK_EQUAL(true, Elg::Utilities::Filesystem::IsPathAFile(executable_path));
  CHECK_EQUAL(false, Elg::Utilities::Filesystem::IsPathAFile(working_direcotry));
}

TEST(Path_IsPathADirectory) {
  Elg::Utilities::Filesystem::Path working_direcotry = Elg::Utilities::Filesystem::GetWorkingDirectoryPath();
  Elg::Utilities::Filesystem::Path executable_path = Elg::Utilities::Filesystem::GetExecutablePath();
  CHECK_EQUAL(false, Elg::Utilities::Filesystem::IsPathADirectory(executable_path));
  CHECK_EQUAL(true, Elg::Utilities::Filesystem::IsPathADirectory(working_direcotry));
}
