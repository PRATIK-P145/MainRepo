#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>

struct data{
    char str[100];
    int flag;
};

int main(){
    key_t key = ftok("shm.txt",'P');
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    struct data *d = (struct data *) shmat(shmid, NULL, 0);

    

    while(d->flag!=1){
        printf("waiting...");
        sleep(2);
    }

    printf("\nData read from file is : %s",d->str);

       d->flag = -1;

    system("ipcs -m");
    shmdt(d);

    return 0;

}
