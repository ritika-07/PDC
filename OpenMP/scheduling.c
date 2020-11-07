# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

int prime_guided ( int n )

{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel shared ( n ) private ( i, j, prime )

# pragma omp for reduction ( + : total ) schedule ( guided, 100 )
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}

int prime_static ( int n )

{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel shared ( n ) private ( i, j, prime )

# pragma omp for reduction ( + : total ) schedule ( static, 100 )
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}

int prime_dynamic ( int n )

{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel \
  shared ( n ) \
  private ( i, j, prime )

# pragma omp for reduction ( + : total ) schedule ( dynamic, 100 )
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }

  return total;
}

int main ( int argc, char *argv[] )

{
  int n, factor=2, high=512, low=1, primes;
  double time1, time2, time3;

 printf ("\nDone by Ritika Kayal, 18BCE2518\n\n"); 
 printf ( "\nTo count the primes from 1 to N where lower limit is 1 and higher limit is 512\n" );
  printf ( "  No. of processors = %d\n", omp_get_num_procs ( )  );
  printf ( "  No. of threads = %d\n", omp_get_max_threads ( )  );

  printf ( "\n" );
  printf ( "         N   no. of primes   Guided Time  Static Time  DynamicTime\n" );
  printf ( "\n" );

  n = low;

  while ( n <= high )
  {
    time1 = omp_get_wtime ( );
    primes = prime_guided ( n );
    time1 = omp_get_wtime ( ) - time1;

    time2 = omp_get_wtime ( );
    primes = prime_static ( n );
    time2 = omp_get_wtime ( ) - time2;

    time3 = omp_get_wtime ( );
    primes = prime_dynamic ( n );
    time3 = omp_get_wtime ( ) - time3;

    printf ( "  %8d  %8d  %12f  %12f  %12f\n", n, primes, time1, time2, time3 );

    n = n * factor;
  }
  return 0;
}


