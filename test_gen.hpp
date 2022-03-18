#pragma once

#include <cstdint>
#include <vector>

namespace ssmhasher {
class TestGen {
 private:
  uint32_t x;
  uint32_t y;
  uint32_t z;
  uint32_t w;

  void mix();

  uint32_t randU32();

 public:
  TestGen();

  explicit TestGen(uint32_t seed);

  void gen(std::byte *blob, size_t size);
};

}  // namespace ssmhasher