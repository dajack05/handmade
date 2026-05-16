#pragma once

#include "src/util/String.hpp"
#include <cstdio>
namespace StringTest {

inline bool StrLenGood() {
  printf("Running %s: ", __PRETTY_FUNCTION__);
  const char *sample = "Test String 123";
  const int sample_len = 15;
  const int value = StrLen(sample);
  return value == sample_len;
}

inline bool StrEqualGood() {
  printf("Running %s: ", __PRETTY_FUNCTION__);
  const char *a = "This Is Good";
  const char *b = "This Is Good";
  return StrEqual(a, b);
}

inline bool StrEqualBad() {
  printf("Running %s: ", __PRETTY_FUNCTION__);
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
  printf("Running %s: ", __PRETTY_FUNCTION__);
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
  printf("Running %s: ", __PRETTY_FUNCTION__);
  const char *number = " 8";
  const int value = StrToInt(number);
  if (value != 0) {
    printf("StrToIntBad. Whitespace. Expected 0 got %i\n", value);
    return false;
  }

  const char *numbers = "12a3";
  const int value2 = StrToInt(numbers);
  if (value2 != 0) {
    printf("StrToIntBad. letter. Expected 0 got %i\n", value);
    return false;
  }

  return true;
}

inline bool StrCopyGood() {
  printf("Running %s: ", __PRETTY_FUNCTION__);
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

}; // namespace StringTest
