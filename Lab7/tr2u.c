#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char* from = argv[1];
  char* to = argv[2];

  if (strlen(from) != strlen(to)) {
    exit(0);
  }

  for (int i = 0; i < strlen(from); i++) {
    for (int x = 0; x < strlen(from); x++) {
      if (i != x && from[i] == from[x]) {
	exit(0);
      }
    }
  }

  char readbuf[2];
  char writebuf[2];
  int stat = read(0, readbuf, 1);
  while (stat != 0) {
    if (stat < 0) {
      exit(0);
    }
    
    char* ret = strchr(from, readbuf[0]);
    if (ret != NULL) {
      writebuf[0] = to[strlen(from) - strlen(ret)];
      write(1, writebuf, 1);
    }
    else {
      writebuf[0] = readbuf[0];
      write(1, writebuf, 1);
    }
    
    stat = read(0, readbuf, 1);
  }
}

