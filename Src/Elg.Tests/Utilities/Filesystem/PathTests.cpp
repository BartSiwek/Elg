/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Filesystem/Path.h"

TEST(Path_Construction) {
  Elg::Utilities::Filesystem::Path path1("/aa//bb\\ccc\\\\dddd/eee/f//\\/gg/");
  CHECK_EQUAL("/aa/bb/ccc/dddd/eee/f/gg/", path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(25), path1.Length());

  Elg::Utilities::Filesystem::Path path2("\\/\\aa/bb/ccc");
  CHECK_EQUAL("/aa/bb/ccc", path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(10), path2.Length());

  Elg::Utilities::Filesystem::Path path3("/aa/bb/ccc\\/\\");
  CHECK_EQUAL("/aa/bb/ccc/", path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(11), path3.Length());
}

TEST(Path_Construction_CornerCases) {
  Elg::Utilities::Filesystem::Path path1("");  // Has one null char
  CHECK_EQUAL("", path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), path1.Length());

  Elg::Utilities::Filesystem::Path path2("/\\/\\/\\/");
  CHECK_EQUAL("/", path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path2.Length());

  Elg::Utilities::Filesystem::Path path3("aaa");
  CHECK_EQUAL("aaa", path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), path3.Length());
}

TEST(Path_Append_Path) {
  Elg::Utilities::Filesystem::Path prefix_path1("/a/b/c/d");
  Elg::Utilities::Filesystem::Path suffix_path1("e/f/g/h");
  prefix_path1.Append(suffix_path1);
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path1.Length());

  Elg::Utilities::Filesystem::Path prefix_path2("/a/b/c/d/");
  Elg::Utilities::Filesystem::Path suffix_path2("e/f/g/h");
  prefix_path2.Append(suffix_path2);
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path2.Length());

  Elg::Utilities::Filesystem::Path prefix_path3("/a/b/c/d");
  Elg::Utilities::Filesystem::Path suffix_path3("/e/f/g/h");
  prefix_path3.Append(suffix_path3);
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path3.Length());

  Elg::Utilities::Filesystem::Path prefix_path4("/a/b/c/d/");
  Elg::Utilities::Filesystem::Path suffix_path4("/e/f/g/h");
  prefix_path4.Append(suffix_path4);
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path4.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path4.Length());

  Elg::Utilities::Filesystem::Path prefix_path5("");
  Elg::Utilities::Filesystem::Path suffix_path5("e/f/g/h");
  prefix_path5.Append(suffix_path5);
  CHECK_EQUAL("e/f/g/h", prefix_path5.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), prefix_path5.Length());

  Elg::Utilities::Filesystem::Path prefix_path6("");
  Elg::Utilities::Filesystem::Path suffix_path6("/e/f/g/h/");
  prefix_path6.Append(suffix_path6);
  CHECK_EQUAL("/e/f/g/h/", prefix_path6.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(9), prefix_path6.Length());

  Elg::Utilities::Filesystem::Path prefix_path7("/a/b/c/d");
  Elg::Utilities::Filesystem::Path suffix_path7("");
  prefix_path7.Append(suffix_path7);
  CHECK_EQUAL("/a/b/c/d", prefix_path7.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(8), prefix_path7.Length());

  Elg::Utilities::Filesystem::Path prefix_path8("/a/b/c/d/");
  Elg::Utilities::Filesystem::Path suffix_path8("");
  prefix_path8.Append(suffix_path8);
  CHECK_EQUAL("/a/b/c/d/", prefix_path8.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(9), prefix_path8.Length());
}

