#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

int count =0;
sem_t r,w;

void *read_func(void *arg){
    int id = (long) arg;
    //sleep(rand() % 3); 
    sem_wait(&r);
    printf("\nReader %d Entered...", id);
    count++;
    if(count==1)
        sem_wait(&w);
    sem_post(&r);

    printf("\n-> Reader %d is Reading...", id);

    sem_wait(&r);
    printf("\nReader %d Exited...", id);
    count--;
    if(count==0)
        sem_post(&w);
    sem_post(&r);
}

void *write_func(void *arg){
    int id = (long) arg;
    //sleep(rand() % 3); 
    sem_wait(&w);

    printf("\nWriter %d is Writing....", id);

    sem_post(&w);
}

int main(){
    pthread_t reader[5], writer[5];
    long i;
    sem_init(&r, 0, 1);
    sem_init(&w, 0, 1);

    for( i=0; i<5; i++){
        pthread_create(&reader[i], NULL, read_func, (void *)i);
    }
    for( i=0; i<5; i++){
        pthread_create(&writer[i], NULL, write_func, (void *)i);
    }

    for( i=0; i<5; i++){
        pthread_join(reader[i], NULL);
    }
    for( i=0; i<5; i++){
        pthread_join(writer[i], NULL);
    }
    

    return 0;
}
