#pragma once

#include "src/tests/String.hpp"
#include <cstdio>

#define RUN_TEST(test)                                                         \
  if (!test) {                                                                 \
    printf("FAIL\n");                                                          \
    return false;                                                              \
  } else {                                                                     \
    printf("PASS\n");                                                          \
  }

inline bool RunTests() {
  RUN_TEST(StringTest::StrLenGood())
  RUN_TEST(StringTest::StrEqualBad())
  RUN_TEST(StringTest::StrEqualGood())
  RUN_TEST(StringTest::StrToIntGood())
  RUN_TEST(StringTest::StrToIntBad())
  RUN_TEST(StringTest::StrCopyGood())

  printf("TEST GOOD 👍\n");
  return true;
}
