#include <stdio.h>
#include <omp.h>
 
int ackermann(int m, int n)
{
        if (!m) return n + 1;
        if (!n) return ackermann(m - 1, 1);
        return ackermann(m - 1, ackermann(m, n - 1));
}
 
int main()
{
        int m, n;
        #pragma omp parallel for
        for (m = 0; m <= 4; m++) {
            printf("At thread: %d\n", omp_get_thread_num);
            #pragma omp parallel for
                for (n = 0; n < 6 - m; n++){
                        printf("At thread: %d\n", omp_get_thread_num);
                        printf("A(%d, %d) = %d\n", m, n, ackermann(m, n));
                }
        }
 
        return 0;
}