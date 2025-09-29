#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
int rank, size;
const int ROOT = 0;
int send_data[100]; // to hold initial data at root
int recv_data;
int result_data;
MPI_Init(&argc, &argv);
// Initialize MPI
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
MPI_Comm_size(MPI_COMM_WORLD, &size);
// Get total number of processes
if (rank == ROOT) {
// Initialize data only at root
printf("Root process initializing data:\n");
for (int i = 0; i < size; i++) {
send_data[i] = i + 1; // Fill with sample data
printf("%d ", send_data[i]);
}
printf("\n");
}
// Scatter: send one element of send_data to each process
MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, ROOT,
MPI_COMM_WORLD);
// Each process works on its part (e.g., multiply by 10)
result_data = recv_data * 10;
printf("Process %d received %d, computed %d\n", rank, recv_data, result_data);
// Gather: collect result_data from all processes to root
int gathered_data[100]; // only root needs to allocate this
MPI_Gather(&result_data, 1, MPI_INT, gathered_data, 1, MPI_INT, ROOT,
MPI_COMM_WORLD);
if (rank == ROOT) {
printf("Root process gathered results:\n");
for (int i = 0; i < size; i++) {
printf("%d ", gathered_data[i]);
}
printf("\n");
}
MPI_Finalize(); // Finalize MPI
return 0;
}