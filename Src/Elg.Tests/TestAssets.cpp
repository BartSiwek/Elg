/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#include "Elg.Tests/TestAssets.h"

namespace Elg {
namespace Tests {

static const elg_char* g_test_asset_path = "";

void SetTestAssetsPath(const elg_char* path) {
  g_test_asset_path = path;
}

const elg_char* GetTestAssetsPath() {
  return g_test_asset_path;
}

}  // namespace Tests
}  // namespace Elg
