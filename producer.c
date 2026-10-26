#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int buff[5]; 
int in = 0, out = 0; 
int val; 
sem_t e, f, s;

void *producer(void *arg)
{
	int data=*(int *)arg;
    sem_wait(&e);
	sem_wait(&s);
		buff[in] = data;
		in = (in + 1) % 5;
		printf("\n Producer has put %d data", data);
	sem_post(&s);
    sem_post(&f);
    return NULL;
}
void *consumer(void *arg)
{
	int data;
	sleep(1);
    do{
    sem_wait(&f);
	sem_wait(&s);
		data = buff[out];
		out = (out + 1) % 5;
	    printf("\n Consumer has put %d data", data);	
	sem_post(&s);
    sem_post(&e);
    sem_getvalue(&e, &val);
    }while (val != 5);
    return NULL;
}
int main()
{
	pthread_t p[8], c;
	int i, a[8] = {11,12,13,14,15,16,17,18};

	sem_init(&e, 0, 5);
	sem_init(&f, 0, 0);
	sem_init(&s, 0, 1);
	
	for (i = 0; i < 8; i++)
		pthread_create(&p[i], NULL, producer, (void *)&a[i]);
	pthread_create(&c, NULL, consumer, NULL);

	for (i = 0; i < 8; i++)
		pthread_join(p[i], NULL);
	pthread_join(c, NULL);
return 0; 
}

