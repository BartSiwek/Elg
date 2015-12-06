/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/MPL/MplMath.h"

TEST(Mpl_Sign) {
  CHECK_EQUAL(-1, Elg::Utilities::Mpl::Sign<-100>::value);
  CHECK_EQUAL(0, Elg::Utilities::Mpl::Sign<0>::value);
  CHECK_EQUAL(1, Elg::Utilities::Mpl::Sign<100>::value);
}

TEST(Mpl_Abs) {
  CHECK_EQUAL(100, Elg::Utilities::Mpl::Abs<-100>::value);
  CHECK_EQUAL(0, Elg::Utilities::Mpl::Abs<0>::value);
  CHECK_EQUAL(100, Elg::Utilities::Mpl::Abs<100>::value);
}

TEST(Mpl_Multiply_Basic) {
  typedef Elg::Utilities::Mpl::Multiply<10, 10> Result1;
  CHECK_EQUAL(100, Result1::value);

  typedef Elg::Utilities::Mpl::Multiply<10, -10> Result2;
  CHECK_EQUAL(-100, Result2::value);

  typedef Elg::Utilities::Mpl::Multiply<-10, 10> Result3;
  CHECK_EQUAL(-100, Result3::value);

  typedef Elg::Utilities::Mpl::Multiply<-10, -10> Result4;
  CHECK_EQUAL(100, Result4::value);
}

TEST(Mpl_Multiply_AlmostOverflow) {
  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x100000000), static_cast<elg_int64>(0x7fffffff)>
    Almost1;
  CHECK_EQUAL(static_cast<elg_int64>(0x7fffffff00000000), Almost1::value);

  typedef Elg::Utilities::Mpl::Multiply<-static_cast<elg_int64>(0x100000000), static_cast<elg_int64>(0x7fffffff)>
    Almost2;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7fffffff00000000), Almost2::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x100000000), -static_cast<elg_int64>(0x7fffffff)>
    Almost3;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7fffffff00000000), Almost3::value);

  typedef Elg::Utilities::Mpl::Multiply<-static_cast<elg_int64>(0x100000000), -static_cast<elg_int64>(0x7fffffff)>
    Almost4;
  CHECK_EQUAL(static_cast<elg_int64>(0x7fffffff00000000), Almost4::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x10000000), static_cast<elg_int64>(0x10000000)>
    Almost5;
  CHECK_EQUAL(static_cast<elg_int64>(0x100000000000000), Almost5::value);

  typedef Elg::Utilities::Mpl::Multiply<-static_cast<elg_int64>(0x10000000), static_cast<elg_int64>(0x10000000)>
    Almost6;
  CHECK_EQUAL(-static_cast<elg_int64>(0x100000000000000), Almost6::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x10000000), -static_cast<elg_int64>(0x10000000)>
    Almost7;
  CHECK_EQUAL(-static_cast<elg_int64>(0x100000000000000), Almost7::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x10000000), static_cast<elg_int64>(0x10000000)>
    Almost8;
  CHECK_EQUAL(static_cast<elg_int64>(0x100000000000000), Almost8::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x7fffffff), static_cast<elg_int64>(0xffffffff)>
    Almost9;
  CHECK_EQUAL(static_cast<elg_int64>(0x7ffffffe80000001), Almost9::value);

  // Here the bottom part overflows but its okay :)
  typedef Elg::Utilities::Mpl::Multiply<-static_cast<elg_int64>(0x7fffffff), static_cast<elg_int64>(0xffffffff)>
    Almost10;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7ffffffe80000001), Almost10::value);

  typedef Elg::Utilities::Mpl::Multiply<static_cast<elg_int64>(0x7fffffff), -static_cast<elg_int64>(0xffffffff)>
    Almost11;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7ffffffe80000001), Almost11::value);

  typedef Elg::Utilities::Mpl::Multiply<-static_cast<elg_int64>(0x7fffffff), -static_cast<elg_int64>(0xffffffff)>
    Almost12;
  CHECK_EQUAL(static_cast<elg_int64>(0x7ffffffe80000001), Almost12::value);
}

