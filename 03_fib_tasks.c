/*
 * Write a OpenMP program to calculate
 * n Fibonacci numbers using tasks.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// Task-based recursive Fibonacci
int fib(int n) {
  int x, y;
  if (n < 2)
    return n;
  #pragma omp task shared(x)
  x = fib(n - 1);
  #pragma omp task shared(y)
  y = fib(n - 2);
  #pragma omp taskwait
  return x + y;
}
int main() {
  int n;
  printf("Enter number of Fibonacci number to compute: ");
  scanf("%d",&n);
  if(n <= 0) {
    printf("Please enter a positive integer. \n");
    return 1;
  }
  printf("\nFibonacci Series (using OpenMP tasks):\n");
  double start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      for (int i = 0; i < n; i++) {
        int result;
        #pragma omp task shared(result)
        {
          result = fib(i);
          #pragma omp critical
          printf("Fibonacci[%d] = %d\n", i, result);
        }
        #pragma omp taskwait
      }
    }
  }
  double end_time = omp_get_wtime();
  printf("\nExecution Time: %.6f seconds\n", end_time - start_time);
  return 0;
}
