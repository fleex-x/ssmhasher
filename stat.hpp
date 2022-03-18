#pragma once

#include <vector>
#include "measure.hpp"
#include "core.hpp"

namespace ssmhasher {

struct Stat {
  HashFunction func;
  std::size_t out_len;
  TestGen TG;
  std::size_t attempts;
  std::size_t step;

  explicit Stat(HashFunction f, std::size_t len);

  void setAttempts(std::size_t attempts_);

  void setStep(std::size_t step_);
  RealSeconds runTest(std::size_t in_len);


  void set()

};

}  // namespace ssmhasher