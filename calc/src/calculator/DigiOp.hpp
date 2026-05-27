#pragma once

#define MAX_DIGIOPLIST_SIZE 2048

enum class Op {
  None,
  Add,
  Subtract,
  Multiply,
  Divide,
};

struct DigiOp {
  double value = 0.0;
  Op op = Op::None;
};

class DigiOpList {
public:
  const unsigned int size();
  const DigiOp get(unsigned int index);
  const unsigned int push(const DigiOp digiOp);
  void erase(unsigned int index);

private:
  DigiOp data[MAX_DIGIOPLIST_SIZE];
  unsigned int writeIdx = 0;
};
