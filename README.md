# TRandom3_NoRoot
A version of TRandom3.cc without any Root part, as well as a comparison between TRandom3 and drand. 

This was done for the sole purpose of looking at different random number generators for PyBoltz. PyBoltz needs a random number generator that has a decent amount of uniqeness (a period of around 2^n, where 2^n is on the same order of the number of collisions put into PyBoltz).

The order of magnitude for the number of collisons in PyBoltz is around 1e8 to 1e10. Therefore, n is around 33. 

## Current conclusions:

TRandom3 is used in garfield as the main random number generator, it has a huge period, which is great! However, TRandom3 is pretty slow. It usually takes triple the amount of time to generate the same number of numbers as drand48 or XorShift256+ .

Drand48 is a standerd c library to generate double percision floating numbers. It's speed is really good. It is a great candidate for use in PyBoltz.

XorShift256+, seems to be the best, as it is pretty simple to implement and build upon. It has the same speed as drand48. 
