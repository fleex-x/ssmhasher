
#include "measure.hpp"
#include "test_gen.hpp"
#include "basic_hash.hpp"

#include <assert.h>
#include <cstring>

#include <iostream>

void raw_access_wrapper(std::byte * in, std::size_t key_len, std::byte * out, std::size_t out_len) {
    assert(key_len <= out_len);
    // memcpy((void*)out, (const void *)in, (int)key_len);
     for (int i = 0; i < key_len; ++i) {
        volatile std::byte x = in[i];
    }
}

void memcpy_wrapper(std::byte * in, std::size_t key_len, std::byte * out, std::size_t out_len) {
    assert(key_len <= out_len);
    memcpy((void*)out, (const void *)in, (int)key_len);
    //  for (int i = 0; i < key_len; ++i) {
        // volatile std::byte x = in[i];
    // }
}

int main() {
    using namespace ssmhasher;
    using namespace basic_hash;


    TestGen tg;
    auto b = std::chrono::steady_clock::now();
    auto snds = SpeedTest(xxhash64, 5, tg, 1'000'000, 4);

    std::cout << "Time taken(xxsh_64), microsec.: " << snds << '\n';

    snds = SpeedTest(murMurHash3_128, 5, tg, 1'000'000, 8);

    std::cout << "Time taken(mmh3_128), microsec.: " << snds << '\n';

    snds = SpeedTest(xxhash64, 5, tg, 1'000'000, 8);

    std::cout << "Time taken(xxhash_64), microsec.: " << snds << '\n';

    snds = SpeedTest(raw_access_wrapper, 5, tg, 1'000'000, 1'000'000);

    std::cout << "Time taken(just for by byte), microsec.: " << snds << '\n';

    snds = SpeedTest(memcpy_wrapper, 5, tg, 1'000'000, 1'000'000);

    std::cout << "Time taken(memcpy), microsec.: " << snds << '\n';
    

}