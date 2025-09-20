#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//Function to check primality
int is_prime(int num) {
  if (num < 2) return 0;
  int limit = sqrt(num);
  for(int i = 2; i <= limit; i++) {
    if(num % i == 0) return 0;
  }
  return 1;
}
int main() {
  int n, i;
  printf("Enter the value of n: ");
  scanf("%d", &n);
  int *prime_serial = (int *)malloc((n + 1) * sizeof(int));
  int *prime_parallel = (int *)malloc((n + 1) * sizeof(int));
  double start_time, end_time;
  //Serial computation
  start_time = omp_get_wtime();
  for(i = 1;i <= n;i++) {
    prime_serial[i] = is_prime(i);
  }
  end_time = omp_get_wtime();
  double serial_time = end_time - start_time;
  //Parallel computation
  start_time = omp_get_wtime();
  #pragma omp parallel for
  for(i = 1;i <= n; i++) {
    prime_parallel[i] = is_prime(i);
  }
  end_time = omp_get_wtime();
  double parallel_time = end_time - start_time;
  //Output results
  printf("\nPrime numbers from 1 to %d: \n", n);
  for(i = 1; i <= n; i++) {
    if(prime_parallel[i]) {
      printf("%d ", i);
    }
  }
  printf("\n\nExecution Time: \n");
  printf("Serial: %.6f seconds\n", serial_time);
  printf("Parallel: %.6f seconds\n", parallel_time);
  free(prime_serial);
  free(prime_parallel);
  return 0;
}