TEST(Mpl_Multiply_Overflow) {
  // Obvious overflow
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), static_cast<int64>(0x100000000)> Over1;
  // CHECK_EQUAL(0, Over1::value);
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), -static_cast<int64>(0x100000000)> Over2;
  // CHECK_EQUAL(0, Over2::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), static_cast<int64>(0x100000000)> Over3;
  // CHECK_EQUAL(0, Over3::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), -static_cast<int64>(0x100000000)> Over4;
  // CHECK_EQUAL(0, Over4::value);

  // Overflow due to sign bit
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), static_cast<int64>(0xffffffff)> Over5;
  // CHECK_EQUAL(static_cast<int64>(0xffffffff00000000), Over5::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), static_cast<int64>(0xffffffff)> Over6;
  // CHECK_EQUAL(-static_cast<int64>(0xffffffff00000000), Over6::value);
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), -static_cast<int64>(0xffffffff)> Over7;
  // CHECK_EQUAL(-static_cast<int64>(0xffffffff00000000), Over7::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), -static_cast<int64>(0xffffffff)> Over8;
  // CHECK_EQUAL(static_cast<int64>(0xffffffff00000000), Over8::value);

  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), static_cast<int64>(0x8fffffff)> Over9;
  // CHECK_EQUAL(0, Over9::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), static_cast<int64>(0x8fffffff)> Over10;
  // CHECK_EQUAL(-static_cast<int64>(0x8fffffff00000000), Over10::value);
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x100000000), -static_cast<int64>(0x8fffffff)> Over11;
  // CHECK_EQUAL(-static_cast<int64>(0x8fffffff00000000), Over11::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x100000000), -static_cast<int64>(0x8fffffff)> Over12;
  // CHECK_EQUAL(static_cast<int64>(0x8fffffff00000000), Over12::value);

  // Overflow after sumation
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x1ffffffff), static_cast<int64>(0x7fffffff)> Over13;
  // CHECK_EQUAL(static_cast<int64>(0x7fffffff00000000), Over13::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x1ffffffff), static_cast<int64>(0x7fffffff)> Over14;
  // CHECK_EQUAL(-static_cast<int64>(0x7fffffff00000000), Over14::value);
  // typedef Elg::Utilities::Mpl::Multiply<static_cast<int64>(0x1ffffffff), -static_cast<int64>(0x7fffffff)> Over15;
  // CHECK_EQUAL(-static_cast<int64>(0x7fffffff00000000), Over15::value);
  // typedef Elg::Utilities::Mpl::Multiply<-static_cast<int64>(0x1ffffffff), -static_cast<int64>(0x7fffffff)> Over16;
  // CHECK_EQUAL(static_cast<int64>(0x7fffffff00000000), Over16::value);
}

TEST(Add_Multiply_Basic) {
  typedef Elg::Utilities::Mpl::Add<1, 2> Result1;
  CHECK_EQUAL(3, Result1::value);

  typedef Elg::Utilities::Mpl::Add<1, -2> Result2;
  CHECK_EQUAL(-1, Result2::value);

  typedef Elg::Utilities::Mpl::Add<3, -2> Result3;
  CHECK_EQUAL(1, Result3::value);

  typedef Elg::Utilities::Mpl::Add<-1, 2> Result4;
  CHECK_EQUAL(1, Result4::value);

  typedef Elg::Utilities::Mpl::Add<-3, 2> Result5;
  CHECK_EQUAL(-1, Result5::value);

  typedef Elg::Utilities::Mpl::Add<-1, 1> Result6;
  CHECK_EQUAL(0, Result6::value);
}

TEST(Mpl_Add_AlmostOverflow) {
  typedef Elg::Utilities::Mpl::Add<static_cast<elg_int64>(0x7ffffffffffffffe), static_cast<elg_int64>(1)> Almost1;
  CHECK_EQUAL(static_cast<elg_int64>(0x7fffffffffffffff), Almost1::value);

  typedef Elg::Utilities::Mpl::Add<-static_cast<elg_int64>(0x7ffffffffffffffe), static_cast<elg_int64>(1)> Almost2;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7ffffffffffffffd), Almost2::value);

  typedef Elg::Utilities::Mpl::Add<static_cast<elg_int64>(0x7ffffffffffffffe), -static_cast<elg_int64>(1)> Almost3;
  CHECK_EQUAL(static_cast<elg_int64>(0x7ffffffffffffffd), Almost3::value);

  typedef Elg::Utilities::Mpl::Add<-static_cast<elg_int64>(0x7ffffffffffffffe), -static_cast<elg_int64>(1)> Almost4;
  CHECK_EQUAL(-static_cast<elg_int64>(0x7fffffffffffffff), Almost4::value);

  typedef Elg::Utilities::Mpl::Add<-static_cast<elg_int64>(0x7fffffffffffffff), -static_cast<elg_int64>(1)> Almost5;
  CHECK_EQUAL(-static_cast<elg_int64>(0x8000000000000000), Almost5::value);
}

TEST(Mpl_Add_Overflow) {
  // Top overflow
  // typedef Elg::Utilities::Mpl::Add<static_cast<int64>(0x7fffffffffffffff), static_cast<int64>(1)> Over1;
  // CHECK_EQUAL(static_cast<int64>(0x8000000000000000), Over1::value);

  // Bottom overflow
  // typedef Elg::Utilities::Mpl::Add<-static_cast<int64>(0x8000000000000000), -static_cast<int64>(1)> Over2;
  // CHECK_EQUAL(-static_cast<int64>(0x80000000000000), Over2::value);
}

