#include "randcpuid.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>


int main (int argc, char** argv) {
  bool valid = false;
  long long nbytes;
  if (argc == 2) {
    char *endptr;
    errno = 0;
    nbytes = strtoll (argv[1], &endptr, 10);
    if (errno)
      perror (argv[1]);
    else
      valid = !*endptr && 0 <= nbytes;
  }
  if (!valid) {
    fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    return 1;
  }
  
  
  if (nbytes == 0)
    return 0;

  
  void* hard;
  void* soft;
  char* error;
  
  unsigned long long (*rand64)(void);
  
  
  hard = dlopen("randlibhw.so", RTLD_NOW);
  if (hard == NULL) {
    error = dlerror();
    printf("Failed to open randlibhw.so:%s\n", error);
    exit(1);
  }
  
  soft = dlopen("randlibsw.so", RTLD_NOW);
  if (soft == NULL) {
    error = dlerror();
    printf("Failed to open randlibsw.so:%s\n", error);
    exit(1);
  }
  
  
  
  
  if (rdrand_supported()) { 
    rand64 = dlsym(hard, "hardware_rand64");
    if (dlerror()){
      error = dlerror();
      printf("Failed to locate rand64():%s\n", error);
      exit(1);
    }
  }
  else {   
    rand64 = dlsym(soft, "software_rand64");
   if (dlerror()){
     error = dlerror();
     printf("Failed to locate rand64():%s\n", error);
     exit(1);
   }
  }
  
    
  int wordsize = sizeof rand64 ();
  int output_errno = 0;
  
  do {
    unsigned long long x = rand64();
    size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
    if (fwrite (&x, 1, outbytes, stdout) != outbytes) {
      output_errno = errno;
      break;
    }
    nbytes -= outbytes;
  }
  while (0 < nbytes);
  
  if (fclose (stdout) != 0)
    output_errno = errno;
  
  if (output_errno) {
    errno = output_errno;
    perror ("output");
    return 1;
  }

  dlclose(hard);
  dlclose(soft);
  return 0;
}


