#pragma once

template <typename T> //
inline T max(T a, T b) {
  return a > b ? a : b;
}

template <typename T> //
inline T min(T a, T b) {
  return a < b ? a : b;
}

inline unsigned int decimalCount(const double source) {
  unsigned int count = 0;
  const int wholePart = (int)source;
  double decimalPart = source - wholePart;
  while (decimalPart > 0.000001) {
    decimalPart *= 10.0;
    decimalPart -= (int)decimalPart;
    count++;
  }
  return count;
}
