 // @(#)root/mathcore:$Id$
 // Author: Peter Malzacher   31/08/99
 
 /**
  
 Random number generator class based on
   M. Matsumoto and T. Nishimura,
   Mersenne Twister: A 623-diminsionally equidistributed
   uniform pseudorandom number generator
   ACM Transactions on Modeling and Computer Simulation,
   Vol. 8, No. 1, January 1998, pp 3--30.
 
 For more information see the Mersenne Twister homepage
   [http://www.math.keio.ac.jp/~matumoto/emt.html]
 
 Advantage: 
 
 -  large period 2**19937 -1
 -  relativly fast (slightly slower than TRandom2 but much faster than TRandom1)
 
 Drawback: 
 -  a relative large internal state of 624 integers 
 - generate only 32 random bits 
 - not passing all the random generator tests. It fails some tests in TestU01
  (see [http://simul.iro.umontreal.ca/testu01/tu01.html])
 
 An altenativly excellent generator passing all tests of TestU01, having 61 random bits and 
 fast as Mersenne and Twister is MIXMAX (TRandomMixMax). 
 
 
 */
 
 //////////////////////////////////////////////////////////////////////
 // Aug.99 ROOT implementation based on CLHEP by P.Malzacher
 //
 // the original code contains the following copyright notice:
 /* This library is free software; you can redistribute it and/or   */
 /* modify it under the terms of the GNU Library General Public     */
 /* License as published by the Free Software Foundation; either    */
 /* version 2 of the License, or (at your option) any later         */
 /* version.                                                        */
 /* This library is distributed in the hope that it will be useful, */
 /* but WITHOUT ANY WARRANTY; without even the implied warranty of  */
 /* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            */
 /* See the GNU Library General Public License for more details.    */
 /* You should have received a copy of the GNU Library General      */
 /* Public License along with this library; if not, write to the    */
 /* Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   */
 /* 02111-1307  USA                                                 */
 /* Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.       */
 /* When you use this, send an email to: matumoto@math.keio.ac.jp   */
 /* with an appropriate reference to your work.                     */
 /////////////////////////////////////////////////////////////////////
 
 #include "Trandom_NoRoot.h"
