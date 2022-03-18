#pragma once

#include <chrono>
#include <cstddef>

namespace ssmhasher {
using Microseconds =
    std::chrono::duration<std::size_t, std::chrono::microseconds>;
using Milliseconds =
    std::chrono::duration<std::size_t, std::chrono::milliseconds>;
using Seconds = std::chrono::duration<std::size_t, std::chrono::seconds>;
using RealSeconds = double;
using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;

using HashFunction = void (*)(std::byte* key, size_t key_len, std::byte* out,
                              std::size_t out_len);

TimePoint Now() { return Clock::now(); }

template <typename Duration>
Microseconds AsMicroseconds(Duration dur) {
  return std::duration_cast<std::chrono::microseconds>(dur);
}

template <typename Duration>
Milliseconds AsMilliseconds(Duration dur) {
  return std::duration_cast<std::chrono::microseconds>(dur);
}

template <typename Duration>
Seconds AsSeconds(Duration dur) {
  return std::duration_cast<std::chrono::microseconds>(dur);
}

}  // namespace ssmhasher