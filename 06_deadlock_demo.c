#include <stdio.h>
#include <mpi.h>
int main(int argc, char** argv) {
int rank, size;
int send_data, recv_data;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (size < 2) {
if (rank == 0)
printf("Need at least 2 processes.\n");
MPI_Finalize();
return 1;
}
send_data = rank;
if (rank == 0) {
printf("Process 0: Sending to 1\n");
MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
printf("Process 0: Receiving from 1\n");
MPI_Recv(&recv_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD,
MPI_STATUS_IGNORE);
} else if (rank == 1) {
printf("Process 1: Sending to 0\n");
MPI_Send(&send_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
printf("Process 1: Receiving from 0\n");
MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
MPI_STATUS_IGNORE);
}
MPI_Finalize();
return 0;
}