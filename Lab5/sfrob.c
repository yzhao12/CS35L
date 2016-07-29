#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void* a, const void* b) {
  char* word1 = *(char**)a;
  char* word2 = *(char**)b;

  int aa = 0;
  int bb = 0;
  for ( ; word1[aa] != ' ' && word2[bb] != ' '; aa++, bb++) {
    if ((char)(word1[aa] ^ 42) < (char)(word2[bb] ^ 42))
      return -1;
    if ((char)(word1[aa] ^ 42) > (char)(word2[bb] ^ 42))
      return 1;
  }
  if (word1[aa] == ' ' && word2[bb] == ' ')
    return 0;
  if (word1[aa] == ' ')
    return -1;
}





  
int main() {
  char** words;
  int numWords = 0;
  int currentCols = 1000;
  int currentWord = 0;
  int currentLetter = 0;

  words = malloc(currentCols * sizeof(char*));

  char curChar = '~';
  while (curChar != EOF) {
    curChar = getchar();
    if (numWords == currentCols) {
      words = realloc(words, (currentCols + 100) * sizeof(char*));
      currentCols += 100;
    }


    if (curChar == '\377')
      break;

    if (curChar == ' ') {
      words[currentWord] = realloc(words[currentWord], currentLetter + 1);
      words[currentWord][currentLetter] = ' ';
      currentLetter = 0;
      currentWord++;
      numWords++;
      continue;
    } else if (currentLetter == 0) {
      words[currentWord] = malloc(sizeof(char));
      words[currentWord][currentLetter] = curChar;
    } else {
      words[currentWord] = realloc(words[currentWord], currentLetter + 1);
      words[currentWord][currentLetter] = curChar;
    }

    currentLetter++;
  }

  if (currentLetter != 0 && words[currentWord - 1][currentLetter - 1] != 0) {
    words[currentWord] = realloc(words[currentWord], currentLetter);
    words[currentWord][currentLetter] = ' ';
    numWords++;
  }
	    
  qsort(words, numWords, sizeof(char*), frobcmp);

  for (int r = 0; r < numWords; r++) {
    for (int c = 0; words[r][c] != '\0'; c++) {
      putchar(words[r][c]);
    }
  }
  
  for (int i = 0; i < numWords; i++) {
    free(words[i]);
  }
  free(words);
}
