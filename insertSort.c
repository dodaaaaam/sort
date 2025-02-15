assignment_04-1-(1)_C
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 48406

typedef struct arr{
  char *word;
  char *mean;
}arr;

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


void insertion_sort(arr* wordArr, int size) {
  int i, j;     // i = 정렬 안 된 부분 시작 인덱스 & 정렬 된 부분에 넣을 원소 인덱스 
  arr key;
  for(i = 1; i < size ; i++){
    wordArr[i].word[0] = tolower(wordArr[i].word[0]);
    key = wordArr[i];
    for(j = i-1; (j >= 0) && (strcmp(key.word, wordArr[j].word) < 0); j--){
        wordArr[j+1] = wordArr[j]; // 레코드의 오른쪽 이동
    }
    wordArr[j+1] = key; // 추가된 데이터를 정렬된 구간의 위치에 넣음
  }
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

  insertion_sort(wordArr, MAX);

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