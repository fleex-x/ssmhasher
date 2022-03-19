
#include <assert.h>

#include <cstring>
#include <iostream>
#include <random>

#include "basic_hash.hpp"
#include "measure.hpp"
#include "test_gen.hpp"

void raw_access_wrapper(std::byte *in, std::size_t key_len, std::byte *out,
                        std::size_t out_len) {
  // assert(key_len <= out_len);
  for (int i = 0; i < key_len; ++i) {
    volatile std::byte x = in[i];
  }
}

void memcpy_wrapper(std::byte *in, std::size_t key_len, std::byte *out,
                    std::size_t out_len) {
  // assert(key_len <= out_len);
  memcpy((void *)out, (const void *)in, (int)key_len);
}

int main() {
  using namespace ssmhasher;
  using namespace basic_hash;

  TestGen tg (std::rand());
  auto b = std::chrono::steady_clock::now();

  constexpr std::size_t key_len = 100;
  constexpr std::size_t attempts = 10000;

  auto ns = SpeedTest(xxhash64, attempts, tg, key_len, 20);

  std::cout << "Time taken(xxhash_64), nanosec.: " << ns.count() << '\n';

  ns = SpeedTest(murMurHash3_128, attempts, tg, key_len, 20);

  std::cout << "Time taken(mmh3_128), nanosec.: " << ns.count() << '\n';

  ns = SpeedTest(raw_access_wrapper, attempts, tg, key_len, key_len);

  std::cout << "Time taken(just for by byte), nanosec.: " << ns.count() << '\n';

  ns = SpeedTest(memcpy_wrapper, attempts, tg, key_len, key_len);

  std::cout << "Time taken(memcpy), nanosec.: " << ns.count() << '\n';
}