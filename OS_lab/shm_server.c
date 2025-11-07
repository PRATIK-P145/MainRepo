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
    int shmid = shmget(key, 1024, 0777|IPC_CREAT);

    struct data *d = (struct data *) shmat(shmid, NULL, 0);

    d->flag = 0;
    printf("Enter data:");
    fgets(d->str, sizeof(d->str), stdin);
    d->str[strcspn(d->str,"\n")] = '\0';

    d->flag = 1;

    while(d->flag !=-1){
        printf("\nwaiting...");
        sleep(2);
    }

    system("ipcs -m");
    shmdt(d);
    system("ipcs -m");
    shmctl(shmid, IPC_RMID, NULL);
    system("ipcs -m");

    return 0;

}
