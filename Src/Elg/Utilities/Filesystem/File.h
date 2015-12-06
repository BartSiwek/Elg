/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_FILESYSTEM_FILE_H_
#define ELG_UTILITIES_FILESYSTEM_FILE_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Filesystem/FileAccessMode.h"
#include "Elg/Utilities/Filesystem/FileHandle.h"

namespace Elg {
namespace Utilities {
namespace Filesystem {

// elg_uint32 is used for sizes and offsets - unlikely we will need files bigger than 4gb
class File {
 public:
  // Consts
  static const elg_uint32 NPOS = 0xFFFFFFFF;

  // Constructor
  File(const char* path, FileAccessMode access_mode);

  // Destructor
  ~File(void);

  // Get the file size
  elg_uint32 Size() const;

  // Synchronously reads from the file into a buffer. Returns the number of bytes read, or 0 if failed.
  elg_uint32 Read(void* buffer, elg_uint32 length);

  // Synchronously writes from a buffer into the file. Returns the number of bytes written, or 0 if failed.
  elg_uint32 Write(const void* buffer, elg_uint32 length);

  // Seeks to the desired position
  void Seek(elg_uint32 position);

  // Seeks to the end of the file
  void SeekToEnd();

  // Seeks to the beginning of the file
  void SeekToBeginning();

  // Skips a certain amount of bytes
  void Skip(elg_uint32 bytes);

  // Returns the current position in the file, or NPOS (0xFFFFFFFF) if the operation failed.
  elg_uint32 Tell() const;

 private:
  FileHandle m_file_handle_;
};
}  // Elg
}  // Utilities
}  // Filesystem

#endif  // ELG_UTILITIES_FILESYSTEM_FILE_H_
