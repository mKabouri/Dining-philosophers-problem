// Taken from:
// http://mfaverge.vvv.enseirb-matmeca.fr/pg204/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NB_PHILOSOPHERS 8

pthread_mutex_t chopsticks[NB_PHILOSOPHERS];

void think(int id) {
    printf("%2d: Je réfléchis\n", id);
    usleep(random() % 2000);
    printf("%2d: J'ai faim\n", id);
}

void eat(int id) {
    printf("%2d: Je mange\n", id);
    usleep(random() % 2000);
    printf("%2d: Je suis repu\n", id);
}

void *philosopher(void *arg) {
    int id = *(int*)arg;
    while (1) {
        think(id);
	pthread_mutex_lock(&chopsticks[id]);
        pthread_mutex_lock(&chopsticks[(id + 1) % NB_PHILOSOPHERS]);
        eat(id);
        pthread_mutex_unlock(&chopsticks[(id + 1) % NB_PHILOSOPHERS]);
        pthread_mutex_unlock(&chopsticks[id]);
    }
    return NULL;
}

int main() {
    pthread_t phils[NB_PHILOSOPHERS];
    int ids[NB_PHILOSOPHERS];

    for (int i = 0; i < NB_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }

    for (int i = 0; i < NB_PHILOSOPHERS; i++) {
        pthread_create(&phils[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NB_PHILOSOPHERS; i++) {
        pthread_join(phils[i], NULL);
    }

    return 0;
}
