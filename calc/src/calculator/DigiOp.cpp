#include "src/calculator/DigiOp.hpp"
#include <cstdio>

const unsigned int DigiOpList::size() const { return writeIdx; }

const DigiOp DigiOpList::get(unsigned int index) const {
  if (index < writeIdx) {
    return data[index];
  }
  printf("DigiOpList::get. Attempted to read index %i in buffer of size %i. "
         "Returning first item.\n",
         index, writeIdx);
  return data[0];
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
