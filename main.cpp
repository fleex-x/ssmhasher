
#include "measure.hpp"
#include "test_gen.hpp"
#include "basic_hash.hpp"

#include <assert.h>
#include <cstring>

#include <iostream>

void memcpy_wrapper(std::byte * in, std::size_t key_len, std::byte * out, std::size_t out_len) {
    assert(key_len <= out_len);
    memcpy((void*)out, (const void *)in, (int)key_len);
}

int main() {
    using namespace ssmhasher;
    using namespace basic_hash;


    TestGen tg;
    auto b = std::chrono::steady_clock::now();
    auto snds = SpeedTest(xxhash32, 5, tg, 1'000'000, 4);

    std::cout << "Time taken(xxsh32), microsec.: " << snds << '\n';

    snds = SpeedTest(xxhash64, 5, tg, 1'000'000, 8);

    std::cout << "Time taken(xxhash64), microsec.: " << snds << '\n';

    snds = SpeedTest(murMurHash2_64, 5, tg, 1'000'000, 8);

    std::cout << "Time taken(mmh2_64), microsec.: " << snds << '\n';

}