TEST(Path_Append_String) {
  Elg::Utilities::Filesystem::Path prefix_path1("/a/b/c/d");
  prefix_path1.Append("e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path1.Length());

  Elg::Utilities::Filesystem::Path prefix_path2("/a/b/c/d/");
  prefix_path2.Append("e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path2.Length());

  Elg::Utilities::Filesystem::Path prefix_path3("/a/b/c/d");
  prefix_path3.Append("/e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path3.Length());

  Elg::Utilities::Filesystem::Path prefix_path4("/a/b/c/d/");
  prefix_path4.Append("/e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", prefix_path4.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), prefix_path4.Length());

  Elg::Utilities::Filesystem::Path prefix_path5("");
  prefix_path5.Append("e/f/g/h");
  CHECK_EQUAL("e/f/g/h", prefix_path5.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), prefix_path5.Length());

  Elg::Utilities::Filesystem::Path prefix_path6("");
  prefix_path6.Append("/e/f/g/h/");
  CHECK_EQUAL("/e/f/g/h/", prefix_path6.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(9), prefix_path6.Length());

  Elg::Utilities::Filesystem::Path prefix_path7("/a/b/c/d");
  prefix_path7.Append("");
  CHECK_EQUAL("/a/b/c/d", prefix_path7.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(8), prefix_path7.Length());

  Elg::Utilities::Filesystem::Path prefix_path8("/a/b/c/d/");
  prefix_path8.Append("");
  CHECK_EQUAL("/a/b/c/d/", prefix_path8.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(9), prefix_path8.Length());
}

TEST(Path_ToAbsolute_Sanity_OneSegment) {
  Elg::Utilities::Filesystem::Path empty_path("");
  empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_path.Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_path.Length());

  Elg::Utilities::Filesystem::Path dot_path(".");
  dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_path.Length());

  Elg::Utilities::Filesystem::Path twodots_path("..");
  twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_path.Length());
}

TEST(Path_ToAbsolute_Sanity_TwoSegments) {
  Elg::Utilities::Filesystem::Path empty_empty_path("/");
  empty_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_empty_path.Length());

  Elg::Utilities::Filesystem::Path empty_literal_path("/a");
  empty_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("/a", empty_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), empty_literal_path.Length());

  Elg::Utilities::Filesystem::Path empty_dot_path("/.");
  empty_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_dot_path.Length());

  Elg::Utilities::Filesystem::Path empty_twodots_path("/..");
  empty_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_twodots_path.Length());

  Elg::Utilities::Filesystem::Path literal_empty_path("b/");
  literal_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("b/", literal_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_empty_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_path("b/a");
  literal_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("b/a", literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_dot_path("b/.");
  literal_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("b", literal_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_dot_path.Length());

  Elg::Utilities::Filesystem::Path literal_twodots_path("b/..");
  literal_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", literal_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_twodots_path.Length());

  Elg::Utilities::Filesystem::Path dot_empty_path("./");
  dot_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_empty_path.Length());

  Elg::Utilities::Filesystem::Path dot_literal_path("./a");
  dot_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", dot_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_literal_path.Length());

  Elg::Utilities::Filesystem::Path dot_dot_path("./.");
  dot_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_dot_path.Length());

  Elg::Utilities::Filesystem::Path dot_twodots_path("./..");
  dot_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_twodots_path.Length());

  Elg::Utilities::Filesystem::Path twodots_empty_path("../");
  twodots_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_empty_path.Length());

  Elg::Utilities::Filesystem::Path twodots_literal_path("../a");
  twodots_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", twodots_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_literal_path.Length());

  Elg::Utilities::Filesystem::Path twodots_dot_path("../.");
  twodots_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_dot_path.Length());

  Elg::Utilities::Filesystem::Path twodots_twodots_path("../..");
  twodots_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_twodots_path.Length());
}

