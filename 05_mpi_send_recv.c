#include <stdio.h>
#include <mpi.h>

int main(int arge, char** argv) {
  int rank, size;
  int message;
  MPI_Init(&arge, &argv); //Initialize the MPI environment
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
  MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes
  if(size < 2) {
    if(rank == 0)
      printf("This program requries at least 2 processes. \n");
    MPI_Finalize();
    return 1;
  }
  if(rank == 0) {
    // Sender process
    message = 42;
    printf("Process 0 sending message: %d to process 1 \n", message);
    MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    // Receiver process
    MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received message: %d from process 0 \n", message);
  }
  MPI_Finalize(); //Finalize the MPI environment
  return 0;
}
