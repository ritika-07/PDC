#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <time.h> 
#include <math.h> 
#include <omp.h> 
#define N 10
int main (int argc, char *argv[]) 
{ 
	float a[N], b[N], temp;
	int i, j, tid;
	float prod=0.0; 
	for(i=0;i<N;i++)
	{
		a[i]=10.0*(i+1);
		b[i]=10.0*(i+2); 
	}
	printf("\nValues of a and b:\n");
	for (i=0;i<N;i++)
	{
		printf("a[%d]= %.1f\tb[%d]= %.1f\n",i,a[i],i,b[i]);
	}
	#pragma omp parallel shared(a,b,prod,temp) private (tid,i) 
	{
		tid=omp_get_thread_num();
		#pragma omp for private (i) 
		for(i=0;i<N;i++){
		temp+=a[i]*b[i];
		}
		#pragma omp critical 
		{
			prod=temp; 
		}
	}
	printf("\n\nDot product= %f\n",prod);
	return 0; 
}

