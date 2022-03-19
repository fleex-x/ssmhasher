
#include <assert.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include "basic_hash.hpp"
#include "measure.hpp"
#include "stat.hpp"
#include "test_gen.hpp"

void memcpy_wrapper(std::byte *in, std::size_t key_len, std::byte *out,
                    std::size_t out_len) {
  assert(key_len <= out_len);
  memcpy((void *)out, (const void *)in, (int)key_len);
}

const ssmhasher::HashFuncInfo table[] = {
    {"memcpy", memcpy_wrapper, INT32_MAX},
    {"xxhash32", basic_hash::xxhash32, 4},
    {"xxhash64", basic_hash::xxhash64, 8},
    {"murMurHash1", basic_hash::murMurHash1, 4},
    {"murMurHash2", basic_hash::murMurHash2, 4},
    {"murMurHash2_64", basic_hash::murMurHash2_64, 8},
    {"murMurHash3_32", basic_hash::murMurHash3_32, 4},
    {"murMurHash3_128", basic_hash::murMurHash3_128, 16}};

int main() {
  using namespace ssmhasher;

  nlohmann::json chart1;
  nlohmann::json chart2;

  for (const auto &HF : table) {
    Stat stat(HF);
    stat.setStep(2);
    stat.setAttempts(1000);
    chart1[HF.name] = stat.buildJson(1, 100)[HF.name];
  }

  for (const auto &HF : table) {
    Stat stat(HF);
    stat.setStep(50);
    stat.setAttempts(1000);
    chart2[HF.name] = stat.buildJson(100, 1000)[HF.name];
  }

#if defined(__aarch64__)
  std::ofstream out1("chart1_m1.json");
  out1 << std::setw(2) << chart1 << std::endl;
  out1.close();

  std::ofstream out2("chart2_m1.json");
  out2 << std::setw(2) << chart2 << std::endl;
  out2.close();
#else
  std::ofstream out1("chart1.json");
  out1 << std::setw(2) << chart1 << std::endl;
  out1.close();

  std::ofstream out2("chart2.json");
  out2 << std::setw(2) << chart2 << std::endl;
  out2.close();
#endif
  return 0;
}