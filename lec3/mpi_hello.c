#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int number_of_processes;
    int my_rank;
    int mpi_error_code;

    mpi_error_code = MPI_Init(&argc, &argv);
    mpi_error_code = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    mpi_error_code = MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
    printf("%d of %d: Hello, world!\n", my_rank,number_of_processes);
    mpi_error_code = MPI_Finalize();
}