TEST(Path_ToAbsolute_Sanity_ThreeSegments) {
  // Not possible '//'
  // Not possible '//a'
  // Not possible '//.'
  // Not possible '//..'

  Elg::Utilities::Filesystem::Path empty_literal_empty_path("/b/");
  empty_literal_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/b/", empty_literal_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), empty_literal_empty_path.Length());

  Elg::Utilities::Filesystem::Path empty_literal_literal_path("/b/a");
  empty_literal_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("/b/a", empty_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), empty_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path empty_literal_dot_path("/b/.");
  empty_literal_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/b", empty_literal_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), empty_literal_dot_path.Length());

  Elg::Utilities::Filesystem::Path empty_literal_twodots_path("/b/..");
  empty_literal_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_literal_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_literal_twodots_path.Length());

  Elg::Utilities::Filesystem::Path empty_dot_empty_path("/./");
  empty_dot_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_dot_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_dot_empty_path.Length());

  Elg::Utilities::Filesystem::Path empty_dot_literal_path("/./a");
  empty_dot_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("/a", empty_dot_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), empty_dot_literal_path.Length());

  Elg::Utilities::Filesystem::Path empty_dot_dot_path("/./.");
  empty_dot_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_dot_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_dot_dot_path.Length());

  Elg::Utilities::Filesystem::Path empty_dot_twodots_path("/./..");
  empty_dot_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_dot_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_dot_twodots_path.Length());

  Elg::Utilities::Filesystem::Path empty_twodots_empty_path("/../");
  empty_twodots_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_twodots_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_twodots_empty_path.Length());

  Elg::Utilities::Filesystem::Path empty_twodots_literal_path("/../a");
  empty_twodots_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("/a", empty_twodots_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), empty_twodots_literal_path.Length());

  Elg::Utilities::Filesystem::Path empty_twodots_dot_path("/../.");
  empty_twodots_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_twodots_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_twodots_dot_path.Length());

  Elg::Utilities::Filesystem::Path empty_twodots_twodots_path("/../..");
  empty_twodots_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", empty_twodots_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), empty_twodots_twodots_path.Length());

  // Not possible 'a//'
  // Not possible 'a//a'
  // Not possible 'a//.'
  // Not possible 'a//..'

  Elg::Utilities::Filesystem::Path literal_literal_empty_path("c/b/");
  literal_literal_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("c/b/", literal_literal_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), literal_literal_empty_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_literal_path("c/b/a");
  literal_literal_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("c/b/a", literal_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(5), literal_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_dot_path("c/b/.");
  literal_literal_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("c/b", literal_literal_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_dot_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_twodots_path("c/b/..");
  literal_literal_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("c", literal_literal_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_literal_twodots_path.Length());

  Elg::Utilities::Filesystem::Path literal_dot_empty_path("c/./");
  literal_dot_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("c/", literal_dot_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_dot_empty_path.Length());

  Elg::Utilities::Filesystem::Path literal_dot_literal_path("c/./a");
  literal_dot_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("c/a", literal_dot_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_dot_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_dot_dot_path("c/./.");
  literal_dot_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("c", literal_dot_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_dot_dot_path.Length());

  Elg::Utilities::Filesystem::Path literal_dot_twodots_path("c/./..");
  literal_dot_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", literal_dot_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_dot_twodots_path.Length());

  Elg::Utilities::Filesystem::Path literal_twodots_empty_path("c/../");
  literal_twodots_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", literal_twodots_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_twodots_empty_path.Length());

  Elg::Utilities::Filesystem::Path literal_twodots_literal_path("c/../a");
  literal_twodots_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("/a", literal_twodots_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_twodots_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_twodots_dot_path("c/../.");
  literal_twodots_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", literal_twodots_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_twodots_dot_path.Length());

  Elg::Utilities::Filesystem::Path literal_twodots_twodots_path("c/../..");
  literal_twodots_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", literal_twodots_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_twodots_twodots_path.Length());

  // Not possible './/'
  // Not possible './/a'
  // Not possible './/.'
  // Not possible './/..'

  Elg::Utilities::Filesystem::Path dot_literal_empty_path("./b/");
  dot_literal_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("b/", dot_literal_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), dot_literal_empty_path.Length());

  Elg::Utilities::Filesystem::Path dot_literal_literal_path("./b/a");
  dot_literal_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("b/a", dot_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), dot_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path dot_literal_dot_path("./b/.");
  dot_literal_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("b", dot_literal_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_literal_dot_path.Length());

  Elg::Utilities::Filesystem::Path dot_literal_twodots_path("./b/..");
  dot_literal_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_literal_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_literal_twodots_path.Length());

  Elg::Utilities::Filesystem::Path dot_dot_empty_path("././");
  dot_dot_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_dot_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_dot_empty_path.Length());

  Elg::Utilities::Filesystem::Path dot_dot_literal_path("././a");
  dot_dot_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", dot_dot_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_dot_literal_path.Length());

  Elg::Utilities::Filesystem::Path dot_dot_dot_path("././.");
  dot_dot_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_dot_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_dot_dot_path.Length());

  Elg::Utilities::Filesystem::Path dot_dot_twodots_path("././..");
  dot_dot_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_dot_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_dot_twodots_path.Length());

  Elg::Utilities::Filesystem::Path dot_twodots_empty_path("./../");
  dot_twodots_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_twodots_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_twodots_empty_path.Length());

  Elg::Utilities::Filesystem::Path dot_twodots_literal_path("./../a");
  dot_twodots_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", dot_twodots_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_twodots_literal_path.Length());

  Elg::Utilities::Filesystem::Path dot_twodots_dot_path("./../.");
  dot_twodots_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_twodots_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_twodots_dot_path.Length());

  Elg::Utilities::Filesystem::Path dot_twodots_twodots_path("./../..");
  dot_twodots_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", dot_twodots_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), dot_twodots_twodots_path.Length());

  // Not possible '..//'
  // Not possible '..//a'
  // Not possible '..//.'
  // Not possible '..//..'

  Elg::Utilities::Filesystem::Path twodots_literal_empty_path("../b/");
  twodots_literal_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("b/", twodots_literal_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), twodots_literal_empty_path.Length());

  Elg::Utilities::Filesystem::Path twodots_literal_literal_path("../b/a");
  twodots_literal_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("b/a", twodots_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), twodots_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path twodots_literal_dot_path("../b/.");
  twodots_literal_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("b", twodots_literal_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_literal_dot_path.Length());

  Elg::Utilities::Filesystem::Path twodots_literal_twodots_path("../b/..");
  twodots_literal_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_literal_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_literal_twodots_path.Length());

  Elg::Utilities::Filesystem::Path twodots_dot_empty_path(".././");
  twodots_dot_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_dot_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_dot_empty_path.Length());

  Elg::Utilities::Filesystem::Path twodots_dot_literal_path(".././a");
  twodots_dot_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", twodots_dot_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_dot_literal_path.Length());

  Elg::Utilities::Filesystem::Path twodots_dot_dot_path(".././.");
  twodots_dot_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_dot_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_dot_dot_path.Length());

  Elg::Utilities::Filesystem::Path twodots_dot_twodots_path(".././..");
  twodots_dot_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_dot_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_dot_twodots_path.Length());

  Elg::Utilities::Filesystem::Path twodots_twodots_empty_path("../../");
  twodots_twodots_empty_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_twodots_empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_twodots_empty_path.Length());

  Elg::Utilities::Filesystem::Path twodots_twodots_literal_path("../../a");
  twodots_twodots_literal_path.ConvertToAbsolute();
  CHECK_EQUAL("a", twodots_twodots_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_twodots_literal_path.Length());

  Elg::Utilities::Filesystem::Path twodots_twodots_dot_path("../../.");
  twodots_twodots_dot_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_twodots_dot_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_twodots_dot_path.Length());

  Elg::Utilities::Filesystem::Path twodots_twodots_twodots_path("../../..");
  twodots_twodots_twodots_path.ConvertToAbsolute();
  CHECK_EQUAL("/", twodots_twodots_twodots_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), twodots_twodots_twodots_path.Length());
}

