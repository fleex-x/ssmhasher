#include "basic_hash.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "MurmurHash1.h"
#include "MurmurHash2.h"
#include "MurmurHash3.h"
#include "xxhash.h"

namespace basic_hash {
void xxhash32(std::byte* key, size_t key_len, std::byte* out,
              std::size_t out_len) {
  *(XXH32_hash_t*)out = XXH32(reinterpret_cast<void*>(key), key_len, 0);
}

void xxhash64(std::byte* key, size_t key_len, std::byte* out,
              std::size_t out_len) {
  *(XXH64_hash_t*)out = XXH64(reinterpret_cast<void*>(key), key_len, 0);
}

void murMurHash1(std::byte* key, size_t key_len, std::byte* out,
                 std::size_t out_len) {
  *(uint32_t*)out = MurmurHash1(reinterpret_cast<void*>(key), key_len, 0);
}

void murMurHash2(std::byte* key, size_t key_len, std::byte* out,
                 std::size_t out_len) {
  uint32_t hash = MurmurHash2(reinterpret_cast<void*>(key), key_len, 0);
}

void murMurHash2_64(std::byte* key, size_t key_len, std::byte* out,
                    std::size_t out_len) {
  *(uint32_t*)out = MurmurHash64A(reinterpret_cast<void*>(key), key_len, 0);
}

void murMurHash3_32(std::byte* key, size_t key_len, std::byte* out,
                    std::size_t out_len) {
  MurmurHash3_x86_32(reinterpret_cast<void*>(key), key_len, 0,
                     reinterpret_cast<void*>(out));
}

void murMurHash3_128(std::byte* key, size_t key_len, std::byte* out,
                     std::size_t out_len) {
  MurmurHash3_x86_128(reinterpret_cast<void*>(key), key_len, 0,
                      reinterpret_cast<void*>(out));
}
}  // namespace basic_hash
