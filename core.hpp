#pragma once

#include <chrono>
#include <cstddef>

namespace ssmhasher {
using Microseconds =
    std::chrono::duration<long long, std::micro>;
using Milliseconds =
    std::chrono::duration<long long, std::milli>;
using Seconds = std::chrono::duration<long long>;
using RealMicroseconds = double;
using RealMilliseconds = double;
using RealSeconds = double;

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

}  // namespace ssmhasher