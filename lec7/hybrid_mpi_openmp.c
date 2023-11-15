#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int numprocs, rank, iam = 0, np = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); // get number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get process id

    #pragma omp parallel default(shared) private(iam)
    {
        np = omp_get_num_threads(); // get number of threads
        iam = omp_get_thread_num(); // get thread id
        printf("Hello from thread %d/%d from process %d/%d.\n", iam, np, rank, numprocs);
    }

    MPI_Finalize();
    return 0;
}
