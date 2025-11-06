#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(){
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    char buffer[100], buffer2[100];
    int d1,d2, i=0;
    char ch;

    if(mkfifo(fifo1,0666)==-1 && errno!=EEXIST)
        printf("Error");
    if(mkfifo(fifo2,0666)==-1 && errno!=EEXIST)
        printf("Error");

        printf("Enter Input data :");
        while((ch=getchar())!='#'){
            buffer[i++] = ch;
            if(i>=sizeof(buffer)-1)
                break;
        }
        buffer[i] = '\0';

        d1 = open(fifo1, O_WRONLY);
        if(d1<0){}
        write(d1, buffer, strlen(buffer)+1);
        close(d1);




        d2 = open(fifo2, O_RDONLY);
        read(d2, buffer2, sizeof(buffer2));
        close(d2);

        printf("User2 created file : %s", buffer2);



        FILE *fptr = fopen(buffer2, "r");




    printf("Contents of file :");
    int c;
        while((ch = fgetc(fptr) != EOF)){
            putchar(ch);
        }
        fclose(fptr);

    return 0;
}
