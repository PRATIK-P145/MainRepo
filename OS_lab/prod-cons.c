#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

sem_t e, f, s;
int data[SIZE], in = 0, out = 0;

void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&e);
        sem_wait(&s);

        data[in] = rand() % 100;
        printf("Producer produced %d\n", data[in]);
        in = (in + 1) % SIZE;

        sem_post(&s);
        sem_post(&f);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 20; i++) { // total items expected
        sem_wait(&f);
        sem_wait(&s);

        int val = data[out];
        printf("Consumer consumed %d\n", val);
        out = (out + 1) % SIZE;

        sem_post(&s);
        sem_post(&e);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t c, p[4];

    sem_init(&e, 0, SIZE);
    sem_init(&f, 0, 0);
    sem_init(&s, 0, 1);

    pthread_create(&c, NULL, consumer, NULL);
    for (int i = 0; i < 4; i++)
        pthread_create(&p[i], NULL, producer, NULL);

    for (int i = 0; i < 4; i++)
        pthread_join(p[i], NULL);
    pthread_join(c, NULL);

    sem_destroy(&e);
    sem_destroy(&f);
    sem_destroy(&s);
    return 0;
}
