#include <stdio.h>
#include <stdbool.h>

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
    arr3[k] = arr2[i];
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

#define SIZE (sizeof(list)/sizeof(list[0]))
int list[] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE] = {0};

int main(){
  printArr(list, SIZE);

  return 0;
}
