#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void main(int argc, char* argv[]){

	//char* temp[] = {"./b.out", "11","12","2","4", NULL};
	
	for(int i=0; i<=4; i++){
		for(int j=0; j<=4; j++){
			if( atoi(argv[j])>atoi(argv[j+1]) ){
				char* t;
				t = argv[j];
				argv[j] = argv[j+1];
				argv[j+1] = t;
			}
		}
	}
	
	int status;
	pid_t pid;
	pid = fork();
	
	if(pid==0){
		printf("\n");
		printf("\nParent ID : %d",getppid());
		printf("\nThis is a Child Process, ID :%d\n", getpid());
		
		
		execv(argv[1], argv);
		printf("\nExit from Child\n");
		
	
	}else{
		wait(&status);
		
		printf("\n");
		printf("\nThis is a Parent Process, ID :%d ", getpid());
		printf("\nChild ID : %d\n",pid);
		
		for(int i=2; i<argc; i++){
			printf("%d ",atoi(argv[i]));
	        }			
	}

}
 /* Inside b.c :
 
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[]){
	printf("Inside b.c \n");
	for(int i=argc-1; i>1; i--){
		printf("%d ",atoi(argv[i]));
	}

}

*/
