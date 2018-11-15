/*

		Author: Michelle Tagarino ID# 5029967
		Header File for Assignment #3 (Readers/Writers Solution)

*/

#include "readerwriter"

int main()
{
	srand(time(NULL));

	sem_init(&x, 0, 1);
	sem_init(&wsem, 0, 1);

	pthread_t tid[MAX]; //thread identifier

	int i;
	for (i = 0; i < MAX; i++) {
		if ( i % 2 == 1 ) {
			pthread_create(&tid[i], NULL, reader, (void*)i); //create reader threads
		}
		else {
			pthread_create(&tid[i], NULL, writer, (void*)i); //create writer threads
		}
	}
	for (i = 0; i < MAX; i++) {
		pthread_join(tid[i], NULL);
	}
	sem_destroy(&x);
	sem_destroy(&wsem);

	printf("\n");	 
	return 0;
}
