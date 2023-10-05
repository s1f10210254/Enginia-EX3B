#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_product(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 64;
    if (argc == 2) {
        n = atoi(argv[1]);
    }

    // Memory allocation
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Matrix initialization
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
        }
    }

    // Measure time for matrix multiplication
    double start_time = omp_get_wtime();
    matrix_product(A, B, C, n);
    double end_time = omp_get_wtime();
    printf("Time taken for matrix multiplication with n=%d: %lf seconds\n", n, end_time - start_time);

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
