#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 4

int main () {
    static long num_steps = 100000000;
    int i;
    double pi, total_sum = 0.0, start_time, run_time;
    double dx = 1.0/(double) num_steps;

    start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        double x;
        int numthreads;
        double local_sum = 0;
        
        #pragma omp for
        for (i=0; i < num_steps; i++) {
            x = (i+0.5) * dx;
            local_sum += 4.0/(1.0+x*x);
        }
        
        #pragma omp critical
        total_sum += local_sum;
    }

    pi = dx * total_sum;
    run_time = omp_get_wtime() - start_time;

    printf("pi is %1.12f in %f seconds %d threads\n", pi, run_time, omp_get_num_threads());
}
