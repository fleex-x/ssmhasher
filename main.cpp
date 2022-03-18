
#include "measure.hpp"
#include "test_gen.hpp"

#include <assert.h>
#include <cstring>

#include <iostream>

void memcpy_wrapper(std::byte * in, std::size_t key_len, std::byte * out, std::size_t out_len) {
    assert(key_len <= out_len);
    // memcpy((void*)out, (const void *)in, (int)key_len);
    for (int i = 0; i < key_len; ++i) {
        volatile auto tmp = in[i];
    }
}

int main() {
    using namespace ssmhasher;

    TestGen tg;
    auto snds = SpeedTest(memcpy_wrapper, 10, tg, 100'000'000, 100'000'000);

    std::cout << "Time tooken: " << snds << '\n';

}