#include <stdint.h> 
 ////////////////////////////////////////////////////////////////////////////////
 /// Default constructor
 /// If seed is 0, the seed is automatically computed via a TUUID object.
 /// In this case the seed is guaranteed to be unique in space and time.
 
 TRandom3::TRandom3(uint32_t seed)
 {
    //Random number generator: Mersenne Twister
    SetSeed(seed);
 }
 
 ////////////////////////////////////////////////////////////////////////////////
 /// Default destructor
 
 TRandom3::~TRandom3()
 {
 }
 
 ////////////////////////////////////////////////////////////////////////////////
 ///  Machine independent random number generator.
 ///  Produces uniformly-distributed floating points in (0,1)
 ///  Method: Mersenne Twister
 
 double TRandom3::Rndm()
 {
    uint32_t y;
 
    const int  kM = 397;
    const int  kN = 624;
    const uint32_t kTemperingMaskB =  0x9d2c5680;
    const uint32_t kTemperingMaskC =  0xefc60000;
    const uint32_t kUpperMask =       0x80000000;
    const uint32_t kLowerMask =       0x7fffffff;
    const uint32_t kMatrixA =         0x9908b0df;
 
    if (fCount624 >= kN) {
       int i;
 
       for (i=0; i < kN-kM; i++) {
          y = (fMt[i] & kUpperMask) | (fMt[i+1] & kLowerMask);
          fMt[i] = fMt[i+kM] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
       }
 
       for (   ; i < kN-1    ; i++) {
          y = (fMt[i] & kUpperMask) | (fMt[i+1] & kLowerMask);
          fMt[i] = fMt[i+kM-kN] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
       }
 
       y = (fMt[kN-1] & kUpperMask) | (fMt[0] & kLowerMask);
       fMt[kN-1] = fMt[kM-1] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
       fCount624 = 0;
    }
 
    y = fMt[fCount624++];
    y ^=  (y >> 11);
    y ^= ((y << 7 ) & kTemperingMaskB );
    y ^= ((y << 15) & kTemperingMaskC );
    y ^=  (y >> 18);
 
    // 2.3283064365386963e-10 == 1./(max<uint32_t>+1)  -> then returned value cannot be = 1.0
    if (y) return ( (double) y * 2.3283064365386963e-10); // * Power(2,-32)
    return Rndm();
 }
 
 ////////////////////////////////////////////////////////////////////////////////
 /// Return an array of n random numbers uniformly distributed in ]0,1]
 
 void TRandom3::RndmArray(int n, float *array)
 {
   for(int i=0; i<n; i++) array[i]=(float)Rndm();
 }
 
 ////////////////////////////////////////////////////////////////////////////////
 /// Return an array of n random numbers uniformly distributed in ]0,1]
 
 void TRandom3::RndmArray(int n, double *array)
 {
    int k = 0;
 
    uint32_t y;
 
    const int  kM = 397;
    const int  kN = 624;
    const uint32_t kTemperingMaskB =  0x9d2c5680;
    const uint32_t kTemperingMaskC =  0xefc60000;
    const uint32_t kUpperMask =       0x80000000;
    const uint32_t kLowerMask =       0x7fffffff;
    const uint32_t kMatrixA =         0x9908b0df;
 
    while (k < n) {
       if (fCount624 >= kN) {
          int i;
 
          for (i=0; i < kN-kM; i++) {
             y = (fMt[i] & kUpperMask) | (fMt[i+1] & kLowerMask);
             fMt[i] = fMt[i+kM] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
          }
 
          for (   ; i < kN-1    ; i++) {
             y = (fMt[i] & kUpperMask) | (fMt[i+1] & kLowerMask);
             fMt[i] = fMt[i+kM-kN] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
          }
 
          y = (fMt[kN-1] & kUpperMask) | (fMt[0] & kLowerMask);
          fMt[kN-1] = fMt[kM-1] ^ (y >> 1) ^ ((y & 0x1) ? kMatrixA : 0x0);
          fCount624 = 0;
       }
 
       y = fMt[fCount624++];
       y ^=  (y >> 11);
       y ^= ((y << 7 ) & kTemperingMaskB );
       y ^= ((y << 15) & kTemperingMaskC );
       y ^=  (y >> 18);
 
       if (y) {
          array[k] = double( y * 2.3283064365386963e-10); // * Power(2,-32)
          k++;
       }
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////////
 ///  Set the random generator sequence
 /// if seed is 0 (default value) a TUUID is generated and used to fill
 /// the first 8 integers of the seed array.
 /// In this case the seed is guaranteed to be unique in space and time.
 /// Use upgraded seeding procedure to fix a known problem when seeding with values
 /// with many zero in the bit pattern (like 2**28).
 /// see http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
 
 void TRandom3::SetSeed(uint64_t seed)
 {
    this->fSeed = seed;
    fCount624 = 624;
    if (seed > 0) {
       fMt[0] = fSeed;
 
       // use multipliers from  Knuth's "Art of Computer Programming" Vol. 2, 3rd Ed. p.106
       for(int i=1; i<624; i++) {
          fMt[i] = (1812433253 * ( fMt[i-1]  ^ ( fMt[i-1] >> 30)) + i );
       }
 
    } else {
        // LFSR random number
        uint32_t iState = 3456223233,bit;
    
        // PN sequance of X^32+X^22+X^2+X+1
        bit = ((iState) ^(iState >> 1) ^(iState >> 21) ^ (iState >> 31)) & 1;
        iState =  (iState >> 1) | (bit <<31);

       for (int i = 0; i< 624; i++) {
          fMt[i]   = static_cast<uint32_t> (iState);
          bit = ((iState) ^(iState >> 1) ^(iState >> 21) ^ (iState >> 31)) & 1;
          iState =  (iState >> 1) | (bit <<31);
       }
       // warm up the generator calling it 10 times
       for (int i = 0; i < 10; ++i) Rndm();
    }
 }

uint32_t TRandom3::GetSeed(){
    return this->fSeed;
}
 