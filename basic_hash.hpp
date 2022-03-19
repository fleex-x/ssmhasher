#pragma once

#include <cstddef>

namespace basic_hash {
//    void xxhash32(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);
//
//    void xxhash64(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);

    void murMurHash1(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);

    void murMurHash2(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);

    void murMurHash2_64(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);

    void murMurHash3_32(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);

    void murMurHash3_128(std::byte* key, size_t key_len, std::byte* out, std::size_t out_len);
}
