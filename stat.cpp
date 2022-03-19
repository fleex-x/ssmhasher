#include "stat.hpp"

#include <stdio.h>

#include <iostream>
#include <string>

namespace ssmhasher {

RealMicroseconds Stat::runTest(std::size_t in_len) {
  return SpeedTest(funcInfo.func, attempts, TG, in_len, funcInfo.out_len);
}

void Stat::setAttempts(std::size_t attempts_) { attempts = attempts_; }

void Stat::setStep(std::size_t step_) { step = step_; }

Stat::Stat(const HashFuncInfo& HF)
    : funcInfo(HF), attempts(100), step(1), TG(1) {}

void Stat::runTests(std::size_t l, std::size_t r) {
  for (std::size_t i = l; i < r; i += step) {
    printf("%f\n", runTest(i));
  }
}

nlohmann::json Stat::buildJson(std::size_t l, std::size_t r) {
  nlohmann::json js;

  for (std::size_t i = l; i < r; i += step) {
    RealMicroseconds result = runTest(i);
    js[funcInfo.name].push_back({std::to_string(i), std::to_string(result)});
  }

  return js;
}

}  // namespace ssmhasher
