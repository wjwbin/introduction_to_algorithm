#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

void showData(int* data, int length)
{
  int i;

  for(i = 0; i < length; i++){
    printf("%d\t", data[i]);
    if(i % 5 == 4)
      printf("\n");
  }
  printf("\n\n");
}

typedef void (*sort_func_type)(int* data, int start, int end);

int main(void)
{

  sort_func_type sort_func[4] = {insertSort, quickSort, mergeSort, heapSort};
  int data [20];
  unsigned int seed;
  int i, j;

  for(i = 0; i < 4; i++){
    seed = (unsigned int)time(NULL) + rand() % 3000;
    srand(seed);
    for(j = 0; j < 20; j++)
      data[j] = rand() % 200;

    printf("================Before Sort===============\n");
    showData(data, 20);
    sort_func[i](data, 0, 19);
    printf("================After Sort================\n");
    showData(data, 20);
  }

}
