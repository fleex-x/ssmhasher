#pragma once

#include <assert.h>
#include <cstddef>
#include <vector>

#include "core.hpp"
#include "test_gen.hpp"

namespace ssmhasher {
template <std::size_t KEY_LEN, std::size_t OUT_LEN>
Milliseconds SingleSpeedTest(HashFunction func, std::byte* key) {
  constexpr bool valid_len = OUT_LEN <= 4096;
  static_assert(OUT_LEN <= 4096, "Use another version of 'SingleSpeedTest'");
  TimePoint begin = now();
  std::byte arr[OUT_LEN];
  func(key, KEY_LEN, out, OUT_LEN) return AsMilliseconds(Now() - begin);
}

Milliseconds SingleSpeedTest(HashFunction func, std::byte* key,
                             std::size_t key_len, std::byte* out,
                             std::size_t out_len) {
  TimePoint begin = Now();
  func(key, key_len, out, out_len);
  return AsMilliseconds(Now() - begin);
}

Milliseconds SpeedTest(HashFunction func, std::size_t attempts,
                       TestGen& test_gen, std::size_t key_len,
                       std::size_t out_len) {
  std::byte* key_storage = new std::byte[key_len];
  std::byte* out_storage = new std::byte[out_len];

  std::vector<Milliseconds> time_of_tests;
  time_of_tests.reserve(attempts);
  for (std::size_t i = 0; i < attempts; ++i) {
    test_gen.gen(key_storage, key_len);
    auto current_test_time = SingleSpeedTest(func, key_storage, key_len, out_storage, out_len);
  }

}

}  // namespace ssmhasher