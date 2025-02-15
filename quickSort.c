assignment_04-1-(2)_C
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 48406
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct arr{
  char *word;
  char *mean;
}arr;

void quick_sort(arr* wordArr, int left, int right);
int partition(arr* wordArr, int left, int right);

void print_Arr(arr* wordArr, int count){
  for(int i=0; i<count; i++){
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

void quick_sort(arr* wordArr, int left, int right)
{
  if (left < right) {
    int q = partition(wordArr, left, right);
    quick_sort(wordArr, left, q - 1);
    quick_sort(wordArr, q + 1, right);
  }
}
int partition(arr* wordArr, int left, int right)
{
  arr pivot, temp;
  int low, high;
  
  low = left;
  high = right + 1;
  pivot = wordArr[left];
  
  do {
    do
      low++;
    while (low <= right && (strcmp(wordArr[low].word, pivot.word) < 0));
    do
      high--;
    while (high >= left && (strcmp(wordArr[high].word, pivot.word) > 0));
    if (low < high) SWAP(wordArr[low], wordArr[high], temp);
  } while (low < high);
  SWAP(wordArr[left], wordArr[high], temp);
  return high;
}

int main() {
  FILE *file = fopen("randdict_utf8.TXT", "r");
  if (file == NULL) {
    perror("No file");
    return 1;
  }

  arr* wordArr = (arr*)malloc(sizeof(arr) * 50000);
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
  
  quick_sort(wordArr, 0, count - 1);

  clock_t end_time = clock();

  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("sorted array :\n");
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