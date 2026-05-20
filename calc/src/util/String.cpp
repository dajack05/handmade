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
  int mValue = value;
  char (&buffer)[1024] = strBuffers.getNext();
  unsigned int bufferIdx = 0;

  // Convert the int section
  unsigned int place = 1;
  while (mValue > 0) {
    const auto digit = mValue % (place * 10) / place;
    mValue -= digit * place;
    place *= 10;
    if (digit >= 0 && digit <= 9) {
      const char c = digit + '0';
      buffer[bufferIdx++] = c;
      if (bufferIdx >= 1024) {
        printf("StrFromInt: Ran out of string buffer space.\n");
        return "";
      }
    }
  }

  // Flip the result
  char copy[1024] = {0};
  StrCopy(buffer, copy, 1024);

  const auto len = StrLen(copy);
  for (auto i = 1; i <= len; i++) {
    buffer[i - 1] = copy[len - i];
  }

  if (len < 1023) {
    buffer[len + 1] = 0;
  }

  return buffer;
}

const char *StrFromDouble(const double &value) {
  const int first = (int)value;
  const double second = value - first;
  auto &buffer = strBuffers.getNext();

  // Convert the int section
  const auto str_first = StrFromInt(first);

  // Figure out how many decimal places are stored
  int decimal_count = 0;
  double tval = second;
  while (tval >= 0.0001) {
    tval *= 10;
    decimal_count++;
    tval = tval - (int)tval;
  }

  tval = second;
  for (auto i = 0; i < decimal_count; i++) {
    tval *= 10;
  }

  const char *str_second = StrFromInt((int)tval);

  const char *str_total = StrAppend(StrAppend(str_first, "."), str_second);
  StrCopy(str_total, buffer, 1024);

  return buffer;
}
