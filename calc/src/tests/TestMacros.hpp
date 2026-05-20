#pragma once

#define BEGIN_TEST printf("Running %s: ", __PRETTY_FUNCTION__);

#define RUN_TEST(test)                                                         \
  if (!test) {                                                                 \
    printf("FAIL\n");                                                          \
    return false;                                                              \
  } else {                                                                     \
    printf("PASS\n");                                                          \
  }
