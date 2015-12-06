/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_FILESYSTEM_PATH_H_
#define ELG_UTILITIES_FILESYSTEM_PATH_H_

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

/*
TODO someday:
const char** GetChildren(const char* path);  // OS
const char** GetRoots();  // OS
*/

namespace Elg {
namespace Utilities {
namespace Filesystem {

class Path {
 public:
  // Consts
  static const elg_uint32 PATH_MAX = 1024;  // Should probably be as big a MAX_PATH/PATH_MAX from OS
  static const elg_char PATH_SEPARATOR = '/';

  // Constructors
  Path();
  explicit Path(const elg_char* path);
  Path(const elg_char* first, const elg_char* last);
  Path(const Path& other);

  // Destructors (the default generated destructor is okay)

  // Operators
  Path& operator=(const Path& other);

  // Member functions [instance]
  const elg_char* AsNullTerminatedString() const;
  elg_char* AsNullTerminatedString();
  elg_uint32 Length() const;

  void Append(const elg_char* path);
  void Append(const Path& path);
  void ConvertToAbsolute();

  void GetParent(elg_char* output) const;
  Path GetParent() const;
  void GetFullFilename(elg_char* output) const;
  Path GetFullFilename() const;
  void GetFilename(elg_char* output) const;
  Path GetFilename() const;
  void GetRoot(elg_char* output) const;
  Path GetRoot() const;
  void GetExtension(elg_char* output) const;

  void RemoveTrailingSeparator();
  void RemoveFullFilename();
  void RemoveExtension();

  void ChangeExtension(const elg_char* new_extension);

  // Member functions [static]


 private:
  // Consts
  static const elg_char STRING_TERMINATOR = '\0';
  static const elg_char UNIX_SEPARATOR = '/';
  static const elg_char WINDOWS_SEPARATOR = '\\';

  // Member functions
  ELG_FORCEINLINE static const elg_char* SkipSeparators(const elg_char* path);

  ELG_FORCEINLINE const elg_char* PushBackNextChar(const elg_char* path);

  ELG_FORCEINLINE elg_uint32 ConvertToAbsoluteDot(elg_uint32 segment_count, elg_char* segment_end,
                                                  elg_char* old_path_end);
  ELG_FORCEINLINE elg_uint32 ConvertToAbsoluteDotDot(elg_uint32 segment_count, elg_char* segment_end,
                                                     elg_char* old_path_end);
  ELG_FORCEINLINE elg_uint32 ConvertToAbsoluteLiteral(elg_uint32 segment_count, elg_char* current,
                                                      elg_char* segment_end, elg_char* old_path_end);

  ELG_FORCEINLINE const elg_char* GetParentBound() const;

  ELG_FORCEINLINE const elg_char* GetFullFilenameBound() const;
  ELG_FORCEINLINE elg_char* GetFullFilenameBound();

  ELG_FORCEINLINE const elg_char* GetExtensionBound() const;

  ELG_FORCEINLINE const elg_char* GetLastDotPosition() const;
  ELG_FORCEINLINE elg_char* GetLastDotPosition();

  ELG_FORCEINLINE const elg_char* GetRootBound() const;

  // Data members
  elg_char m_path_[PATH_MAX + 1];
  elg_char* m_path_end_;
};

Path CombinePaths(const elg_char* prefix, const elg_char* suffix);
Path CombinePaths(const elg_char* prefix, const Path& suffix);
Path CombinePaths(const Path& prefix, const elg_char* suffix);
Path CombinePaths(const Path& prefix, const Path& suffix);
}  // Filesystem
}  // Utilities
}  // Elg

#endif  // ELG_UTILITIES_FILESYSTEM_PATH_H_
