#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

#define LEFT(i)   (i*2)
#define RIGHT(i)  (i*2+1)
#define PARENT(i) (i/2)


void insertSort(int *data, int start, int end)
{
  if(start == end)
    return;

  int i, j;
  for(j = start + 1; j <= end; j++){
    int temp = data[j];
    i = j - 1;
    while(data[i] > temp){
      data[i + 1] = data[i];
      i--;
    }
    data[i + 1] = temp;
  }
}

static int partitial(int *data, int start, int end)
{
  int x = data[start];
  int i = start;
  int j, temp;
  for(j = start + 1; j <= end; j++){
    if(x > data[j]){
      i++;
      temp = data[i];
      data[i] = data[j];
      data[j] = temp;
    }
  }
  data[start] = data[i];
  data[i] = x;
  return i;
}

void quickSort(int *data, int start, int end)
{
  if(start >= end)
    return;

  int pivot = partitial(data, start, end);

  quickSort(data, start, pivot - 1);
  quickSort(data, pivot + 1, end);
}

void mergeSort(int *data, int start, int end)
{
  if(start == end)
    return;

  int midpoint = (start + end) / 2;

  mergeSort(data, start, midpoint);
  mergeSort(data, midpoint + 1, end);

  int* sorted_list1 = (int*)malloc(sizeof(int) * (midpoint - start + 2));
  int* sorted_list2 = (int*)malloc(sizeof(int) * (end - midpoint + 1));

  int i, j;
  for(i = start, j = 0; i <= midpoint; i++, j++){
    sorted_list1[j] = data[i];
  }
  sorted_list1[j] = 1000000;

  for(i = midpoint + 1, j = 0; i <= end; i++, j++) {
    sorted_list2[j] = data[i];
  }
  sorted_list2[j] = 10000000;

  int index;
  for(index = start, i = 0, j = 0; index <= end; index++){
    if(sorted_list1[i] > sorted_list2[j]){
      data[index] = sorted_list2[j];
      j++;
    } else {
      data[index] = sorted_list1[i];
      i++;
    }
  }
}

static void max_heapify(int* data, int index, int base, int heap_size)
{
  int next_index = index;

  int i = LEFT(index);
  int j = RIGHT(index);

  if(i <= heap_size){
    if(data[i + base] > data[index + base]){
      next_index = i;
    }
  }

  if(j <= heap_size){
    if(data[j + base] > data[next_index + base]){
      next_index = j;
    }
  }

  if(next_index != index){
    int temp = data[index + base];
    data[index + base] = data[next_index + base];
    data[next_index + base] = temp;
    max_heapify(data, next_index, base, heap_size);
  }
}

void heapSort(int* data, int start, int end)
{
  if(start >= end)
    return;

  int base = start - 1;

  int midpoint = (end - base) / 2;


  int index;
  for(index = midpoint; index >= 1; index--){
    max_heapify(data, index, base, end - base);
  }

  for(index = end - base; index > 1; index--){
    int temp = data[index + base];
    data[index + base] = data[1 + base];
    data[1 + base] = temp;
    max_heapify(data, 1, base, index - 1);
  }
}
