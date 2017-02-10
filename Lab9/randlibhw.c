#include "randlib.h"
#include <immintrin.h>



extern void
hardware_rand64_init (void)
{
}


extern unsigned long long hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

extern void
hardware_rand64_fini (void)
{
}
