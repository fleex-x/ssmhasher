#include "stat.hpp"

#include <string>

namespace ssmhasher {

Stat::Stat(HashFunction f, std::size_t len)
    : func(f), out_len(len), attempts(100) {}

auto Stat::runTest(std::size_t in_len) {
  return SpeedTest(func, attempts, TG, in_len, out_len);
}

void Stat::setAttempts(std::size_t attempts_) { attempts = attempts_; }

void Stat::setStep(std::size_t step_) {
  step = step_;
}

}  // namespace ssmhasher
