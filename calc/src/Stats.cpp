#include "src/Stats.hpp"
#include "src/util/HashMap.hpp"
#include "src/util/String.hpp"

namespace Stats {

HashMap<double, 64> times;

void Update(const char *tag, double ms) { times.set(tag, ms); }

void Print() {
  for (const char *key : times.keys) {
    if (StrLen(key) > 0) {
      printf("%s:%f\n", key, times.get(key));
    }
  }
}

}; // namespace Stats
