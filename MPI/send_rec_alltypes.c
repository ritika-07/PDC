#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h>
int main(int argc, char* argv[]) 
{
MPI_Init(&argc, &argv);
enum role_ranks { P0, P1 };
int my_rank; 
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

//BUFFERED
double t1=MPI_Wtime();
switch(my_rank)
{
case P0: {
    printf("\nName: Ritika Kayal\nRegistration Number: 18BCE2518\n\n"); 
    int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int); 
    char* buffer_attached = (char*)malloc(buffer_attached_size); 
    MPI_Buffer_attach(buffer_attached, buffer_attached_size);
    int msg = 2518;
    printf("Buffered send: MPI process %d sent value %d.\n\n", my_rank, msg); 
    MPI_Bsend(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
    MPI_Buffer_detach(&buffer_attached, &buffer_attached_size); 
    free(buffer_attached);
    break;
}
case P1: {
int msg; MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("Buffered receive: MPI process %d receives value: %d.\tTime: %f\n\n", my_rank, msg, MPI_Wtime()-t1); 
break;
} 
}

//IMMEDIATE
t1=MPI_Wtime();
switch(my_rank)
{
case P0: {
int msg = 2518;
MPI_Request request;
printf("Immediate send: MPI process %d sends value %d\n\n", my_rank, msg); 
MPI_Isend(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
MPI_Wait(&request, MPI_STATUS_IGNORE);
break; 
}
case P1: {
int msg;
MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("Immediate receive: MPI process %d received value: %d\tTime: %f\n\n", my_rank, msg, MPI_Wtime()-t1);
break; 
}
}

//STANDARD
t1=MPI_Wtime();
switch(my_rank)
{
case P0: {
     char *message = "Hello, world!";
     printf("Standard send: MPI process %d sends value %s\n\n", my_rank, message);
     MPI_Send(message, 16, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
     break;
  }

case P1: {
     char message[16];
     MPI_Status  status;
     MPI_Recv(message, 16, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
     printf("Standard receive: MPI process %d received value: %s\tTime: %f\n\n", my_rank, message, MPI_Wtime()-t1);
     break;
  }
}

//READY
t1=MPI_Wtime();
 switch(my_rank)
    {
        case P0:
        {
            MPI_Barrier(MPI_COMM_WORLD);
            int buffer_sent = 12345;
            printf("Ready send: MPI process %d sends value %d\n\n", my_rank, buffer_sent);
            MPI_Rsend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            break;
        }
        case P1:
        {
            int received;
            MPI_Request request;
            MPI_Irecv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Barrier(MPI_COMM_WORLD);
 
            // Wait for the underlying MPI_Recv to complete.
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            printf("Ready receive: MPI process %d received value: %d\tTime: %f\n\n", my_rank, received, MPI_Wtime()-t1);
            break;
        }
    }

//SYNCHRONOUS
t1=MPI_Wtime();
switch(my_rank)
    {
        case P0:
        {
            // The "master" MPI process issues the MPI_Ssend.
            int buffer_sent = 12345;
            MPI_Request request;
            printf("Synchronous send: MPI process %d sends value %d.\n\n", my_rank, buffer_sent);
            MPI_Ssend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            break;
        }
        case P1:
        {
            // The "slave" MPI process receives the message.
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Synchronous receive: MPI process %d received value: %d.\tTime: %f\n\n", my_rank, received, MPI_Wtime()-t1);
            break;
        }
    }

//NON BLOCKING
//BUFFERED NONBLOCKING
t1=MPI_Wtime();
switch(my_rank)
    {
        case P0:
        {
            // Declare the buffer and attach it
            int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(int);
            char* buffer_attached = malloc(buffer_attached_size);
            MPI_Buffer_attach(buffer_attached, buffer_attached_size);
 
            // Issue the MPI_Ibsend
            int buffer_sent = 12345;
            MPI_Request request;
            printf("Buffered non-blocking send: MPI process %d sends value %d.\n\n", my_rank, buffer_sent);
            MPI_Ibsend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
            
            // Let's wait for the MPI_Ibsend to complete before progressing further.
            MPI_Wait(&request, MPI_STATUS_IGNORE);
 
            // Detach the buffer. It blocks until all messages stored are sent.
            MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
            free(buffer_attached);
            break;
        }
        case P1:
        {
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Buffered non-blocking receive: MPI process %d received value: %d.\tTime: %f\n\n", my_rank, received, MPI_Wtime()-t1);
            break;
        }
    }

//SYNCHRONOUS NON-BLOCKING
t1=MPI_Wtime();
switch(my_rank)
    {
        case P0:
        {
            int buffer_sent = 12345;
            MPI_Request request;
            printf("Synchronous non-blocking send: MPI process %d sends value %d.\n\n", my_rank, buffer_sent);
            MPI_Issend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
            
            // Do other things while the MPI_Issend completes
            // <...>
 
            // Let's wait for the MPI_Issend to complete before progressing further.
            MPI_Status status;
            MPI_Wait(&request, &status);
            break;
        }
        case P1:
        {
            int received;
            MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Synchronous non-blocking receive: MPI process %d received value: %d.\tTime: %f\n\n", my_rank, received, MPI_Wtime()-t1);
            break;
        }
    }

//READY NONBLOCKING
t1=MPI_Wtime();
switch(my_rank)
    {
        case P0:
        {
            MPI_Barrier(MPI_COMM_WORLD);
 
            int buffer_sent = 12345;
            MPI_Request request;
            printf("Ready non-blocking send: MPI process %d sends value %d.\n\n", my_rank, buffer_sent);
            MPI_Irsend(&buffer_sent, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
 
            // Do something else while the MPI_Irsend progresses
            // <...>
 
            // Wait for the underlying MPI_Rsend to complete.
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            break;
        }
        case P1:
        {
            int received;
            MPI_Request request;
            MPI_Irecv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
 
            // Tell the other process that the receive is posted, so the ready send can be issued
            MPI_Barrier(MPI_COMM_WORLD);
 
            // Wait for the underlying MPI_Recv to complete.
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            printf("Ready non-blocking receive: MPI process %d receives value %d.\tTime: %f\n\n", my_rank, received, MPI_Wtime()-t1);
            break;
        }
    }

MPI_Finalize();
return EXIT_SUCCESS; 
}