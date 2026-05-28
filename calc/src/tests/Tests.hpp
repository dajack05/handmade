#pragma once

#include "src/calculator/Calculator.hpp"
#ifndef NDEBUG

#include "src/calculator/Calculator.test.hpp"
#include "src/calculator/DigiOp.test.hpp"
#include "src/tests/String.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/Queue.test.hpp"
#include "src/util/Stack.test.hpp"

inline bool RunTests() {
  RUN_TEST(StringTest::StrLenGood())
  RUN_TEST(StringTest::StrEqualBad())
  RUN_TEST(StringTest::StrEqualGood())
  RUN_TEST(StringTest::StrAppendGood())
  RUN_TEST(StringTest::StrToIntGood())
  RUN_TEST(StringTest::StrToIntBad())
  RUN_TEST(StringTest::StrCopyGood())
  RUN_TEST(StringTest::StrFromIntGood())
  RUN_TEST(StringTest::StrFromDoubleGood())

  RUN_TEST(DigiOpTest::All())

  RUN_TEST(StackTest::All())
  RUN_TEST(QueueTest::All())

  RUN_TEST(Cal::InternalTest())

  RUN_TEST(CalculatorTest::CalculateResultGood())

  printf("TEST GOOD 👍\n");
  return true;
}

#else

inline bool RunTests() { return true; }

#endif // NDEBUG
