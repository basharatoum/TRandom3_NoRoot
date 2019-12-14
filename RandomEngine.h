#ifndef G_RANDOM_ENGINE_H
#define G_RANDOM_ENGINE_H

#include "Trandom_NoRoot.h"
#include <stdint.h>
namespace Garfield {

/// ROOT random number generator.

class RandomEngine{
 public:
  /// Constructor
  RandomEngine();
  /// Destructor
  ~RandomEngine();
  /// Call the random number generator.
  double Draw(){ return m_rng.Rndm(); }
  /// Initialise the random number generator.
  void Seed(const unsigned int s) ;
  /// Print information about the generator used and the seed. 
  void Print();

 private:
  TRandom3 m_rng;
};

}

#endif
