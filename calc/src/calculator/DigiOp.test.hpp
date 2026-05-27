
#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"
#include <cstdio>

namespace DigiOpTest {

inline bool PushTest() {
  BEGIN_TEST
  DigiOpList list;
  const DigiOp el{123.456, Op::None};
  list.push(el);
  ASSERT_DBL(list.get(0).value, 123.456)
  list.push({222.22, Op::None});
  ASSERT_DBL(list.get(1).value, 222.22)
  return true;
}

inline bool SizeTest() {
  BEGIN_TEST
  DigiOpList list;
  const DigiOp el{123.456, Op::None};
  ASSERT_INT(list.size(), 0)
  list.push(el);
  ASSERT_INT(list.size(), 1)
  list.push(el);
  ASSERT_INT(list.size(), 2)
  return true;
}

inline bool EraseTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push({(double)i, Op::None});
  }
  ASSERT_INT(list.size(), 10);
  for (auto i = 0; i < 10; i++) {
    ASSERT_DBL(list.get(i).value, (double)i);
  }
  list.erase(0);
  ASSERT_INT(list.size(), 9);
  for (auto i = 0; i < list.size(); i++) {
    ASSERT_DBL(list.get(i).value, (double)i + 1);
  }
  return true;
}

inline bool GetTest() {
  BEGIN_TEST
  DigiOpList list;
  list.push({123, Op::None});
  ASSERT_DBL(list.get(0).value, 123.0)
  return true;
}

inline bool LimitsTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < MAX_DIGIOPLIST_SIZE; i++) {
    list.push({(double)i, Op::None});
  }
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  // Warning should print here
  list.push({123.123, Op::None});
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  return true;
}

inline bool All() {
  RUN_TEST(PushTest())
  RUN_TEST(GetTest())
  RUN_TEST(SizeTest())
  RUN_TEST(EraseTest())
  RUN_TEST(LimitsTest())
  return true;
}

} // namespace DigiOpTest
