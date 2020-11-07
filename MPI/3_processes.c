#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h> 
#include <string.h>
int main(int argc, char* argv[]) {
MPI_Init(&argc, &argv);
enum role_ranks { P0, P1, P2 };
int my_rank; 
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
switch(my_rank)
{
case P0: {
printf("\nName: Ritika Kayal\nRegistration number: 18BCE2518\n\n"); 
char msg[] = "001";
printf("MPI process %d sends value %s to process %d.\n", my_rank, msg, my_rank+1);
MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); char msg1[10];
MPI_Recv(&msg1, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
strcpy(msg,msg1);
printf("MPI process %d received %s value from process: %d.\n", my_rank, msg, my_rank); 
break;
}
case P1: {
char msg[10];
MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("MPI process %d received %s value from process: %d.\n", my_rank, msg, my_rank);
strcpy(msg,"010");
printf("MPI process %d sends value %s to process %d.\n", my_rank, msg, my_rank+1);
MPI_Send(&msg, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
break; 
}
case P2: {
char msg[10];
MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("MPI process %d received value %s from process: %d.\n", my_rank, msg, my_rank);
strcpy(msg,"011");
printf("MPI process %d sends value %s to process %d.\n", my_rank, msg, my_rank+1);
MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
break;
} }
MPI_Finalize();
return EXIT_SUCCESS; 
}
