/*

		Author: Michelle Tagarino ID# 5029967
		Assignment #3: Reader/writer solution using pthreads and semaphores in C
		Purpose: Implement the Readers/Writers Solution, where readers have priority.

*/

#include "readerwriter"

/*
	Reader thread will begin control in this function
*/
void *reader(void *arg)
{
	rand_sleep = rand() % 1 + 1;

	while(1) {
		int threadID = (int)arg;
		
		printf("Reader %1d trying to access data\n", threadID);

		sem_wait(&x);
		read_count++;
		
		if (read_count==1) {
			sem_wait(&wsem);
		}
		
		sem_post(&x);

		printf("Reader %1d is reading\n", threadID);
		sleep(rand_sleep);
		printf("Reader %1d is done reading\n", threadID);
		
		sem_wait(&x);
		read_count--;
		
		if (read_count==0) {
			sem_post(&wsem);
		}

		sem_post(&x);

		pthread_exit(0);
	}
}

/*
	Writer thread will begin control in this function
*/
void *writer(void *arg)
{
	rand_sleep = rand() % 1 + 1;

	while(1) {
		int threadID = (int)arg;
		
		printf("Writer %1d is trying to write\n", threadID);

		sem_wait(&wsem);
		
		printf("Writer %1d is writing\n", threadID);
		sleep(rand_sleep);
		printf("Writer %1d is done writing\n", threadID);
		
		sem_post(&wsem);
	
		printf("Writer %1d is wrapping things up\n", threadID);

		pthread_exit(0);
	}
}
