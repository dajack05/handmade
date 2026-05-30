#pragma once

#include "src/tests/TestMacros.hpp"
#include "src/util/Math.hpp"
#include <cstdio>
namespace MathTest {

inline bool MaxTest() {
  BEGIN_TEST

  {
    const int a = 1;
    const int b = 2;
    const int res = max(a, b);
    ASSERT_INT(res, 2);
  }

  {
    const float a = 1.23f;
    const float b = 2.34f;
    const float res = max(a, b);
    ASSERT_DBL(res, 2.34f);
  }

  {
    const double a = -10.0;
    const double b = 10.0;
    const double res = max(a, b);
    ASSERT_DBL(res, 10.0);
  }

  return true;
}

inline bool MinTest() {
  BEGIN_TEST

  {
    const int a = 1;
    const int b = 2;
    const int res = min(a, b);
    ASSERT_INT(res, 1);
  }

  {
    const float a = 1.23f;
    const float b = 2.34f;
    const float res = min(a, b);
    ASSERT_DBL(res, 1.23f);
  }

  {
    const double a = -10.0;
    const double b = 10.0;
    const double res = min(a, b);
    ASSERT_DBL(res, -10.0);
  }

  return true;
}

inline bool DecimalTest() {
  {
    const double a = 123.456;
    const unsigned int expected = 3;
    const unsigned int result = decimalCount(a);
    ASSERT_INT(result, expected);
  }

  {
    const double a = 123.000;
    const unsigned int expected = 0;
    const unsigned int res = decimalCount(a);
    ASSERT_INT(res, 0);
  }
  return true;
}

inline bool All() {
  RUN_TEST(MinTest())
  RUN_TEST(MaxTest())
  RUN_TEST(DecimalTest())
  return true;
}

}; // namespace MathTest
