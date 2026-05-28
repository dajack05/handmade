#include "src/calculator/DigiOp.hpp"
#include "src/util/String.hpp"
#include <cstdio>

const unsigned int DigiOpList::size() const { return writeIdx; }

DigiOp &DigiOpList::get(unsigned int index) {
  if (index < writeIdx) {
    return data[index];
  }
  printf("DigiOpList::get. Attempted to read index %i in buffer of size %i. "
         "Returning first item.\n",
         index, writeIdx);
  return data[0];
}

DigiOp &DigiOpList::last() {
  if (writeIdx > 0) {
    return data[writeIdx - 1];
  }
  return data[writeIdx++];
}

const unsigned int DigiOpList::push(const DigiOp digiOp) {
  if (writeIdx >= MAX_DIGIOPLIST_SIZE) {
    printf("DigiOpList::push. RAN OUT OF ROOM. Consider increasing "
           "MAX_DIGIOPLIST_SIZE.\n");
    return 0;
  }
  const unsigned int idx = writeIdx++;
  data[idx] = digiOp;
  return idx;
}

void DigiOpList::erase(unsigned int index) {
  if (index >= writeIdx) {
    printf("DigiOpList::erase. Attempted to erase non-assigned element at "
           "index %i in list of size %i.\n",
           index, writeIdx);
    return;
  }

  for (auto i = index; i < writeIdx; i++) {
    data[i] = data[i + 1];
  }
  writeIdx--;
}

void DigiOpList::clear() { writeIdx = 0; }

void DigiOpList::toString(char *destination, unsigned int maxSize) const {
  unsigned int strIdx = 0;
  printf("Size: %i. maxSize: %i\n", size(), maxSize);
  for (auto i = 0; i < size() && strIdx < maxSize; i++) {
    const DigiOp digit = data[i];
    if (digit.isOp()) {
      if (strIdx >= maxSize) {
        printf("DigiOpList::toString. Op. Ran out of room in destination.\n");
        return;
      }
      destination[strIdx++] = OpChar[(unsigned int)digit.op];
    } else {
      const char *valueStr = StrFromDouble(digit.value);
      printf("valueStr: %s\n", valueStr);
      for (auto j = 0; j < StrLen(valueStr); j++) {
        if (strIdx >= maxSize) {
          printf(
              "DigiOpList::toString. Value. Ran out of room in destination.\n");
          return;
        }
        destination[strIdx++] = valueStr[j];
      }
    }

    if (i < size() - 1) {
      if (strIdx >= maxSize) {
        printf("DigiOpList::toString. PostSpace. Ran out of room in "
               "destination.\n");
        return;
      }
      destination[strIdx++] = ' ';
    }
  }
  printf("Write %i chars\n", strIdx);
}

void DigiOp::PrettyPrint(const DigiOp &item) {
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
