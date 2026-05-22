#include "src/util/String.hpp"

#include "src/util/Math.hpp"
#include "src/util/RingBuffer.hpp"
#include <climits>
#include <cstdio>

RingBuffer<char[1024], 128> strBuffers;

unsigned int StrLen(const char *str) {
  unsigned int count = 0;
  char c;
  while ((c = *str++)) {
    count++;
  }
  return count;
}

void StrCopy(const char *from, char *to, unsigned int maxLength) {
  for (auto i = 0; i < maxLength; i++) {
    to[i] = from[i];
    if (from[i] == 0) {
      return;
    }
  }
}

const char *StrAppend(const char *a, const char *b) {
  auto &buffer = strBuffers.getNext();
  const auto len_a = StrLen(a);
  const auto len_b = StrLen(b);
  if (len_a + len_b >= 1024) {
    printf(
        "StrAppend: total length exceeds 1024. Expect missing data.\n%s %s\n",
        a, b);
  }

  const unsigned int write_len_a = min(len_a, (unsigned int)1024);
  StrCopy(a, buffer, write_len_a);
  const unsigned int write_len_b = min(len_b, 1024 - write_len_a);
  StrCopy(b, &buffer[write_len_a], write_len_b);

  return buffer;
}

bool StrEqual(const char *a, const char *b) {
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

int StrToInt(const char *input) {
  // Verify chars are in range
  int result = 0;
  char c;
  while ((c = *input++)) {
    if (c < '0' || c > '9') {
      printf("StrToInt: ERROR. char '%c' is out of range.\n", c);
      return INT_MAX;
    }
    result = result * 10 + c - '0';
  }
  return result;
}

const char *StrFromInt(const int value) {
  char (&buffer)[1024] = strBuffers.getNext();
  snprintf(buffer, 1024, "%i", value);
  return buffer;
}

const char *StrFromDouble(const double &value) {
  char (&buffer)[1024] = strBuffers.getNext();
  snprintf(buffer, 1024, "%g", value);
  return buffer;
}

const char *StrTrim(const char *text, unsigned int count) {
  auto buffer = strBuffers.getNext();
  const auto textLen = StrLen(text);
  for (auto i = 0; i < 1024 && i < textLen - count; i++) {
    buffer[i] = text[i];
  }
  return buffer;
}
