#pragma once

#include <vector>
#include "measure.hpp"
#include "core.hpp"
#include "json.hpp"

namespace ssmhasher {

struct HashFuncInfo {
  std::string name;
  HashFunction func;
  std::size_t out_len;
};

class Stat {
 private:
  HashFuncInfo funcInfo;
  TestGen TG;
  std::size_t attempts;
  std::size_t step;

 public:
  explicit Stat(const HashFuncInfo &HF);

  void setAttempts(std::size_t attempts_);

  void setStep(std::size_t step_);


  RealSeconds runTest(std::size_t in_len);

  void runTests(std::size_t l, std::size_t r);

  nlohmann::json buildJson(std::size_t l, std::size_t r);

};

}  // namespace ssmhasher