TEST(Path_ToAbsolute) {
  Elg::Utilities::Filesystem::Path path1("./a/b/c/d");
  path1.ConvertToAbsolute();
  CHECK_EQUAL("a/b/c/d", path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), path1.Length());

  Elg::Utilities::Filesystem::Path path2("/./b/c/d");
  path2.ConvertToAbsolute();
  CHECK_EQUAL("/b/c/d", path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path2.Length());

  Elg::Utilities::Filesystem::Path path3("/a/./c/d");
  path3.ConvertToAbsolute();
  CHECK_EQUAL("/a/c/d", path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path3.Length());

  Elg::Utilities::Filesystem::Path path4("/a/b/./d");
  path4.ConvertToAbsolute();
  CHECK_EQUAL("/a/b/d", path4.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path4.Length());

  Elg::Utilities::Filesystem::Path path5("/a/b/c/.");
  path5.ConvertToAbsolute();
  CHECK_EQUAL("/a/b/c", path5.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path5.Length());

  Elg::Utilities::Filesystem::Path path6("../a/b/c/d");
  path6.ConvertToAbsolute();
  CHECK_EQUAL("a/b/c/d", path6.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), path6.Length());

  Elg::Utilities::Filesystem::Path path7("/../b/c/d");
  path7.ConvertToAbsolute();
  CHECK_EQUAL("/b/c/d", path7.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path7.Length());

  Elg::Utilities::Filesystem::Path path8("/a/../c/d");
  path8.ConvertToAbsolute();
  CHECK_EQUAL("/c/d", path8.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), path8.Length());

  Elg::Utilities::Filesystem::Path path9("/a/b/../d");
  path9.ConvertToAbsolute();
  CHECK_EQUAL("/a/d", path9.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), path9.Length());

  Elg::Utilities::Filesystem::Path path10("/a/b/c/..");
  path10.ConvertToAbsolute();
  CHECK_EQUAL("/a/b", path10.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), path10.Length());

  Elg::Utilities::Filesystem::Path path11("a/../b/c/d");
  path11.ConvertToAbsolute();
  CHECK_EQUAL("/b/c/d", path7.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), path11.Length());

  Elg::Utilities::Filesystem::Path path12("a/./b/c/d");
  path12.ConvertToAbsolute();
  CHECK_EQUAL("a/b/c/d", path12.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), path12.Length());
}

