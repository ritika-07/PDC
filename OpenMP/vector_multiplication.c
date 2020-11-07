# include <stdio.h>
# include <stdlib.h> 
# include <omp.h>
# include <time.h>

int main() 
{
	int i,j,tid;
	int n = 3, sum = 0; 
	int arr1[3][3] = {{9,8,7},{6,5,4},{3,2,1}}; 
	int arr2[3] = {1,2,3};
	int ans[3] = {n,n};
	
	double stime = clock();
	omp_set_num_threads (n);
	#pragma omp parallel shared(arr1,arr2,ans,sum) private(tid,j) 
	{
		tid = omp_get_thread_num();
		#pragma omp for
			for (i=0; i<n; i++) 
			{
				printf("For loop i: %d \t For tid: %d \n",i,tid); 
				printf("\n");
				for (j=0; j<n; j++)
				{ 
					ans[i] = ans[i] + (arr1[i][j]*arr2[j]); 
					printf("For loop j: %d \t For tid: %d \n",j,tid); 
					printf("Array 1: %d \t Array2:%d \n", arr1[i][j],arr2[j]);
					printf("Final array, ans[i]: %d \n",ans[i] );
				}
				printf("\n");
				#pragma omp critical 
				{
					sum = sum + ans[i];
					printf("Thread number: %d is at row %d and has ans[%d]=%d\t",tid,i,i,ans[i]); 
					printf("Total= %d\n",sum);
				} 
			}
	}
	double etime = clock(); 
	printf("\nTime taken: %f \n", (etime-stime) / CLOCKS_PER_SEC);
	return 0; 
}


