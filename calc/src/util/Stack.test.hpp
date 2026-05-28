#include "src/tests/TestMacros.hpp"
#include "src/util/Stack.hpp"
#include <cstdio>

namespace StackTest {

inline bool PushTest() {
  BEGIN_TEST
  Stack<int, 10> list;
  list.push(1);
  ASSERT_INT(list.size(), 1)
  list.push(2);
  ASSERT_INT(list.size(), 2)
  return true;
}

inline bool PopTest() {
  BEGIN_TEST
  Stack<int, 10> list;
  list.push(1);
  list.push(2);
  list.push(3);
  ASSERT_INT(list.pop(), 3);
  ASSERT_INT(list.pop(), 2);
  ASSERT_INT(list.pop(), 1);
  return true;
}

inline bool LimitsTest() {
  BEGIN_TEST
  const unsigned int testListSize = 10;
  Stack<int, testListSize> list;
  for (auto i = 0; i < testListSize; i++) {
    list.push(i);
  }
  ASSERT_INT(list.size(), testListSize);

  // Warning should print here
  list.push(123);
  ASSERT_INT(list.size(), testListSize);

  return true;
}

inline bool All() {
  RUN_TEST(PushTest())
  RUN_TEST(PopTest())
  RUN_TEST(LimitsTest())
  return true;
}

} // namespace StackTest
