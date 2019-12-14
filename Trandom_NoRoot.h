// @(#)root/mathcore:$Id$
// Author: Peter Malzacher   31/08/99

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TRandom3
#define ROOT_TRandom3
#include <stdint.h>
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TRandom3                                                             //
//                                                                      //
// random number generator class: Mersenne Twister                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


class TRandom3{
protected:
   uint64_t   fSeed;
private:
   uint32_t   fMt[624];
   int    fCount624;

public:
   TRandom3(uint32_t seed=4357);
   ~TRandom3();
   double  Rndm();
   void      RndmArray(int n, float *array);
   void      RndmArray(int n,double *array);
   void      SetSeed(uint64_t seed=0);
   uint32_t GetSeed();
};
#endif