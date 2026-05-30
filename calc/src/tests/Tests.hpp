#pragma once

#ifndef NDEBUG

#include "src/calculator/Calc.hpp"
#include "src/calculator/Calc.test.hpp"
#include "src/calculator/DigiOp.test.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/Math.test.hpp"
#include "src/util/Queue.test.hpp"
#include "src/util/Stack.test.hpp"
#include "src/util/String.test.hpp"

inline bool RunTests() {
  RUN_TEST(StringTest::All())
  RUN_TEST(MathTest::All())
  RUN_TEST(DigiOpTest::All())
  RUN_TEST(StackTest::All())
  RUN_TEST(QueueTest::All())
  RUN_TEST(Calc::InternalTest())
  RUN_TEST(CalculatorTest::CalculateResultGood())

  printf("TEST GOOD 👍\n");
  return true;
}

#else

inline bool RunTests() { return true; }

#endif // NDEBUG
