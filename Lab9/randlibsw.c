

#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>

void software_rand64_init (void) __attribute__((constructor));
void software_rand64_fini (void) __attribute__((destructor));


static FILE *urandstream;


extern unsigned long long software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

extern void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

extern void
software_rand64_fini (void)
{
  fclose (urandstream);
}

