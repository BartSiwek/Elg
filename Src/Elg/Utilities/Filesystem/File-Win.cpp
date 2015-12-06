/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#ifdef _WIN32

#pragma warning(push)
#pragma warning(disable : 6540)
#include <windows.h>
#pragma warning(pop)

#include "Elg/Utilities/Asserts.h"
#include "Elg/Utilities/Filesystem/File.h"

namespace Elg {
namespace Utilities {
namespace Filesystem {

// Constructor
File::File(const char* path, FileAccessMode access_mode) : m_file_handle_(INVALID_HANDLE_VALUE) {
  DWORD access_flags = 0;
  DWORD share_mode = 0;
  DWORD creation_disposition = 0;
  if ((access_mode & FILE_ACCESS_MODE_READ) != 0) {
    access_flags |= GENERIC_READ;
    share_mode = FILE_SHARE_READ;
    creation_disposition = OPEN_EXISTING;
  }
  if ((access_mode & FILE_ACCESS_MODE_WRITE) != 0) {
    access_flags |= GENERIC_WRITE;
    share_mode = 0;
    creation_disposition = OPEN_ALWAYS;
  }

  m_file_handle_ = CreateFileA(path, access_flags, share_mode, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL,
                               NULL);

  ASSERT(m_file_handle_ != INVALID_HANDLE_VALUE, "Cannot open file [%s]", path);
}

// Destructor
File::~File(void) {
  CloseHandle(m_file_handle_);
}

// Get the file size (4GB max should be enough)
elg_uint32 File::Size() const {
  return static_cast<elg_uint32>(GetFileSize(m_file_handle_, NULL));
}

// Synchronously reads from the file into a buffer. Returns the number of bytes read, or 0 if the operation failed.
elg_uint32 File::Read(void* buffer, elg_uint32 length) {
  DWORD bytes_read;
  BOOL read_ok = ReadFile(m_file_handle_, buffer, length, &bytes_read, NULL);

  VERIFY_TRUE(read_ok, "Cannot read from file");

  return static_cast<elg_uint32>(bytes_read);
}

// Synchronously writes from a buffer into the file. Returns the number of bytes written, or 0 if the operation failed.
elg_uint32 File::Write(const void* buffer, elg_uint32 length) {
  DWORD bytes_written;
  VERIFY_TRUE(WriteFile(m_file_handle_, buffer, length, &bytes_written, NULL), "Cannot write to file");
  return static_cast<elg_uint32>(bytes_written);
}

// Seeks to the desired position
void File::Seek(elg_uint32 position) {
  VERIFY_TRUE(SetFilePointer(m_file_handle_, position, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER,
              "Error seeking to a position %d", position);
}

// Seeks to the end of the file
void File::SeekToEnd() {
  VERIFY_TRUE(SetFilePointer(m_file_handle_, 0, NULL, FILE_END) != INVALID_SET_FILE_POINTER, "Error seeking to end");
}

// Seeks to the beginning of the file
void File::SeekToBeginning() {
  VERIFY_TRUE(SetFilePointer(m_file_handle_, 0, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER,
              "Error seeking to beginning");
}

// Skips a certain amount of bytes
void File::Skip(elg_uint32 bytes) {
  VERIFY_TRUE(SetFilePointer(m_file_handle_, bytes, NULL, FILE_CURRENT) != INVALID_SET_FILE_POINTER,
              "Error skipping %d bytes", bytes);
}

// Returns the current position in the file, or NPOS (0xFFFFFFFF) if the operation failed.
elg_uint32 File::Tell() const {
  return static_cast<elg_uint32>(SetFilePointer(m_file_handle_, 0, NULL, FILE_CURRENT));
}
}  // Elg
}  // Utilities
}  // Filesystem


#endif  // _WIN32
