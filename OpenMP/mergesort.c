#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void merge(int b[],int c[],int a[],int p,int q)
{
          int i=0,j=0,k=0,x;

          while((i<p)&&(j<q))
         {
                 if(b[i]<=c[j])
                        a[k++]=b[i++];
                 else
                        a[k++]=c[j++];
         }


         if(i==p)
        {
                 #pragma omp parallel for
                                    for(x=j;x<q;x++)
                       a[k++]=c[x];
        }
        else
       {
                #pragma omp parallel for
                           for(x=i;x<p;x++)
                       a[k++]=b[x];
       }
}

void mergesort1(int a[],int n)
{
           int b[1000],c[1000],i,j=0;
           if(n>1)
          {
                   for(i=0;i<n/2;i++)
                         b[i]=a[i];
                  for(i=n/2;i<n;i++)
                  {
                    c[j]=a[i];
                     j++;
                  }

              #pragma omp parallel
              mergesort1(b,n/2);

              #pragma omp parallel
              mergesort1(c,j);

              #pragma omp parallel
              merge(b,c,a,n/2,j);
        }
}

void main()
{
	int i,a[1000],num;
    double  start_time,end_time;
    char f_name[10];
	int n=10;
    printf("\nDone by Ritika Kayal, 18BCE2518\n\n");
    for(i=0;i<n;i++)
    {
		a[i]=rand()%100;
    }

    printf("\nUnsorted array:");
    for(i=0;i<n;i++)
    printf("\t%d",a[i]);
    omp_set_num_threads(5);
    start_time=omp_get_wtime();
    mergesort1(a,n);
    end_time=omp_get_wtime();
	printf("\nSorted array:");
    for(i=0;i<n;i++)
    printf("\t%d",a[i]);
    printf("\nTime taken=%f\n",end_time-start_time);
    printf("\n");
}


