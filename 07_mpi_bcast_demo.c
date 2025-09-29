#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
int rank, size;
int data;
MPI_Init(&argc, &argv);
// Initialize MPI environment
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
MPI_Comm_size(MPI_COMM_WORLD, &size);
// Get total number of processes
if (rank == 0) {
data = 2025; // Root process sets the value to broadcast
printf("Process %d broadcasting value %d\n", rank, data);
}
// Broadcast the value of 'data' from process 0 to all other processes
MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
// All processes print the received value
printf("Process %d received value %d\n", rank, data);
MPI_Finalize(); // Finalize the MPI environment
return 0;
}