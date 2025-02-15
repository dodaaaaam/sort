assignment_04-1-(3)_C
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 48406
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct arr {
  char *word;
  char *mean;
} arr;

void print_Arr(arr *wordArr, int count) {
  for (int i = 0; i < count; i++) {
    printf("%s : %s\n", wordArr[i].word, wordArr[i].mean);
  }
}

char *trim(char *str) {
  char *end;

  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  *(end + 1) = 0;

  return str;
}

void adjust(arr *wordArr, int root, int n) {
  int child;
  arr rootkey = wordArr[root];
  int rootIndex = root;

  child = 2 * root + 1; 
  while (child < n) {
    if (child + 1 < n && strcmp(wordArr[child].word, wordArr[child + 1].word) < 0) {
      child++;
    }
    if (strcmp(rootkey.word, wordArr[child].word) >= 0) {
      break;
    }
    wordArr[rootIndex] = wordArr[child];
    rootIndex = child;
    child = 2 * rootIndex + 1;
  }
  wordArr[rootIndex] = rootkey;
}

void heap_sort(arr *wordArr, int n) {
  int i;
  arr temp;

  for (i = n / 2 - 1; i >= 0; i--) {
    adjust(wordArr, i, n);
  }

  for (i = n - 1; i > 0; i--) {
    SWAP(wordArr[0], wordArr[i], temp);
    adjust(wordArr, 0, i);
  }
}

int main() {
  FILE *file = fopen("randdict_utf8.TXT", "r");
  if (file == NULL) {
    perror("No file");
    return 1;
  }

  arr *wordArr = (arr *)malloc(sizeof(arr) * 50000);
  int count = 0;

  char buffer[100];
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';

    char *token = strtok(buffer, ":");
    if (token != NULL) {
      arr bufArr;
      bufArr.word = strdup(trim(token));
      token = strtok(NULL, ":");
      if (token != NULL) {
        bufArr.mean = strdup(trim(token));
      } else {
        bufArr.mean = strdup("");
      }
      wordArr[count++] = bufArr;
    }
  }

  clock_t start_time = clock();

  heap_sort(wordArr, count);

  clock_t end_time = clock();

  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("Sorted array:\n");
  print_Arr(wordArr, count);

  printf("Execution time: %f seconds\n", elapsed_time);

  for (int i = 0; i < count; i++) {
    free(wordArr[i].word);
    free(wordArr[i].mean);
  }
  free(wordArr);

  fclose(file);

  return 0;
}
