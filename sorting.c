#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE (sizeof(list)/sizeof(list[0]))
int list[] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE] = {0};

//Swaps two elements
void swap(int *x, int *y){
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bubbleSort(int arr[], int size){
  bool noSwap = true;
  for(int i = 0; i < size - 1; i++)
  {
    noSwap = true;
    for(int j = 0; j < size - i - 1; j++)
    {
        if(arr[j] > arr[j + 1])
        {
          swap(&arr[j], &arr[j+1]);
          noSwap = false;
        }
    }
    //If no swap took place, the list is sorted and escape the loop.
    if(noSwap == true) break;
  }
}

void mergeArrays(int arr1[], int size1, int arr2[], int size2, int arr3[]){
  int i = 0, j = 0, k = 0;
  while(i<size1 && j<size2){
  if(arr1[i] < arr2[j]){
    arr3[k] = arr1[i];
    k++; i++;
  }
  else{
    arr3[k] = arr2[j];
    k++; j++;
  }
  }
  while(i < size1){
    arr3[k] = arr1[i];
    k++; i++;
  }
  while (j < size2) {
    arr3[k] = arr2[j];
    k++; j++;
  }
}

void printArr(int arr[], int size){
  for(int i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

typedef struct SortingThreadParameters{
  int *subArray;
  unsigned int size;
} SortingThreadParameters;

typedef struct MergingThreadParameters{
  SortingThreadParameters left;
  SortingThreadParameters right;
} MergingThreadParameters;

void *sortThread(void *param){
  bubbleSort( ((struct SortingThreadParameters*)param)->subArray,
              ((struct SortingThreadParameters*)param)->size);
}

void *mergeThread(void *param){
  mergeArrays(
    //Left Array and size
    (((struct MergingThreadParameters*)param)->left).subArray,
    (((struct MergingThreadParameters*)param)->left).size,
    //Right Array and size
    (((struct MergingThreadParameters*)param)->right).subArray,
    (((struct MergingThreadParameters*)param)->right).size,
    result
  );

}

int main(){
  pthread_t thread1;
  pthread_t thread2;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  SortingThreadParameters *paramsLeft = malloc(sizeof(SortingThreadParameters));
  paramsLeft->subArray = list;
  paramsLeft->size = SIZE/2;
  //Create First sorting pthread
  pthread_create(&thread1, &attr, sortThread, (void *)paramsLeft);

  SortingThreadParameters *paramsRight = malloc(sizeof(SortingThreadParameters));
  paramsRight->subArray = list + paramsLeft->size;
  paramsRight->size = SIZE - paramsLeft->size;

  //Create Second sorting pthread
  pthread_create(&thread2, &attr, sortThread, (void *)paramsRight);
  //Wait for threads to complete
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  pthread_t thread3;
  //Create Merging Thread
  MergingThreadParameters *paramsMerge = malloc(sizeof(MergingThreadParameters));
  paramsMerge->left = *paramsLeft;
  paramsMerge->right = *paramsRight;
  pthread_create(&thread3, &attr, mergeThread, (void *)paramsMerge);
  pthread_join(thread3, NULL);
  printArr(result, SIZE);

  return 0;
}
