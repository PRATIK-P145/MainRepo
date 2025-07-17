#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

void sort(int arr[], int n, bool flag){ //  1-Asc, 0-Desc.
	int temp;
	for(int j=0; j<n-1; j++){
		for(int i=0; i<n-1; i++){
				if(arr[i] > arr[i+1] == flag){
					temp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = temp;	
				}
		}
	}
}

int main(){
	
	int n;

	printf("Enter no. of elements : ");
	scanf("%d", &n);
	
 	int arr[20];
 	
 	for(int i=0; i<n; i++){
 		printf("-value %d : ",i+1);
 		scanf("%d", &arr[i]);
 	}
 	
/* 	
 	printf("\nArray is:\n");
 	for(int i=0; i<n; i++){
 		printf(" %d ",arr[i]);
 	}
*/

	pid_t pid;
	pid = fork();
	
	if(pid==0){ //child
	  printf("\n");
		printf("\nThis is a Child Process, ID :%d ", getpid());
		printf("\nParent ID : %d",getppid());
		sort(arr,n,0);
		printf("\nSorted Array (Descending) : \n");
	 
	 for(int i=0; i<n; i++){
 		printf(" %d - %d\n",arr[i], getpid());
 	 }
 	 
	}else{ //parent
		int status;
		wait(&status);
		
		printf("\n");
		printf("\nThis is a Parent Process, ID :%d ", getpid());
		printf("\nChild ID : %d",pid);
		
		
		sort(arr,n,1);
		printf("\nSorted Array (Ascending) :\n");
	  for(int i=0; i<n; i++){
 			printf(" %d - %d\n",arr[i], getpid());
 	 	}
 	 	printf("\n");
	}
 	
