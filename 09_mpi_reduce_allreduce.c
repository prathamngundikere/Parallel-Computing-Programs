#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
int rank, size;
int local_value;
int sum_result, prod_result, max_result, min_result;
int all_sum, all_prod, all_max, all_min;
MPI_Init(&argc, &argv);
// Initialize MPI
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
MPI_Comm_size(MPI_COMM_WORLD, &size);
// Get total number of processes
local_value = rank + 1; // Each process sets a value
printf("Process %d has value %d\n", rank, local_value);
// ---------- MPI_Reduce (result stored at root only) ----------
MPI_Reduce(&local_value, &sum_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
MPI_Reduce(&local_value, &prod_result, 1, MPI_INT, MPI_PROD, 0,
MPI_COMM_WORLD);
MPI_Reduce(&local_value, &max_result, 1, MPI_INT, MPI_MAX, 0,
MPI_COMM_WORLD);
MPI_Reduce(&local_value, &min_result, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
if (rank == 0) {
printf("\n[Using MPI_Reduce to root process]\n");
printf("Sum = %d\n", sum_result);
printf("Product = %d\n", prod_result);
printf("Max = %d\n", max_result);
printf("Min = %d\n", min_result);
}
// ---------- MPI_Allreduce (result stored at all processes) ----------
MPI_Allreduce(&local_value, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
MPI_Allreduce(&local_value, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
MPI_Allreduce(&local_value, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
MPI_Allreduce(&local_value, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
printf("\nProcess %d [Using MPI_Allreduce]: Sum=%d, Product=%d, Max=%d, Min=%d\n",
rank, all_sum, all_prod, all_max, all_min);
MPI_Finalize(); // Finalize MPI
return 0;
}