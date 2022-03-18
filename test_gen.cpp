#include "test_gen.hpp"

namespace ssmhasher {

uint32_t TestGen::randU32() {
  mix();
  return x;
}

void TestGen::gen(std::byte *blob, std::size_t size) {
  auto *blocks = reinterpret_cast<uint32_t *>(blob);

  while (size >= 4) {
    blocks[0] = randU32();
    blocks++;
    size -= 4;
  }

  auto *tail = reinterpret_cast<uint8_t *>(blocks);

  for (int i = 0; i < size; i++) {
    tail[i] = (uint8_t)randU32();
  }
}

TestGen::TestGen(uint32_t seed) {
  x = 0x498b3bc5 ^ seed;
  y = 0;
  z = 0;
  w = 0;

  for (int i = 0; i < 10; i++) {
    mix();
  }
}

TestGen::TestGen() : TestGen(0) {}

void TestGen::mix() {
  uint32_t t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

}