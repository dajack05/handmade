#pragma once

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
