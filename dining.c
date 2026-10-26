#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];

void *philosopher(void *num) {
    int phil = *(int *)num;

    // Think
    printf("Philosopher %d is thinking.\n", phil);
    sleep(1);

    // Pick up left chopstick
    sem_wait(&chopstick[phil]);
    printf("Philosopher %d picked up left chopstick %d.\n", phil, phil);

    // Pick up right chopstick
    sem_wait(&chopstick[(phil + 1) % 5]);
    printf("Philosopher %d picked up right chopstick %d.\n", phil, (phil + 1) % 5);

    // Eat
    printf("Philosopher %d is eating.\n", phil);
    sleep(2);

    // Put down right chopstick
    sem_post(&chopstick[(phil + 1) % 5]);
    printf("Philosopher %d put down right chopstick %d.\n", phil, (phil + 1) % 5);



    // Put down left chopstick
    sem_post(&chopstick[phil]);
    printf("Philosopher %d put down left chopstick %d.\n", phil, phil);

    return NULL;
}

int main() {
    int i, a[5];
    pthread_t tid[5];

    // Initialize semaphores
    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    // Create philosopher threads
    for (i = 0; i < 5; i++) {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
    }

    // Wait for threads to finish
    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);

    // Destroy semaphores
    for (i = 0; i < 5; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}

