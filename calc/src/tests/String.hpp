#pragma once

#include "src/tests/TestMacros.hpp"
#include "src/util/String.hpp"
#include <climits>
#include <cstdio>
#include <mutex>
#include <type_traits>

namespace StringTest {

inline bool StrLenGood() {
  BEGIN_TEST
  const char *sample = "Test String 123";
  const int sample_len = 15;
  const int value = StrLen(sample);
  return value == sample_len;
}

inline bool StrEqualGood() {
  BEGIN_TEST
  const char *a = "This Is Good";
  const char *b = "This Is Good";
  return StrEqual(a, b);
}

inline bool StrEqualBad() {
  BEGIN_TEST
  // Check capitalization
  const char *a = "This Is Bad";
  const char *b = "This is Bad";
  if (StrEqual(a, b)) {
    printf("StrEqualBad. Did not catch capitalization error\n");
    return false;
  }

  const char *c = "This Is Bad ";
  if (StrEqual(a, c)) {
    printf("StrEqualBad. Did not catch whitesapce at end of string\n");
    return false;
  }

  return true;
}

inline bool StrToIntGood() {
  BEGIN_TEST
  const char *number = "8";
  const int value = StrToInt(number);
  if (value != 8) {
    printf("StrToIntGood. Expected 8 got %i\n", value);
    return false;
  }

  const char *numbers = "123";
  const int value2 = StrToInt(numbers);
  if (value2 != 123) {
    printf("StrToIntGood. Expected 123 got %i\n", value);
    return false;
  }

  return true;
}

inline bool StrToIntBad() {
  BEGIN_TEST
  const char *number = " 8";
  const int value = StrToInt(number);
  if (value != INT_MAX) {
    printf("StrToIntBad. Whitespace. Expected 0 got %i\n", value);
    return false;
  }

  const char *numbers = "12a3";
  const int value2 = StrToInt(numbers);
  if (value2 != INT_MAX) {
    printf("StrToIntBad. letter. Expected 0 got %i\n", value);
    return false;
  }

  return true;
}

inline bool StrCopyGood() {
  BEGIN_TEST
  // Test too long
  const char *first = "This is a test string";
  char second[10] = {0};
  StrCopy(first, second, 10);
  for (auto i = 0; i < 10; i++) {
    if (second[i] != first[i]) {
      printf("StrCopyGood. second[%i] (%c) != first[%i] %c\n", i, second[i], i,
             first[i]);
      return false;
    }
  }

  // Test short
  const char *third = "This One";
  char fourth[10] = {0};
  StrCopy(third, fourth, 10);
  for (auto i = 0; i < 10; i++) {
    if (i < 8) {
      if (third[i] != fourth[i]) {
        printf("StrCopyGood. third[%i] (%c) != fourth[%i] %c\n", i, third[i], i,
               fourth[i]);
        return false;
      }
    } else {
      if (fourth[i] != 0) {
        printf("StrCopyGood. fourth[%i] (%c) != 0.\n", i, fourth[i]);
        return false;
      }
    }
  }
  return true;
}

inline bool StrFromIntGood() {
  BEGIN_TEST

  const int value = 12345;
  const char *str = StrFromInt(value);
  if (!StrEqual(str, "12345")) {
    printf("StrFromIntGood: Expected '12345' got '%s'\n", str);
    return false;
  }

  return true;
}

inline bool StrFromDoubleGood() {
  BEGIN_TEST

  const double value = 123.456;
  const char *str = StrFromDouble(value);
  if (!StrEqual(str, "123.456")) {
    printf("StrFromDoubleGood. expected str to = \"123.456\". Got \"%s\"\n",
           str);
    return false;
  }

  return true;
}

inline bool StrAppendGood() {
  BEGIN_TEST

  const char *a = "123";
  const char *b = "456";
  const char *c = StrAppend(a, b);
  if (!StrEqual(c, "123456")) {
    printf("StrAppendGood: Expected '123456' got '%s'\n", c);
    return false;
  }

  return true;
}

inline bool StrTrimGood() {
  BEGIN_TEST

  const char *a = "1234567890";
  const char *b = StrTrim(a, 2);
  if (!StrEqual(b, "12345678")) {
    printf("StrTrimGood. Expected '12345678' got %s\n", b);
    return false;
  }

  return true;
}

}; // namespace StringTest
