/*
* Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
*/

#ifndef ELG_TESTS_TESTASSETS_H_
#define ELG_TESTS_TESTASSETS_H_

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Tests {

void SetTestAssetsPath(const elg_char* path);
const elg_char* GetTestAssetsPath();

}  // namespace Tests
}  // namespace Elg

#endif  // ELG_TESTS_TESTASSETS_H_
