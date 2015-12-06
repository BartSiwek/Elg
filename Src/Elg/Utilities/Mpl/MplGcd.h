/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_MPL_MPLGCD_H_
#define ELG_UTILITIES_MPL_MPLGCD_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"
#include "Elg/Utilities/MPL/MplMath.h"

namespace Elg {
namespace Utilities {
namespace Mpl {

template<elg_int64 Dividend, elg_int64 Divisor>
struct Gcd;

template<elg_int64 Dividend, elg_int64 Divisor>
struct Gcd : Gcd<Divisor, (Dividend % Divisor)> {
};

template<elg_int64 Dividend>
struct Gcd<Dividend, 0> {
  static const elg_int64 value = Abs<Dividend>::value;
};

template<elg_int64 Divisor>
struct Gcd<0, Divisor> {
  static const elg_int64 value = Abs<Divisor>::value;
};

}  // namespace Mpl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_MPL_MPLGCD_H_
