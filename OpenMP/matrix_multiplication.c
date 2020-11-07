#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5
int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i,j,k;
    double time1, time2, total;
	time1 = omp_get_wtime ( );
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
	{
            A[i][j] = 2;
            B[i][j] = 3;
	}
    #pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nDone by, Ritika Kayal 18BCE2518\n\n");
    printf("\nMatrix A:\n", total);
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",A[i][j]);
        }
        printf("\n");
    }
    printf("\nMatrix B:\n", total);
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",B[i][j]);
        }
        printf("\n");
    }
	printf("\nAnswer\n", total);
    for (i= 0; i< N; i++)
    {
        for (j= 0; j< N; j++)
        {
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }
    time2 = omp_get_wtime ( );
    total = time2 - time1;
    printf("\nTotal time = %f seconds\n\n", total);
}
