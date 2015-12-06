/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg.Tests/TestAssets.h"

int main(int argc, char** argv) {
  if (argc >= 2) {
    Elg::Tests::SetTestAssetsPath(argv[1]);
  }

  int result = UnitTest::RunAllTests();
  system("PAUSE");
  return result;
}
