#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s ./b.out num1 num2 num3 ...\n", argv[0]);
        return 1;
    }

    // Sort numeric arguments (indices 2 to argc-1)
    for (int i = 2; i < argc - 1; i++) {
        for (int j = 2; j < argc - i + 1; j++) {
            if (atoi(argv[j]) > atoi(argv[j + 1])) {
                char* temp = argv[j];
                argv[j] = argv[j + 1];
                argv[j + 1] = temp;
            }
        }
    }

    pid_t pid = fork();
    int status;

    if (pid == 0) {
        printf("\nParent ID : %d", getppid());
        printf("\nThis is Child Process, ID : %d\n", getpid());

        // Build argument list for execv
        char* args_for_b[argc - 1];
        args_for_b[0] = argv[1];
        for (int i = 2; i < argc; i++) {
            args_for_b[i - 1] = argv[i];
        }
        args_for_b[argc - 1] = NULL;

        execv(argv[1], args_for_b);
        perror("execv failed");
        exit(1);
    } else {
        wait(&status);
        printf("\nThis is Parent Process, ID : %d", getpid());
        printf("\nChild ID : %d\n", pid);

        printf("Sorted numbers (ascending): ");
        for (int i = 2; i < argc; i++) {
            printf("%d ", atoi(argv[i]));
        }
        printf("\n");
    }

    return 0;
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