TEST(Path_GetParent) {
  elg_char temp_buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];

  Elg::Utilities::Filesystem::Path empty_path("");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  empty_path.GetParent(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_path("/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_path("a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_path.GetParent(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_path.GetParent(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_literal_path.GetParent(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_literal_path.GetParent(temp_buffer);
  CHECK_EQUAL("a/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_literal_separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  trailing_separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("dir/", temp_buffer);

  Elg::Utilities::Filesystem::Path no_trailing_separator_path("dir/subdir");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  no_trailing_separator_path.GetParent(temp_buffer);
  CHECK_EQUAL("dir/", temp_buffer);
}

TEST(Path_GetParent_Path) {
  Elg::Utilities::Filesystem::Path empty_path("");
  CHECK_EQUAL("", empty_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  CHECK_EQUAL("/", separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  CHECK_EQUAL("", literal_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  CHECK_EQUAL("/", separator_literal_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  CHECK_EQUAL("", literal_separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_separator_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  CHECK_EQUAL("/", separator_literal_separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_separator_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  CHECK_EQUAL("/", separator_literal_literal_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_literal_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  CHECK_EQUAL("a/", literal_separator_literal_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_literal_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  CHECK_EQUAL("", literal_literal_separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_literal_separator_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/");
  CHECK_EQUAL("dir/", trailing_separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), trailing_separator_path.GetParent().Length());

  Elg::Utilities::Filesystem::Path no_trailing_separator_path("dir/subdir");
  CHECK_EQUAL("dir/", no_trailing_separator_path.GetParent().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(4), no_trailing_separator_path.GetParent().Length());
}

TEST(Path_RemoveTrailingSlash) {
  Elg::Utilities::Filesystem::Path empty_path("");
  empty_path.RemoveTrailingSeparator();
  CHECK_EQUAL("", empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  separator_path.RemoveTrailingSeparator();
  CHECK_EQUAL("", separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), separator_path.Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  literal_path.RemoveTrailingSeparator();
  CHECK_EQUAL("a", literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  literal_separator_path.RemoveTrailingSeparator();
  CHECK_EQUAL("a", literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  separator_literal_path.RemoveTrailingSeparator();
  CHECK_EQUAL("/a", separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_path("ab");
  literal_literal_path.RemoveTrailingSeparator();
  CHECK_EQUAL("ab", literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/b");
  literal_separator_literal_path.RemoveTrailingSeparator();
  CHECK_EQUAL("a/b", literal_separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_separator_literal_path.Length());
}

TEST(Path_GetFullFilename) {
  elg_char temp_buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];

  Elg::Utilities::Filesystem::Path empty_path("");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  empty_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_path("/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_path("a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_separator_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_literal_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("aa", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_literal_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_literal_separator_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/file.txt");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  trailing_separator_path.GetFullFilename(temp_buffer);
  CHECK_EQUAL("file.txt", temp_buffer);
}

TEST(Path_GetFullFilename_Path) {
  Elg::Utilities::Filesystem::Path empty_path("");
  CHECK_EQUAL("", empty_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  CHECK_EQUAL("", separator_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), separator_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  CHECK_EQUAL("a", literal_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  CHECK_EQUAL("a", separator_literal_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  CHECK_EQUAL("", literal_separator_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_separator_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  CHECK_EQUAL("", separator_literal_separator_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), separator_literal_separator_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  CHECK_EQUAL("aa", separator_literal_literal_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), separator_literal_literal_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  CHECK_EQUAL("a", literal_separator_literal_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_separator_literal_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  CHECK_EQUAL("", literal_literal_separator_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_literal_separator_path.GetFullFilename().Length());

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/file.txt");
  CHECK_EQUAL("file.txt", trailing_separator_path.GetFullFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(8), trailing_separator_path.GetFullFilename().Length());
}

TEST(Path_GetExtension) {
  elg_char temp_buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];

  Elg::Utilities::Filesystem::Path path1("");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path1.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path2("/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path2.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path3("a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path3.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path4("/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path4.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path5("a.x");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path5.GetExtension(temp_buffer);
  CHECK_EQUAL("x", temp_buffer);

  Elg::Utilities::Filesystem::Path path6("/a.x");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path6.GetExtension(temp_buffer);
  CHECK_EQUAL("x", temp_buffer);

  Elg::Utilities::Filesystem::Path path7("a.x.y");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path7.GetExtension(temp_buffer);
  CHECK_EQUAL("y", temp_buffer);

  Elg::Utilities::Filesystem::Path path8("/a.x.y");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path8.GetExtension(temp_buffer);
  CHECK_EQUAL("y", temp_buffer);

  Elg::Utilities::Filesystem::Path path9("a.x.y/b");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path9.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path10("/a.x.y/b");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path10.GetExtension(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path11("a.x.y/b.z");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path11.GetExtension(temp_buffer);
  CHECK_EQUAL("z", temp_buffer);

  Elg::Utilities::Filesystem::Path path12("/a.x.y/b.z");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path12.GetExtension(temp_buffer);
  CHECK_EQUAL("z", temp_buffer);
}

TEST(Path_GetFilename) {
  elg_char temp_buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];

  Elg::Utilities::Filesystem::Path path1("");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path1.GetFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path2("/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path2.GetFilename(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path path3("a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path3.GetFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path path4("/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path4.GetFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path path5("a.x");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path5.GetFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path path6("/a.x");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path6.GetFilename(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path path7("a.x.y");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path7.GetFilename(temp_buffer);
  CHECK_EQUAL("a.x", temp_buffer);

  Elg::Utilities::Filesystem::Path path8("/a.x.y");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path8.GetFilename(temp_buffer);
  CHECK_EQUAL("a.x", temp_buffer);

  Elg::Utilities::Filesystem::Path path9("a.x.y/b");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path9.GetFilename(temp_buffer);
  CHECK_EQUAL("b", temp_buffer);

  Elg::Utilities::Filesystem::Path path10("/a.x.y/b");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path10.GetFilename(temp_buffer);
  CHECK_EQUAL("b", temp_buffer);

  Elg::Utilities::Filesystem::Path path11("a.x.y/b.z");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path11.GetFilename(temp_buffer);
  CHECK_EQUAL("b", temp_buffer);

  Elg::Utilities::Filesystem::Path path12("/a.x.y/b.z");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  path12.GetFilename(temp_buffer);
  CHECK_EQUAL("b", temp_buffer);
}

TEST(Path_GetFilename_Path) {
  Elg::Utilities::Filesystem::Path path1("");
  CHECK_EQUAL("", path1.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), path1.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path2("/");
  CHECK_EQUAL("", path2.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), path2.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path3("a");
  CHECK_EQUAL("a", path3.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path3.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path4("/a");
  CHECK_EQUAL("a", path4.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path4.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path5("a.x");
  CHECK_EQUAL("a", path5.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path5.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path6("/a.x");
  CHECK_EQUAL("a", path6.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path6.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path7("a.x.y");
  CHECK_EQUAL("a.x", path7.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), path7.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path8("/a.x.y");
  CHECK_EQUAL("a.x", path8.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), path8.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path9("a.x.y/b");
  CHECK_EQUAL("b", path9.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path9.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path10("/a.x.y/b");
  CHECK_EQUAL("b", path10.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path10.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path11("a.x.y/b.zyx");
  CHECK_EQUAL("b", path11.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path11.GetFilename().Length());

  Elg::Utilities::Filesystem::Path path12("/a.x.y/b.zyb");
  CHECK_EQUAL("b", path12.GetFilename().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), path12.GetFilename().Length());
}

TEST(Path_GetRoot) {
  elg_char temp_buffer[Elg::Utilities::Filesystem::Path::PATH_MAX + 1];

  Elg::Utilities::Filesystem::Path empty_path("");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  empty_path.GetRoot(temp_buffer);
  CHECK_EQUAL("", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_path("/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_path("a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_path.GetRoot(temp_buffer);
  CHECK_EQUAL("a", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_path.GetRoot(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("a/", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  separator_literal_literal_path.GetRoot(temp_buffer);
  CHECK_EQUAL("/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_separator_literal_path.GetRoot(temp_buffer);
  CHECK_EQUAL("a/", temp_buffer);

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  literal_literal_separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("aa/", temp_buffer);

  Elg::Utilities::Filesystem::Path trailing_separator_path("root/dir/file.txt");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  trailing_separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("root/", temp_buffer);

  Elg::Utilities::Filesystem::Path no_trailing_separator_path("root/dir");
  std::memset(temp_buffer, 0, Elg::Utilities::Filesystem::Path::PATH_MAX + 1);
  no_trailing_separator_path.GetRoot(temp_buffer);
  CHECK_EQUAL("root/", temp_buffer);
}

TEST(Path_GetRoot_Path) {
  Elg::Utilities::Filesystem::Path empty_path("");
  CHECK_EQUAL("", empty_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  CHECK_EQUAL("/", separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  CHECK_EQUAL("a", literal_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  CHECK_EQUAL("/", separator_literal_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  CHECK_EQUAL("a/", literal_separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  CHECK_EQUAL("/", separator_literal_separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_separator_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  CHECK_EQUAL("/", separator_literal_literal_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_literal_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  CHECK_EQUAL("a/", literal_separator_literal_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_literal_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  CHECK_EQUAL("aa/", literal_literal_separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_separator_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path trailing_separator_path("root/dir/file.txt");
  CHECK_EQUAL("root/", trailing_separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(5), trailing_separator_path.GetRoot().Length());

  Elg::Utilities::Filesystem::Path no_trailing_separator_path("root/dir");
  CHECK_EQUAL("root/", no_trailing_separator_path.GetRoot().AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(5), no_trailing_separator_path.GetRoot().Length());
}

TEST(Path_RemoveFullFilename) {
  Elg::Utilities::Filesystem::Path empty_path("");
  empty_path.RemoveFullFilename();
  CHECK_EQUAL("", empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  separator_path.RemoveFullFilename();
  CHECK_EQUAL("/", separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_path.Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  literal_path.RemoveFullFilename();
  CHECK_EQUAL("", literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), literal_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  separator_literal_path.RemoveFullFilename();
  CHECK_EQUAL("/", separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  literal_separator_path.RemoveFullFilename();
  CHECK_EQUAL("a/", literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  separator_literal_separator_path.RemoveFullFilename();
  CHECK_EQUAL("/a/", separator_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), separator_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  separator_literal_literal_path.RemoveFullFilename();
  CHECK_EQUAL("/", separator_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  literal_separator_literal_path.RemoveFullFilename();
  CHECK_EQUAL("a/", literal_separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  literal_literal_separator_path.RemoveFullFilename();
  CHECK_EQUAL("aa/", literal_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path trailing_filename_path("dir/subdir/file.txt");
  trailing_filename_path.RemoveFullFilename();
  CHECK_EQUAL("dir/subdir/", trailing_filename_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(11), trailing_filename_path.Length());

  Elg::Utilities::Filesystem::Path trailing_no_extension_path("dir/subdir/file");
  trailing_no_extension_path.RemoveFullFilename();
  CHECK_EQUAL("dir/subdir/", trailing_no_extension_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(11), trailing_no_extension_path.Length());
}

TEST(Path_RemoveExtension) {
  Elg::Utilities::Filesystem::Path empty_path("");
  empty_path.RemoveExtension();
  CHECK_EQUAL("", empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  separator_path.RemoveExtension();
  CHECK_EQUAL("/", separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_path.Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  literal_path.RemoveExtension();
  CHECK_EQUAL("a", literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), literal_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  separator_literal_path.RemoveExtension();
  CHECK_EQUAL("/a", separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  literal_separator_path.RemoveExtension();
  CHECK_EQUAL("a/", literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  separator_literal_separator_path.RemoveExtension();
  CHECK_EQUAL("/a/", separator_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), separator_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  separator_literal_literal_path.RemoveExtension();
  CHECK_EQUAL("/aa", separator_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), separator_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  literal_separator_literal_path.RemoveExtension();
  CHECK_EQUAL("a/a", literal_separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  literal_literal_separator_path.RemoveExtension();
  CHECK_EQUAL("aa/", literal_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/file.txt");
  trailing_separator_path.RemoveExtension();
  CHECK_EQUAL("dir/subdir/file", trailing_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(15), trailing_separator_path.Length());

  Elg::Utilities::Filesystem::Path trailing_no_extension_path("dir/subdir/file");
  trailing_no_extension_path.RemoveExtension();
  CHECK_EQUAL("dir/subdir/file", trailing_no_extension_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(15), trailing_no_extension_path.Length());
}

TEST(Path_ChangeExtension) {
  Elg::Utilities::Filesystem::Path empty_path("");
  empty_path.ChangeExtension("xyz");
  CHECK_EQUAL("", empty_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(0), empty_path.Length());

  Elg::Utilities::Filesystem::Path separator_path("/");
  separator_path.ChangeExtension("xyz");
  CHECK_EQUAL("/", separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(1), separator_path.Length());

  Elg::Utilities::Filesystem::Path literal_path("a");
  literal_path.ChangeExtension("xyz");
  CHECK_EQUAL("a.xyz", literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(5), literal_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_path("/a");
  separator_literal_path.ChangeExtension("xyz");
  CHECK_EQUAL("/a.xyz", separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(6), separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_path("a/");
  literal_separator_path.ChangeExtension("xyz");
  CHECK_EQUAL("a/", literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(2), literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_separator_path("/a/");
  separator_literal_separator_path.ChangeExtension("xyz");
  CHECK_EQUAL("/a/", separator_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), separator_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path separator_literal_literal_path("/aa");
  separator_literal_literal_path.ChangeExtension("xyz");
  CHECK_EQUAL("/aa.xyz", separator_literal_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), separator_literal_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_separator_literal_path("a/a");
  literal_separator_literal_path.ChangeExtension("xyz");
  CHECK_EQUAL("a/a.xyz", literal_separator_literal_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), literal_separator_literal_path.Length());

  Elg::Utilities::Filesystem::Path literal_literal_separator_path("aa/");
  literal_literal_separator_path.ChangeExtension("xyz");
  CHECK_EQUAL("aa/", literal_literal_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(3), literal_literal_separator_path.Length());

  Elg::Utilities::Filesystem::Path trailing_separator_path("dir/subdir/file.txt");
  trailing_separator_path.ChangeExtension("xyz");
  CHECK_EQUAL("dir/subdir/file.xyz", trailing_separator_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(19), trailing_separator_path.Length());

  Elg::Utilities::Filesystem::Path trailing_no_extension_path("dir/subdir/file");
  trailing_no_extension_path.ChangeExtension("xyz");
  CHECK_EQUAL("dir/subdir/file.xyz", trailing_no_extension_path.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(19), trailing_no_extension_path.Length());
}

TEST(Path_Combine) {
  // We test just one version of this function as they are coded the same as of now
  Elg::Utilities::Filesystem::Path path1 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d", "e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", path1.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), path1.Length());

  Elg::Utilities::Filesystem::Path path2 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d/", "e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", path2.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), path2.Length());

  Elg::Utilities::Filesystem::Path path3 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d", "/e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", path3.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), path3.Length());

  Elg::Utilities::Filesystem::Path path4 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d/", "/e/f/g/h");
  CHECK_EQUAL("/a/b/c/d/e/f/g/h", path4.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(16), path4.Length());

  Elg::Utilities::Filesystem::Path path5 = Elg::Utilities::Filesystem::CombinePaths("", "e/f/g/h");
  CHECK_EQUAL("e/f/g/h", path5.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(7), path5.Length());

  Elg::Utilities::Filesystem::Path path6 = Elg::Utilities::Filesystem::CombinePaths("", "/e/f/g/h");
  CHECK_EQUAL("/e/f/g/h", path6.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(8), path6.Length());

  Elg::Utilities::Filesystem::Path path7 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d", "");
  CHECK_EQUAL("/a/b/c/d", path7.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(8), path7.Length());

  Elg::Utilities::Filesystem::Path path8 = Elg::Utilities::Filesystem::CombinePaths("/a/b/c/d/", "");
  CHECK_EQUAL("/a/b/c/d/", path8.AsNullTerminatedString());
  CHECK_EQUAL(static_cast<elg_uint32>(9), path8.Length());
}
