/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#include "Elg/Utilities/Filesystem/Path.h"

#include <cstring>

#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace Utilities {
namespace Filesystem {

Path::Path() : m_path_end_(m_path_) {
  // Put the NULL at the end (so we can return this as a string without any more fuss)
  *m_path_end_ = STRING_TERMINATOR;
}

Path::Path(const elg_char* path) : m_path_end_(m_path_) {
  ASSERT(std::strlen(path) <= PATH_MAX, "The path length must not exceed MAX_PATH");

  while (*path != STRING_TERMINATOR) {
    path = PushBackNextChar(path);
  }

  // Put the NULL at the end (so we can return this as a string without any more fuss)
  *m_path_end_ = STRING_TERMINATOR;
}

Path::Path(const elg_char* first, const elg_char* last) : m_path_end_(m_path_) {
  ASSERT((last - first) <= PATH_MAX, "The path length must not exceed MAX_PATH");

  elg_uint32 path_length = static_cast<elg_uint32>(last - first);
  std::memcpy(m_path_, first, path_length);
  m_path_end_ = m_path_ + path_length;
  *m_path_end_ = STRING_TERMINATOR;
}

Path::Path(const Path& other) : m_path_end_(m_path_) {
  elg_uint32 path_length = static_cast<elg_uint32>(other.m_path_end_ - other.m_path_);
  std::memcpy(m_path_, other.m_path_, path_length + 1);
  m_path_end_ = m_path_ + path_length;
}

Path& Path::operator=(const Path& other) {
  if (this != &other) {
    elg_uint32 path_length = static_cast<elg_uint32>(other.m_path_end_ - other.m_path_);
    std::memcpy(m_path_, other.m_path_, path_length + 1);
    m_path_end_ = m_path_ + path_length;
  }

  return *this;
}

const elg_char* Path::AsNullTerminatedString() const {
  return m_path_;
}

elg_char* Path::AsNullTerminatedString() {
  return m_path_;
}

elg_uint32 Path::Length() const {
  return static_cast<elg_uint32>(m_path_end_ - m_path_);
}

void Path::Append(const elg_char* path) {
  ASSERT((m_path_end_ - m_path_) + std::strlen(path) <= PATH_MAX, "The path length must not exceed MAX_PATH");

  // If both prefix and suffix are not empty and prefix does not end with and separator - append it
  if (!(m_path_end_ == m_path_) && (*path != STRING_TERMINATOR) && (*(m_path_end_ - 1) != PATH_SEPARATOR)) {
    *m_path_end_ = PATH_SEPARATOR;
    ++m_path_end_;
  }

  // If the prefix is not empty skip all the separators at the start
  if (!(m_path_end_ == m_path_)) {
    path = SkipSeparators(path);
  }

  // Append the input
  while (*path != STRING_TERMINATOR) {
    path = PushBackNextChar(path);
  }

  // Append the final NUL
  *m_path_end_ = STRING_TERMINATOR;
}

void Path::Append(const Path& path) {
  Append(&path.m_path_[0]);
}

void Path::ConvertToAbsolute() {
  // The algorithm variables
  elg_uint32 segment_count = 0;
  elg_char* current = m_path_;
  elg_char* old_path_end = m_path_end_;

  // Reset the path end - it will be used as a insertion point
  m_path_end_ = m_path_;

  // Iterate over segments
  while (current <= old_path_end) {
    // Find the end of the segment
    elg_char* segment_end = current;
    while ((segment_end < old_path_end) && (*segment_end != PATH_SEPARATOR)) {
      ++segment_end;
    }

    // Get the length
    elg_uint32 segment_length = static_cast<elg_uint32>(segment_end - current);

    // Act on different possibilities
    if (segment_length == 1 && current[0] == '.') {
      segment_count = ConvertToAbsoluteDot(segment_count, segment_end, old_path_end);
    } else if (segment_length == 2 && current[0] == '.' && current[1] == '.') {
      segment_count = ConvertToAbsoluteDotDot(segment_count, segment_end, old_path_end);
    } else {
      segment_count = ConvertToAbsoluteLiteral(segment_count, current, segment_end, old_path_end);
    }

    // Move further
    current = segment_end + 1;
  }

  // Empty path should give a single separator
  if (m_path_end_ == m_path_) {
    *m_path_end_ = PATH_SEPARATOR;
    ++m_path_end_;
  }

  // Finish up the string
  *m_path_end_ = '\0';
}

void Path::GetParent(elg_char* output) const {
  const elg_char* bound = GetParentBound();
  elg_uint32 parent_length = static_cast<elg_uint32>(bound - m_path_);
  std::memcpy(output, m_path_, parent_length);
  *(output + parent_length) = STRING_TERMINATOR;
}

Path Path::GetParent() const {
  const elg_char* bound = GetParentBound();
  return Path(m_path_, bound);
}

void Path::GetFullFilename(elg_char* output) const {
  const elg_char* bound = GetFullFilenameBound();
  elg_uint32 filename_length = static_cast<elg_uint32>(m_path_end_ - bound);
  std::memcpy(output, bound, filename_length);
  *(output + filename_length) = STRING_TERMINATOR;
}

Path Path::GetFullFilename() const {
  const elg_char* bound = GetFullFilenameBound();
  return Path(bound, m_path_end_);
}

void Path::GetFilename(elg_char* output) const {
  const elg_char* bound = GetFullFilenameBound();
  const elg_char* dot = GetLastDotPosition();
  elg_uint32 filename_length = static_cast<elg_uint32>(dot - bound);
  std::memcpy(output, bound, filename_length);
  *(output + filename_length) = STRING_TERMINATOR;
}

Path Path::GetFilename() const {
  const elg_char* bound = GetFullFilenameBound();
  const elg_char* dot = GetLastDotPosition();
  return Path(bound, dot);
}

void Path::GetRoot(elg_char* output) const {
  const elg_char* bound = GetRootBound();
  elg_uint32 root_length = static_cast<elg_uint32>(bound - m_path_);
  std::memcpy(output, m_path_, root_length);
  *(output + root_length) = STRING_TERMINATOR;
}

Path Path::GetRoot() const {
  const elg_char* bound = GetRootBound();
  return Path(m_path_, bound);
}

void Path::GetExtension(elg_char* output) const {
  const elg_char* bound = GetExtensionBound();
  elg_uint32 extension_length = static_cast<elg_uint32>(m_path_end_ - bound);
  std::memcpy(output, bound, extension_length);
  *(output + extension_length) = STRING_TERMINATOR;
}

void Path::RemoveTrailingSeparator() {
  if (m_path_end_ > m_path_ && *(m_path_end_ - 1) == PATH_SEPARATOR) {
    --m_path_end_;
    *m_path_end_ = STRING_TERMINATOR;
  }
}

void Path::RemoveFullFilename() {
  elg_char* bound = GetFullFilenameBound();
  m_path_end_ = bound;
  *m_path_end_ = STRING_TERMINATOR;
}

void Path::RemoveExtension() {
  elg_char* bound = GetLastDotPosition();
  m_path_end_ = bound;
  *m_path_end_ = STRING_TERMINATOR;
}

void Path::ChangeExtension(const elg_char* new_extension) {
  // Find out where is the dot in out current path
  elg_char* bound = GetLastDotPosition();

  // Append path only if there is something before the dot that is not a separator
  if (bound != m_path_ && *(bound - 1) != PATH_SEPARATOR) {
    // Assert we got enough space (a bit overestimated because of strlen)
    ASSERT((bound - m_path_) + std::strlen(new_extension) + (m_path_end_ == bound) <= PATH_MAX,
           "The path length must not exceed MAX_PATH");

    // Append the dot if we need it
    if (bound == m_path_end_) {
      *bound = '.';
    }
    ++bound;

    // Copy the new extension
    while (*new_extension != STRING_TERMINATOR &&
           *new_extension != WINDOWS_SEPARATOR &&
           *new_extension != UNIX_SEPARATOR) {
        *bound = *new_extension;
        ++bound;
        ++new_extension;
    }

    // Finish up with a NUL
    m_path_end_ = bound;
    *m_path_end_ = STRING_TERMINATOR;
  }
}

ELG_FORCEINLINE const elg_char* Path::SkipSeparators(const elg_char* path) {
  while (*path == WINDOWS_SEPARATOR || *path == UNIX_SEPARATOR) {
    ++path;
  }
  return path;
}

ELG_FORCEINLINE const elg_char* Path::PushBackNextChar(const elg_char* path) {
  if (*path == WINDOWS_SEPARATOR || *path == UNIX_SEPARATOR) {
    // Put ONE separator at the insertion point, advance insertion point by one, and a current character to the end
    path = SkipSeparators(path);
    *m_path_end_ = PATH_SEPARATOR;
    ++m_path_end_;
    return path;
  } else {
    // A regular character - move it to a insertion location and advance both pointers
    *m_path_end_ = *path;
    ++m_path_end_;
    return(path + 1);
  }
}

ELG_FORCEINLINE elg_uint32 Path::ConvertToAbsoluteDot(elg_uint32 segment_count, elg_char* segment_end,
                                                  elg_char* old_path_end) {
  if (segment_count >= 1) {
    // We have ...-separator-dot - remove the dot and separator to the left
    --m_path_end_;
    --segment_count;

    // Add separator to the right if needed
    if (segment_end < old_path_end) {
      *m_path_end_ = PATH_SEPARATOR;
      ++m_path_end_;
      ++segment_count;
    }
  }  // else - We have dot-... - just skip it

  return segment_count;
}

ELG_FORCEINLINE elg_uint32 Path::ConvertToAbsoluteDotDot(elg_uint32 segment_count, elg_char* segment_end,
                                                     elg_char* old_path_end) {
  if (segment_count >= 3) {
    // We have ...-separator-literal-separator-dotdot - take the ones to the left
    segment_count -= 3;
    m_path_end_ -= 2;
    while (*m_path_end_ != PATH_SEPARATOR) {
      --m_path_end_;
    }
    // We do not substract 1 cause we are already in a spot where we will overwrite the seaparator

    // Add separator the one to the right if needed
    if (segment_end < old_path_end) {
      *m_path_end_ = PATH_SEPARATOR;
      ++m_path_end_;
      ++segment_count;
    }
  } else if (segment_count > 0) {
    // We have literal-separator-dotdot - take the ones to the left and don't add a separator
    segment_count = 0;
    m_path_end_ = m_path_;

    // Add separator the one to the right if needed
    if (segment_end < old_path_end) {
      *m_path_end_ = PATH_SEPARATOR;
      ++m_path_end_;
      ++segment_count;
    }
  }  // else - We have dotdot-... - just skip it

  return segment_count;
}

ELG_FORCEINLINE elg_uint32 Path::ConvertToAbsoluteLiteral(elg_uint32 segment_count, elg_char* current,
                                                      elg_char* segment_end, elg_char* old_path_end) {
  // The LITERAL
  while (current != segment_end) {
    *m_path_end_ = *current;
    ++m_path_end_;
    ++current;
  }
  segment_count++;

  // Add separator the one to the right if needed
  if (segment_end < old_path_end) {
    *m_path_end_ = PATH_SEPARATOR;
    ++m_path_end_;
    ++segment_count;
  }

  return segment_count;
}

ELG_FORCEINLINE const elg_char* Path::GetParentBound() const {
  if (m_path_end_ - m_path_ == 0) {
    return m_path_;
  } else if (m_path_end_ - m_path_ == 1) {
    if (*m_path_ == PATH_SEPARATOR) {
      return m_path_end_;
    } else {
      return m_path_;
    }
  } else {
    // Start before tailing NUL
    const elg_char* bound = m_path_end_ - 1;  // We got at least two characters

    // If there is a tailing separator - skip it
    if (*bound == PATH_SEPARATOR) {
      --bound;
    }

    // Find last separator
    while ((bound >= m_path_) && (*bound != PATH_SEPARATOR)) {
      --bound;
    }

    return bound + 1;
  }
}

ELG_FORCEINLINE const elg_char* Path::GetFullFilenameBound() const {
  // Find the last separator
  const elg_char* bound = m_path_end_;
  while ((bound > m_path_) && (*(bound - 1) != PATH_SEPARATOR)) {
    --bound;
  }

  return bound;
}

ELG_FORCEINLINE elg_char* Path::GetFullFilenameBound() {
  // Find the last separator
  elg_char* bound = m_path_end_;
  while ((bound > m_path_) && (*(bound - 1) != PATH_SEPARATOR)) {
    --bound;
  }

  return bound;
}

ELG_FORCEINLINE const elg_char* Path::GetExtensionBound() const {
  // Find the last dot
  const elg_char* bound = m_path_end_;
  while ((bound > m_path_) && (*(bound - 1) != PATH_SEPARATOR) && (*(bound - 1) != '.')) {
    --bound;
  }

  if ((bound != m_path_) && (*(bound - 1) != PATH_SEPARATOR)) {
    return bound;
  } else {
    return m_path_end_;
  }
}

ELG_FORCEINLINE const elg_char* Path::GetLastDotPosition() const {
  // Find the last dot
  const elg_char* bound = m_path_end_;
  while ((bound > m_path_) && (*(bound - 1) != PATH_SEPARATOR) && (*(bound - 1) != '.')) {
    --bound;
  }

  if ((bound != m_path_) && (*(bound - 1) != PATH_SEPARATOR)) {
    return bound - 1;
  } else {
    return m_path_end_;
  }
}

ELG_FORCEINLINE elg_char* Path::GetLastDotPosition() {
  // Find the last dot
  elg_char* bound = m_path_end_;
  while ((bound > m_path_) && (*(bound - 1) != PATH_SEPARATOR) && (*(bound - 1) != '.')) {
    --bound;
  }

  if ((bound != m_path_) && (*(bound - 1) != PATH_SEPARATOR)) {
    return bound - 1;
  } else {
    return m_path_end_;
  }
}

ELG_FORCEINLINE const elg_char* Path::GetRootBound() const {
  // Find the first separator
  const elg_char* bound = m_path_;
  while ((bound < m_path_end_) && (*bound != PATH_SEPARATOR)) {
    ++bound;
  }

  // We want the separator if its there
  if (bound != m_path_end_) {
    ++bound;
  }

  return bound;
}

Path CombinePaths(const elg_char* prefix, const elg_char* suffix) {
  Path result(prefix);
  result.Append(suffix);
  return result;
}

Path CombinePaths(const elg_char* prefix, const Path& suffix) {
  Path result(prefix);
  result.Append(suffix);
  return result;
}

Path CombinePaths(const Path& prefix, const elg_char* suffix) {
  Path result(prefix);
  result.Append(suffix);
  return result;
}

Path CombinePaths(const Path& prefix, const Path& suffix) {
  Path result(prefix);
  result.Append(suffix);
  return result;
}
}  // Elg
}  // Utilities
}  // Filesystem
