#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void main() {
       printf("\nName: Ritika Kayal\nRegistration Number:18BCE2518\n\n");
        int A[3][3],p,q, answer=0;
        printf("Enter elements:\n");
            for(p=0;p<3;p++)
                {
                    for(q=0;q<3;q++)
                    {
                    scanf("%d",&A[p][q]);
                    }
                }
            printf("\nInputted matrix :\n");
            for(p=0;p<3;p++)
            {
            for(q=0;q<3 ;q++)
                printf("%d ",A[p][q]);
                printf("\n");
            }
        double ts= omp_get_wtime();
        #pragma omp parallel for reduction (+:answer)
        for(p=0;p<3;p++)
        answer = (A[0][p]*(A[1][(p+1)%3]*A[2][(p+2)%3] - A[1][(p+2)%3]*A[2][(p+1)%3]));

        double te= omp_get_wtime();
        printf("\nDeterminant: %d\n",answer);
        printf("\nTime taken: %f\n\n",te-ts);
        }
