#include "measure.hpp"

#include <assert.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

#include "core.hpp"
#include "test_gen.hpp"

namespace ssmhasher {
Nanoseconds SingleSpeedTest(HashFunction func, std::byte* key,
                            std::size_t key_len, std::byte* out,
                            std::size_t out_len) {
  TimePoint begin = Now();
  func(key, key_len, out, out_len);
  return AsNanoseconds(Now() - begin);
}

Nanoseconds SpeedTest(HashFunction func, std::size_t attempts,
                      TestGen& test_gen, std::size_t key_len,
                      std::size_t out_len) {
  using namespace std::chrono_literals;
  std::byte* key_storage = new std::byte[key_len];
  std::byte* out_storage = new std::byte[out_len];

  std::vector<Nanoseconds> time_of_tests;
  time_of_tests.reserve(attempts);
  for (std::size_t i = 0; i < attempts; ++i) {
    test_gen.gen(key_storage, key_len);
    auto current_test_time =
        SingleSpeedTest(func, key_storage, key_len, out_storage, out_len);
    time_of_tests.push_back(current_test_time);
  }
  
  sort(time_of_tests.begin(), time_of_tests.end(),
       [&](auto a, auto b) { return a.count() < b.count(); });

  Nanoseconds response =
      accumulate(begin(time_of_tests), end(time_of_tests), AsNanoseconds(0ns),
                 [&](auto a, auto b) { return a + b; });

  delete[] out_storage;
  delete[] key_storage;

  return Nanoseconds(response.count() / time_of_tests.size());
}

}  // namespace ssmhasher
