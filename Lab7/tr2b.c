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

  char cur = getchar();
  while (cur != EOF) {
    char* ret = strchr(from, cur);
    if (ret != NULL) {
      putchar(to[strlen(from) - strlen(ret)]);
    }
    else
      putchar(cur);

    cur = getchar();
  }
}
