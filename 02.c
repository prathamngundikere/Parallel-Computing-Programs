/* 
 * OpenMP program that divides the itertions into 
 * chunks containing 2 iteration respectively...
 * ...
 */

#include <stdio.h>
#include <omp.h>
int main() {
  int n;
  printf("Enter number of iterations: ");
  scanf("%d", &n);
  // Set the schedule to static, chunk size 2
  omp_set_schedule(omp_sched_static, 2);
  // Array to hold thread number for each iteration
  int thread_for_iteration[n];
  //Parallel loop
  #pragma omp parallel for schedule(runtime)
  for(int i = 0; i < n; i++) {
    int tid = omp_get_thread_num();
    thread_for_iteration[i] = tid;
  }
  // Now group and print results by thread
  int max_threads = omp_get_max_threads();
  printf("\nThread-wise Iteration Mapping: \n");
  for(int t = 0; t < max_threads; t++) {
    int first = 1;
    for(int i = 0; i < n; i++) {
      if(thread_for_iteration[i] == t){
        if(first) {
          printf("Thread %d: Iteration %d", t, i);
          first = 0;
        } else if(i > 0 && thread_for_iteration[i - 1] != t){
          printf("-- %d\nThread %d: Iteration %d", i - 1, t, i);
        }
      }
    }
    if (!first)
      printf("-- %d\n",n - 1);
  }
  return 0;
}
