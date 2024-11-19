#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {
	#pragma omp parallel for
	/*
	{
		int nthreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();
		printf("my_dgemv(): Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
		printf("my_dgemv(): For actual timing runs, please comment out these printf() and omp_get_*() statements. \n");
	}
	*/
        for (int row=0; row<n; row++)
        {
                double sum = 0;
                int rowOffset = row*n;

		#pragma omp parallel for reduction (+:sum)
                for (int col=0; col<n; col++)
                {
                        sum += A[rowOffset+col] * x[col];
                }

                y[row] += sum;
        }
}

