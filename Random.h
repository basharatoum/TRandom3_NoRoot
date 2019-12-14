#ifndef G_RANDOM_H
#define G_RANDOM_H

#include <cmath>
#include "RandomEngine.h"

namespace Garfield {

/// Random number generator
extern RandomEngine randomEngine;

/// Draw a random number uniformly distributed in the range [0, 1).
inline double RndmUniform() { return randomEngine.Draw(); }

/// Draw a random number uniformly distributed in the range (0, 1).
inline double RndmUniformPos() {
  double r = RndmUniform();
  while (r <= 0.) r = RndmUniform();
  return r;
}

/// Draw a Gaussian random variate with mean zero and standard deviation one.
inline double RndmGaussian() {
  static bool cached = false;
  static double u = 0.;
  if (cached) {
    cached = false;
    return u;
  }
  // Box-Muller algorithm
  u = 2. * RndmUniform() - 1.;
  double v = 2. * RndmUniform() - 1.;
  double r2 = u * u + v * v;
  while (r2 > 1.) {
    u = 2. * RndmUniform() - 1.;
    v = 2. * RndmUniform() - 1.;
    r2 = u * u + v * v;
  }
  const double p = sqrt(-2. * log(r2) / r2);
  u *= p;
  cached = true;
  return v * p;
}

} 
#endif

