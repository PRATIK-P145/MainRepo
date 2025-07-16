#include <unistd.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	int status;
	int a = 10;
	
	if(pid == 0){
		printf("\nThis a Child Process. ID = %d\n", getpid());
		printf("Parent's ID = %d\n", getppid());
		printf("value of a = %d\n", (a+15));
	}else{
		//sleep(2);  zombie state
		system("\nps");
		wait(&status);
		system("\nps");
		
		printf("\nThis a Parent Process. ID = %d\n", getpid());
		printf("Child's ID = %d\n", pid);
		printf("value of a = %d\n", (a*2));
	}	

 return 0;
}
