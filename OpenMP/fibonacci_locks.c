#include <stdio.h>
#include <omp.h>
#include <pthread.h>
pthread_t tid[2]; 
pthread_mutex_t lock;  
long fib(long num) 
{
 if (num < 2) {
 return 1;
 }
 pthread_mutex_lock(&lock); 
 return fib(num - 2) + fib(num - 1);
 pthread_mutex_unlock(&lock);
}

 
int main(int argc, char ** argv) 
{
 long num = 0;
 printf("\nDone By, Ritika Kayal 18BCE2518\n");
 printf("\nFibonacci sequence for 20 numbers:\n\n");
 for (num = 0; num <= 20; num++) {
 printf("%ld ",  fib(num));
  
 }
 printf("\n");
 return 0;
}
