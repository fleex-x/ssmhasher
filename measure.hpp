#pragma once

#include <assert.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

#include "core.hpp"
#include "test_gen.hpp"

namespace ssmhasher {
Milliseconds SingleSpeedTest(HashFunction func, std::byte* key,
                             std::size_t key_len, std::byte* out,
                             std::size_t out_len);
RealSeconds SpeedTest(HashFunction func, std::size_t attempts,
                      TestGen& test_gen, std::size_t key_len,
                      std::size_t out_len);

}  // namespace ssmhasher