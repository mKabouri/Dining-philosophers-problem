#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NB_PHILOSOPHERS 8

void think(int id) {
	printf( "%2d: Je reflechi\n", id );
	usleep( random() % 2000 );
	printf( "%2d: J'ai faim\n", id );
}

void eat(int id) {
	printf( "%2d: Je mange\n", id );
	usleep( random() % 2000 );
	printf( "%2d: Je suis repu\n", id );
}

int main() {
  // We have to create 8 threads. (A thread for every philosopher).
  pthread_t phils[NB_PHILOSOPHERS];

  for (int i = 0; i < NB_PHILOSOPHERS; i++) {
	pthread_create(&phils[i], NULL,
				   void *(*start_routine) (void *), NULL);
  }
  
  return 0;
}
