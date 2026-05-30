#pragma once

#include <cstdio>
#include <initializer_list>
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

static const char OpChar[] = {
    '!', '(', ')', '-', '+', '/', '*',
};

struct DigiOp {
  double value = 0.0;
  Op op = Op::None;

  DigiOp() = default;
  DigiOp(double value) : value(value) {}
  DigiOp(Op op) : op(op) {}
  DigiOp(double value, Op op) : value(value), op(op) {}

  static void PrettyPrint(const DigiOp &item);
  inline const bool isOp() const { return op != Op::None; }
};

class DigiOpList {
public:
  const unsigned int size() const;
  DigiOp &get(unsigned int index);

  void push(const DigiOp digiOp);
  inline void push(const double digit) { push(DigiOp{digit}); }
  inline void push(const Op op) { push(DigiOp{op}); }
  void pushAll(std::initializer_list<const DigiOp> digiOps);
  void erase(unsigned int index);
  void clear();
  DigiOp &last();
  void toString(char *destination, unsigned int maxSize) const;

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
