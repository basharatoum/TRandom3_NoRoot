#include "RandomEngine.h"
#include <iostream>
#include <stdint.h>
namespace Garfield {

RandomEngine randomEngine;

RandomEngine::RandomEngine() : m_rng(0) {}

RandomEngine::~RandomEngine() {}

void RandomEngine::Seed(const unsigned int s) {
  m_rng.SetSeed(s);
  std::cout << "RandomEngineRoot::Seed:\n"
            << "    Seed: " << m_rng.GetSeed() << "\n";
}

void RandomEngine::Print() {
  std::cout << "RandomEngineRoot::Print:\n"
            << "    Generator type: TRandom3\n"
            << "    Seed: " << m_rng.GetSeed() << "\n";
}
}
