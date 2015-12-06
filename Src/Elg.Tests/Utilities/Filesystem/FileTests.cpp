/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#pragma warning(pop)

#include <UnitTest++.h>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Filesystem/File.h"

TEST(Elg_File_Something) {
  // Prepare path
  elg_char path[MAX_PATH];
  GetTempFileNameA(".", "TEST", 0, path);

  // Write section
  {
    Elg::Utilities::Filesystem::File write_file =
      Elg::Utilities::Filesystem::File(path, Elg::Utilities::Filesystem::FILE_ACCESS_MODE_WRITE);

    CHECK_EQUAL(static_cast<elg_uint32>(18), write_file.Write("Some test data.\r\n", 18));

    write_file.SeekToBeginning();

    CHECK_EQUAL(static_cast<elg_uint32>(4), write_file.Write("Test", 4));

    write_file.Seek(5);

    CHECK_EQUAL(static_cast<elg_uint32>(4), write_file.Write("some", 4));
  }

  // Read section
  {
    Elg::Utilities::Filesystem::File read_file =
      Elg::Utilities::Filesystem::File(path, Elg::Utilities::Filesystem::FILE_ACCESS_MODE_READ);

    CHECK_EQUAL(static_cast<elg_uint32>(18), read_file.Size());

    elg_char buffer[1024];
    elg_uint32 bytes_read = read_file.Read(buffer, 1024);
    CHECK_EQUAL(static_cast<elg_uint32>(18), bytes_read);
    CHECK_EQUAL("Test some data.\r\n", buffer);
  }

  // Clean up
  DeleteFileA(path);
}
