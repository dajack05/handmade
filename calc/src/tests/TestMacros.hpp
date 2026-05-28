#pragma once

#define BEGIN_TEST printf("Running %s. ", __PRETTY_FUNCTION__);

#define RUN_TEST(test)                                                         \
  if (!test) {                                                                 \
    printf("FAIL\n");                                                          \
    return false;                                                              \
  } else {                                                                     \
    printf("\n");                                                              \
  }

#define ASSERT_DBL(value, expect)                                              \
  if (value != expect) {                                                       \
    printf("%s:%i. FAIL expected %f got %f\n", __PRETTY_FUNCTION__, __LINE__,  \
           expect, value);                                                     \
    return false;                                                              \
  }

#define ASSERT_INT(value, expect)                                              \
  if (value != expect) {                                                       \
    printf("%s:%i. FAIL expected %i got %i\n", __PRETTY_FUNCTION__, __LINE__,  \
           expect, value);                                                     \
    return false;                                                              \
  }
