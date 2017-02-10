#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int comparisons = 0;

int frobcmp(const void* a, const void* b) {
  char* word1 = *(char**)a;
  char* word2 = *(char**)b;

  comparisons++;

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

  char* fileWords;
  int curSize;
  int curPos = 0;

  struct stat fileStat;
  fstat(0, &fileStat);

  if (S_ISREG(fileStat.st_mode)) {
    if (fileStat.st_size == 0)
      exit(0);

    curSize = fileStat.st_size;
    fileWords = malloc(curSize);

    char curChar[2];
    int stat = read(0, curChar, 1);
    while (stat != 0) {
      fstat(0, &fileStat);
      if (fileStat.st_size >= curSize) {
	curSize = fileStat.st_size;
	fileWords = realloc(fileWords, curSize);
      }

      if (curChar[0] == '\377')
	break;

      fileWords[curPos] = curChar[0];

      curPos++;

      stat = read(0, curChar, 1);
    }

    if (fileWords[curPos - 1] != ' ' && curPos != 0) {
      fileWords = realloc(fileWords, curSize + 1);
      fileWords[curPos] = ' ';
    }

    words = malloc(currentCols * sizeof(char*));

    for (int i = 0; i <= curPos; i++) {
      if (numWords == currentCols) {
	words = realloc(words, (currentCols + 1) * sizeof(char*));
	currentCols += 1;
      }

      if (fileWords[i] == ' ') {
	words[currentWord] = realloc(words[currentWord], currentLetter + 1);
	words[currentWord][currentLetter] = ' ';
	currentLetter = 0;
	currentWord++;
	numWords++;
	continue;
      } else if (currentLetter == 0) {
	words[currentWord] = malloc(sizeof(char));
	words[currentWord][currentLetter] = fileWords[i];
      } else {
	words[currentWord] = realloc(words[currentWord], currentLetter + 1);
	words[currentWord][currentLetter] = fileWords[i];
      }

      currentLetter++;
    }

    qsort(words, numWords - 1, sizeof(char*), frobcmp);

    char writeBuf[2];
    for (int r = 0; r < numWords; r++) {
      for (int c = 0; words[r][c] != '\0'; c++) {
	writeBuf[0] = words[r][c];
	write(1, writeBuf, 1);
      }
    }

    for (int i = 0; i < numWords; i++) {
      free(words[i]);
    }
    free(words);

    fprintf(stderr, "Comparisons: %d\n", comparisons);
    exit(1);
  } else {

    words = malloc(currentCols * sizeof(char*));

    char curChar[2];
    int stat = 1;
    while (stat != 0) {
      stat = read(0, curChar, 1);
      if (numWords == currentCols) {
	words = realloc(words, (currentCols + 100) * sizeof(char*));
	currentCols += 100;
      }

      if (stat == 0)
	break;


      if (curChar[0] == '\377')
	break;

      if (curChar[0] == ' ') {
	words[currentWord] = realloc(words[currentWord], currentLetter + 1);
	words[currentWord][currentLetter] = ' ';
	currentLetter = 0;
	currentWord++;
	numWords++;
	continue;
      } else if (currentLetter == 0) {
	words[currentWord] = malloc(sizeof(char));
	words[currentWord][currentLetter] = curChar[0];
      } else {
	words[currentWord] = realloc(words[currentWord], currentLetter + 1);
	words[currentWord][currentLetter] = curChar[0];
      }

      currentLetter++;
    }

    if (currentLetter != 0 && words[currentWord - 1][currentLetter - 1] != 0) {
      words[currentWord] = realloc(words[currentWord], currentLetter);
      words[currentWord][currentLetter] = ' ';
      numWords++;
    }

    qsort(words, numWords, sizeof(char*), frobcmp);

    char writebuf[2];
    for (int r = 0; r < numWords; r++) {
      for (int c = 0; words[r][c] != '\0'; c++) {
	writebuf[0] = words[r][c];
	write(1, writebuf, 1);
      }
    }

    for (int i = 0; i < numWords; i++) {
      free(words[i]);
    }
    free(words);

    fprintf(stderr, "Comparisons: %d\n", comparisons);
  }

}


  
