#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int rdcnt = 0;
sem_t r, w;

/* Writer function */
void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&w);
    printf("Writer %d is writing...\n", id);
    sleep(1);

    sem_post(&w);
    return NULL;
}

/* Reader function */
void *reader(void *arg)
{
    int id = *(int *)arg;

    /* Entry section */
    sem_wait(&r);
    rdcnt++;

    if (rdcnt == 1)
        sem_wait(&w);      // First reader blocks writers

    sem_post(&r);



    /* Reading section */
    printf("Reader %d is reading...\n", id);
    sleep(1);

    /* Exit section */
    sem_wait(&r);
    rdcnt--;

    if (rdcnt == 0)
        sem_post(&w);      // Last reader allows writers

    sem_post(&r);
    return NULL;
}

int main()
{
    pthread_t readers[5], writers[5];
    int rid[5], wid[5];

    /* Initialize semaphores */
    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);

    /* Create readers */
    for (int i = 0; i < 5; i++)
    {
        rid[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &rid[i]);
    }

    /* Create writers */
    for (int i = 0; i < 5; i++)
    {
        wid[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &wid[i]);
    }

    /* Wait for readers */
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);


    /* Wait for writers */
    for (int i = 0; i < 5; i++)
        pthread_join(writers[i], NULL);

    /* Destroy semaphores */
    sem_destroy(&r);
    sem_destroy(&w);

    return 0;
}

