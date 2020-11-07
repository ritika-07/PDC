#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<assert.h>

float find_sum(int* array) {
float sum = 0.f;
int i;
for (i= 0; i<4; i++)
{
sum+= array[i];
}
return sum;
}

int main (int argc, char** argv)
{
    int data[4];
    int *buf=NULL;
    float val=0;
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (world_rank==0)
    {
        printf("\nName: Ritika Kayal\nRegistration number:18BCE2518\n");
        int arr[16]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        buf=arr;
        printf("\nData before scatter process %d: ", world_rank);
        for (int i=0; i<16; i++)
        {
         printf("%d ", buf[i]);
        }
        printf("\n");

 }
    MPI_Scatter (buf, 4, MPI_INT, &data, 4, MPI_INT, 0,MPI_COMM_WORLD);
    switch (world_rank){
        case 0:
        printf("\nData after scatter in process %d: ",world_rank);
        for (int i=0;i<4; i++){
        printf("%d ", data[i]); }
        val= find_sum(data);
        printf("\nSum of data in process %d: %0.2f", world_rank,val);
        printf("\n");
        break;
    case 1:
        printf("\nData after scatter in process %d: ",world_rank);
        for (int i=0; i<4; i++){
        printf("%d ", data[i]); }
        val= find_sum(data);
        printf("\nSum of data in process %d: %0.2f", world_rank,val); printf("\n");
        break;
    case 2:
        printf("\nData after scatter in process %d: ",world_rank);
        for (int i=0; i<4; i++){
        printf("%d ", data[i]); }
        val= find_sum(data);
        printf("\nSum of data in process %d: %0.2f", world_rank,val); printf("\n");
        break;
    case 3:
        printf("\nData after scatter in process %d: ",world_rank);
        for (int i=0; i<4; i++){
        printf("%d ", data[i]); }
        val= find_sum(data);
        printf("\nSum of data in process %d: %0.2f", world_rank,val); printf("\n");
break; }
    float final_sums[4];
    MPI_Gather(&val, 1, MPI_FLOAT, &final_sums, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);
    float final_val;
    int flag=0;
    float key= final_sums[0];
    if (world_rank==0){
    for (int i= 0; i<4; i++)
    {
    if (key!=final_sums[i])
    {
flag=1;
break; }
    }
    if (flag==1)
    {
        printf("\nSums are NOT EQUAL\n\n");
    }
    else {
        printf("\nSums are EQUAL\n\n");
    }
    }
    MPI_Finalize();
return 0; }
