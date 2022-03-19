#include <assert.h>

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

#include <iostream>

#include "core.hpp"
#include "test_gen.hpp"

#include "measure.hpp"

namespace ssmhasher {
Microseconds SingleSpeedTest(HashFunction func, std::byte* key,
                             std::size_t key_len, std::byte* out,
                             std::size_t out_len) {
  TimePoint begin = Now();
  func(key, key_len, out, out_len);
  return AsMicroseconds(Now() - begin);
}

RealMicroseconds SpeedTest(HashFunction func, std::size_t attempts,
                       TestGen& test_gen, std::size_t key_len,
                       std::size_t out_len) {
  std::byte* key_storage = new std::byte[key_len];
  std::byte* out_storage = new std::byte[out_len];

  std::vector<Microseconds> time_of_tests;
  time_of_tests.reserve(attempts);
  for (std::size_t i = 0; i < attempts; ++i) {
    test_gen.gen(key_storage, key_len);
    auto current_test_time =
        SingleSpeedTest(func, key_storage, key_len, out_storage, out_len);
    time_of_tests.push_back(current_test_time);
  }

  std::vector<double> real_times(time_of_tests.size(), 0.0);
  std::transform(
      time_of_tests.begin(), time_of_tests.end(), real_times.begin(),
      [&](auto time) -> double { return time.count(); });

  // assume there is no Nan's 
  sort(real_times.begin(), real_times.end());

  RealMicroseconds response = std::accumulate(begin(real_times), end(real_times), 0.0);

  delete[] out_storage;
  delete[] key_storage;

  // constexpr std::size_t MS_PER_SECOND = 1000;

  return (response ) / real_times.size();
}

}  // namespace ssmhasher