
#include "measure.hpp"
#include "test_gen.hpp"

#include <assert.h>
#include <cstring>

#include <iostream>

void memcpy_wrapper(std::byte * in, std::size_t key_len, std::byte * out, std::size_t out_len) {
    assert(key_len <= out_len);
    memcpy((void*)out, (const void *)in, (int)key_len);
}

int main() {
    using namespace ssmhasher;


    TestGen tg;
    auto b = std::chrono::steady_clock::now();
    auto snds = SpeedTest(memcpy_wrapper, 1, tg, 1'000'000'000, 1'000'000'000);

    std::cout << "Real time taken: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - b).count() << '\n';
    std::cout << "Time taken: " << snds << '\n';

}