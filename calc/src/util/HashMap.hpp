#pragma once

#include "src/util/String.hpp"
#include <cstdio>
#define HASH_MAX_KEY_LEN 64

inline unsigned int hash(const char *str, unsigned int mod) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = hash * 33 + c;
  }
  return hash % mod;
}

template <typename T, unsigned int SIZE> //
struct HashMap {
  char keys[SIZE][HASH_MAX_KEY_LEN];
  T values[SIZE];

  void set(const char *key, T value) {
    if (StrLen(key) > HASH_MAX_KEY_LEN) {
      printf("HashMap key too long.\n");
      return;
    }
    const unsigned int h = hash(key, SIZE);
    // Check for collisions
    if (keys[h][0] != 0 && !StrEqual(key, keys[h])) {
      printf("HasMap::set. Hash collision detected between %s and %s\n", key,
             keys[h]);
      return;
    }
    StrCopy(key, keys[h], HASH_MAX_KEY_LEN);
    values[h] = value;
  }

  T &get(const char *key) {
    if (StrLen(key) > HASH_MAX_KEY_LEN) {
      printf("HashMap::get Key too long.\n");
      return values[0];
    }
    const unsigned int h = hash(key, SIZE);
    // Check for collisions
    if (keys[h][0] != 0 && !StrEqual(key, keys[h])) {
      printf("HasMap::set. Hash collision detected between %s and %s\n", key,
             keys[h]);
      return values[0];
    }
    return values[h];
  }
};
