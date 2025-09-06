/*
* Program using OpenMP to sort an array 
* on n elements using both sequential and 
* parallel mergesort (using section). Record
* the difference in execution time
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

//Merge function
void merge(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  int* L = (int*)malloc(n1 * sizeof(int));
  int* R = (int*)malloc(n2 * sizeof(int));
  for(int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for(int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];
  int i = 0, j = 0, k = left;
  while(i < n1 && j < n2)
    arr[k++] = (L[i] <= R[j] ? L[i++]:R[j++]);
  while(i < n1)
    arr[k++] = L[i++];
  while(j < n2)
    arr[k++] = R[j++];
  free(L);
  free(R);
}

//Sequential Merge Sort
void mergeSortSequential(int arr[], int left, int right) {
  if(left < right) {
    int mid = (left + right) / 2;
    mergeSortSequential(arr, left, mid);
    mergeSortSequential(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

// Parallel Merge Sort with Sections
void mergeSortParallel(int arr[], int left, int right, int depth) {
  if(left < right) {
    int mid = (left + right) / 2;
    if(depth <= 0) {
      mergeSortSequential(arr, left, mid);
      mergeSortSequential(arr, mid + 1, right);
    } else {
      #pragma omp parallel sections
      {
        #pragma omp section
        mergeSortParallel(arr, left, mid, depth - 1);
        #pragma omp section
        mergeSortParallel(arr, mid + 1, right, depth - 1);
      }
    }
    merge(arr, left, mid, right);
  }
}

//Function to print the array
void printArray(int arr[], int size) {
  for(int i = 0; i < size; i++)
    printf("%d ",arr[i]);
  printf("\n");
}

//Copy array
void copyArray(int* src, int* dest, int n) {
  for(int i = 0; i < n; i++)
    dest[i] = src[i];
}

int main() {
  int n;
  printf("Enter number of elements: ");
  scanf("%d", &n);
  int* arr = (int*)malloc(n*sizeof(int));
  int* arr_seq = (int*)malloc(n*sizeof(int));
  int* arr_par = (int*)malloc(n*sizeof(int));
  // Generate random number
  srand(time(NULL));
  for(int i = 0; i < n; i++)
    arr[i] = rand() % 10000;
  copyArray(arr, arr_seq, n);
  copyArray(arr, arr_par, n);
  double start, end;
  //Sequential mergesort
  start = omp_get_wtime();
  mergeSortSequential(arr_seq, 0, n-1);
  end = omp_get_wtime();
  double time_seq = end - start;
  //Parallel mergesort
  start = omp_get_wtime();
  mergeSortParallel(arr_par, 0, n-1, 4); //depth = 4 can be adjusted
  end = omp_get_wtime();
  double time_par = end - start;
  //Output Results
  printf("\nFirst 10 elements of sorted array (sequential): \n");
  printArray(arr_seq, n < 10 ? n : 10);
  printf("\nFirst 10 elements of sorted array (parallel): \n");
  printArray(arr_par, n < 10 ? n : 10);
  printf("\nExecution Time: \n");
  printf("Sequential Merge Sort: %.6f seconds \n", time_seq);
  printf("Parallel Merge Sort: %.6f seconds \n", time_par);
  printf("Speedup: %2.fx\n", time_seq/time_par);
  //Cleanup
  free(arr);
  free(arr_seq);
  free(arr_par);
  return 0;
}
