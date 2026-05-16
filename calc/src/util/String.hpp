#pragma once

#include <cstdio>
inline unsigned int StrLen(const char *str) {
  unsigned int count = 0;
  char c;
  while ((c = *str++)) {
    count++;
  }
  return count;
}

inline void StrCopy(const char *from, char *to, unsigned int maxLength) {
  for (auto i = 0; i < maxLength; i++) {
    to[i] = from[i];
    if (from[i] == 0) {
      return;
    }
  }
}

inline bool StrEqual(const char *a, const char *b) {
  for (auto i = 0; i < 10000; i++) {
    if (a[i] != b[i]) {
      return false;
    }

    if (a[i] == 0) {
      return true;
    }
  }
  return true;
}

inline int StrToInt(const char *input) {
  // Verify chars are in range
  int result = 0;
  char c;
  while ((c = *input++)) {
    if (c < '0' || c > '9') {
      printf("StrToInt: ERROR. char '%c' is out of range.\n", c);
      return 0;
    }
    result = result * 10 + c - '0';
  }
  return result;
}
