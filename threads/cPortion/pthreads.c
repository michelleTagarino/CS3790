/*

		Author: Michelle Tagarino ID# 5029967
		Lab Assignment #2: C pthreads
		Purpose: This program reads two integers, M and N, where M < N. It spawns M threads to look for prime 
			 	 numbers within the given range [1...N]. Each thread is assigned an interval range computed by N/M.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n; //used to find primes bewtween 1 and n
int m; //number of threads
int intervalLength; //range of each thread

/* Function Prototypes */
void *runner(void *param); //threads call this function
int isPrime(int); //determines whether number is prime

/*
	The thread will begin control in this function
*/
void *runner(void *param)
{
	int lowerBound; //start of thread range
	int upperBound; //end of thread range
	int threadID;   //current thread

	threadID = (int)param;
	lowerBound = (threadID * intervalLength) + 1;
	upperBound = (threadID + 1) * intervalLength;
	
	int i;
	for (i = lowerBound; i <= upperBound; i++)
	{
		if (isPrime(i) != 0) {
				fprintf(stderr,"\nThread %2d found: %2d", threadID,i);
		}
	}
}
/*
	Returns the number if it is prime, 0 if it is not
*/
int isPrime(int n)
{
	int i;
	if (n < 2) return 0;
	if (n == 2) return n;
	for (i = 2; i < n; i++) {
		if (n % i == 0) return 0;
	}
	return n;
}

int main(int argc, char *argv[])
{
	if (argc != 3) 
	{
		fprintf(stderr, "Usage: <%s> <RANGE (N)> <# of threads (M)> \n",argv[0]);
		return -1;
	}
	
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	
	pthread_t tid[m]; //the thread identifier
	
	intervalLength = n/m;

	int i;
	for (i = 0; i < m; i++)
	{
		pthread_create(&tid[i], NULL, runner,(void*)i); //create the thread
	}

	for (i = 0; i < m; i++)
	{
		pthread_join(tid[i],NULL); //wait for threads to complete
	}
  	printf("\n\n");
	return 0;
}
