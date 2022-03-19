#pragma once

#include <chrono>
#include <cstddef>

#define MAX_TEST_SIZE 1000

namespace ssmhasher {
using Microseconds =
    std::chrono::duration<long long, std::micro>;
using Milliseconds =
    std::chrono::duration<long long, std::milli>;
using Seconds = std::chrono::duration<long long>;
using RealMicroseconds = double;
using RealMilliseconds = double;
using RealSeconds = double;

using Nanoseconds = std::chrono::duration<long long, std::nano>;

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;

using HashFunction = void (*)(std::byte* key, size_t key_len, std::byte* out,
                              std::size_t out_len);

inline TimePoint Now() { return Clock::now(); }

template <typename Duration>
Microseconds AsMicroseconds(Duration dur) {
  return std::chrono::duration_cast<Microseconds>(dur);
}

template <typename Duration>
Milliseconds AsMilliseconds(Duration dur) {
  return std::chrono::duration_cast<Milliseconds>(dur);
}

template <typename Duration>
Seconds AsSeconds(Duration dur) {
  return std::chrono::duration_cast<Seconds>(dur);
}

template <typename Duration>
Nanoseconds AsNanoseconds(Duration dur) {
  return std::chrono::duration_cast<Nanoseconds>(dur);
}


}  // namespace ssmhasher