TEST(Mpl_Min) {
  typedef Elg::Utilities::Mpl::Min<-100, 0> Min1;
  CHECK_EQUAL(-100, Min1::value);

  typedef Elg::Utilities::Mpl::Min<0, 0> Min2;
  CHECK_EQUAL(0, Min2::value);

  typedef Elg::Utilities::Mpl::Min<100, 0> Min3;
  CHECK_EQUAL(0, Min3::value);

  typedef Elg::Utilities::Mpl::Min<0, -100> Min4;
  CHECK_EQUAL(-100, Min4::value);

  typedef Elg::Utilities::Mpl::Min<0, 0> Min5;
  CHECK_EQUAL(0, Min5::value);

  typedef Elg::Utilities::Mpl::Min<0, 100> Min6;
  CHECK_EQUAL(0, Min6::value);
}

TEST(Mpl_Max) {
  typedef Elg::Utilities::Mpl::Max<-100, 0> Max1;
  CHECK_EQUAL(0, Max1::value);

  typedef Elg::Utilities::Mpl::Max<0, 0> Max2;
  CHECK_EQUAL(0, Max2::value);

  typedef Elg::Utilities::Mpl::Max<100, 0> Max3;
  CHECK_EQUAL(100, Max3::value);

  typedef Elg::Utilities::Mpl::Max<0, -100> Max4;
  CHECK_EQUAL(0, Max4::value);

  typedef Elg::Utilities::Mpl::Max<0, 0> Max5;
  CHECK_EQUAL(0, Max5::value);

  typedef Elg::Utilities::Mpl::Max<0, 100> Max6;
  CHECK_EQUAL(100, Max6::value);
}

TEST(Mpl_Log2) {
  CHECK_EQUAL(0, Elg::Utilities::Mpl::Log2<0>::value);
  CHECK_EQUAL(0, Elg::Utilities::Mpl::Log2<1>::value);
  CHECK_EQUAL(1, Elg::Utilities::Mpl::Log2<2>::value);
  CHECK_EQUAL(1, Elg::Utilities::Mpl::Log2<3>::value);
  CHECK_EQUAL(2, Elg::Utilities::Mpl::Log2<4>::value);
  CHECK_EQUAL(2, Elg::Utilities::Mpl::Log2<5>::value);
  CHECK_EQUAL(2, Elg::Utilities::Mpl::Log2<6>::value);
  CHECK_EQUAL(2, Elg::Utilities::Mpl::Log2<7>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<8>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<9>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<10>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<11>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<12>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<13>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<14>::value);
  CHECK_EQUAL(3, Elg::Utilities::Mpl::Log2<15>::value);
  CHECK_EQUAL(4, Elg::Utilities::Mpl::Log2<16>::value);
  CHECK_EQUAL(5, Elg::Utilities::Mpl::Log2<32>::value);
  CHECK_EQUAL(6, Elg::Utilities::Mpl::Log2<64>::value);
  CHECK_EQUAL(7, Elg::Utilities::Mpl::Log2<128>::value);
  CHECK_EQUAL(8, Elg::Utilities::Mpl::Log2<256>::value);
  CHECK_EQUAL(9, Elg::Utilities::Mpl::Log2<512>::value);
  CHECK_EQUAL(10, Elg::Utilities::Mpl::Log2<1024>::value);
}

TEST(Mpl_IsPow2) {
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<0>::value);

  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<1>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<2>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<3>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<4>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<5>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<6>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<7>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<8>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<9>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<10>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<11>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<12>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<13>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<14>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<15>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<16>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<32>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<64>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<128>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<256>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<512>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<1024>::value);

  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-1>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-2>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-3>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-4>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-5>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-6>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-7>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-8>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-9>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-10>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-11>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-12>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-13>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-14>::value);
  CHECK_EQUAL(false, Elg::Utilities::Mpl::IsPow2<-15>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-16>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-32>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-64>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-128>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-256>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-512>::value);
  CHECK_EQUAL(true, Elg::Utilities::Mpl::IsPow2<-1024>::value);
}

TEST(Mpl_Pow2) {
  CHECK_EQUAL(1, Elg::Utilities::Mpl::Pow2<0>::value);
  CHECK_EQUAL(2, Elg::Utilities::Mpl::Pow2<1>::value);
  CHECK_EQUAL(4, Elg::Utilities::Mpl::Pow2<2>::value);
  CHECK_EQUAL(8, Elg::Utilities::Mpl::Pow2<3>::value);
  CHECK_EQUAL(16, Elg::Utilities::Mpl::Pow2<4>::value);
  CHECK_EQUAL(32, Elg::Utilities::Mpl::Pow2<5>::value);
  CHECK_EQUAL(64, Elg::Utilities::Mpl::Pow2<6>::value);
  CHECK_EQUAL(128, Elg::Utilities::Mpl::Pow2<7>::value);
  CHECK_EQUAL(256, Elg::Utilities::Mpl::Pow2<8>::value);
  CHECK_EQUAL(512, Elg::Utilities::Mpl::Pow2<9>::value);
  CHECK_EQUAL(1024, Elg::Utilities::Mpl::Pow2<10>::value);
}
