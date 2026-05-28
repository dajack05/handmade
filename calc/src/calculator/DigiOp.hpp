#pragma once

#include "src/util/String.hpp"
#include <cstdio>
#define MAX_DIGIOPLIST_SIZE 2048

enum class Op {
  None,
  ParenOpen,
  ParenClose,
  Subtract,
  Add,
  Divide,
  Multiply,
};

struct DigiOp {
  double value = 0.0;
  Op op = Op::None;

  static void PrettyPrint(const DigiOp &item) {
    if (item.op == Op::None) {
      printf("%f", item.value);
    } else {
      char opStr[12] = {0};
      switch (item.op) {
      case Op::None:
        StrCopy("None", opStr, 12);
        break;
      case Op::ParenClose:
        StrCopy("ParenClose", opStr, 12);
        break;
      case Op::ParenOpen:
        StrCopy("ParenOpen", opStr, 12);
        break;
      case Op::Add:
        StrCopy("Add", opStr, 12);
        break;
      case Op::Subtract:
        StrCopy("Subtract", opStr, 12);
        break;
      case Op::Multiply:
        StrCopy("Multiply", opStr, 12);
        break;
      case Op::Divide:
        StrCopy("Divide", opStr, 12);
        break;
      }
      printf("%s", opStr);
    }
  }
};

class DigiOpList {
public:
  const unsigned int size() const;
  const DigiOp get(unsigned int index) const;
  const unsigned int push(const DigiOp digiOp);
  void erase(unsigned int index);

  inline void prettyPrint(void (*printFunc)(const DigiOp &item)) const {
    printf("DigiOpList[%i]:[", MAX_DIGIOPLIST_SIZE);
    for (auto i = 0; i < size(); i++) {
      const DigiOp item = data[i];
      printFunc(item);

      if (i < size() - 1) {
        printf(", ");
      }
    }
    printf("]\n");
  }

private:
  DigiOp data[MAX_DIGIOPLIST_SIZE];
  unsigned int writeIdx = 0;
};
