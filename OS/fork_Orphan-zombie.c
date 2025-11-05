#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdbool.h>
#include<stdlib.h>

int main(){

    pid_t pid;
    pid = fork();

    if(pid==0){ //child process
        printf("\n[child] Child Process startd\n");
        printf("[child] PID: %d \t Parent ID: %d \n",getpid(), getppid());

        printf("[child] Child process Doing some work\n");
        //sleep(2);
        printf("[c] Finished execution\n");
        exit(0);
    }
    else if(pid>0){ // parent process
        int status;

        sleep(5);
        printf("\n[parent] Parent Process startd\n");
        printf("\n[parent] PID: %d \t Child ID: %d \n",getpid(), pid);
        
        printf("\n[parent] Parent process checking process table :\n");
        system("ps -o pid,ppid,state,cmd");

        wait(&status);
        printf("\n[parent] Parent process checking process table AGAIN :\n");
        system("ps -o pid,ppid,state,cmd");
       
    }

    return 0;

}
