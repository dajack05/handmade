
#include "src/calculator/DigiOp.hpp"
#include "src/tests/TestMacros.hpp"
#include "src/util/String.hpp"
#include <cstdio>

namespace DigiOpTest {

inline bool PushTest() {
  BEGIN_TEST
  DigiOpList list;
  list.push(123.456);
  ASSERT_DBL(list.get(0).value, 123.456)
  list.push(222.22);
  ASSERT_DBL(list.get(1).value, 222.22)
  return true;
}

inline bool SizeTest() {
  BEGIN_TEST
  DigiOpList list;
  ASSERT_INT(list.size(), 0)
  list.push(123.456);
  ASSERT_INT(list.size(), 1)
  list.push(123.456);
  ASSERT_INT(list.size(), 2)
  return true;
}

inline bool EraseTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push((double)i);
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
  list.push(123.0);
  ASSERT_DBL(list.get(0).value, 123.0)
  return true;
}

inline bool LimitsTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < MAX_DIGIOPLIST_SIZE; i++) {
    list.push((double)i);
  }
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  // Warning should print here
  list.push(123.123);
  ASSERT_INT(list.size(), MAX_DIGIOPLIST_SIZE)

  return true;
}

inline bool ClearTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push((double)i);
  }
  ASSERT_INT(list.size(), 10);
  list.clear();
  ASSERT_INT(list.size(), 0);
  return true;
}

inline bool LastTest() {
  BEGIN_TEST
  DigiOpList list;
  for (auto i = 0; i < 10; i++) {
    list.push((double)i);
  }

  ASSERT_DBL(list.last().value, 9.0);

  return true;
}

inline bool ToStringTest() {
  BEGIN_TEST
  DigiOpList list;
  list.pushAll({
      1,
      Op::Add,
      2,
      Op::Subtract,
      3,
      Op::Multiply,
      4,
      Op::Divide,
      5,
      Op::ParenOpen,
      6,
      Op::ParenClose,
  });

  char str[512] = {0};
  list.toString(str, 512);
  const char *expectedStr = "1 + 2 - 3 * 4 / 5 ( 6 )";
  ASSERT_INT(StrLen(str), StrLen(expectedStr));
  for (auto i = 0; i < StrLen(str); i++) {
    ASSERT_CHAR(str[i], expectedStr[i]);
  }

  return true;
}

inline bool All() {
  RUN_TEST(PushTest())
  RUN_TEST(GetTest())
  RUN_TEST(SizeTest())
  RUN_TEST(EraseTest())
  RUN_TEST(LimitsTest())
  RUN_TEST(ClearTest())
  RUN_TEST(ToStringTest())
  return true;
}

} // namespace DigiOpTest
