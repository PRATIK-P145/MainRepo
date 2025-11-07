// user2.c : Reads data from user1, counts lines/words/chars, and sends filename back

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    char buffer[100];
    int d1, d2, i = 0;
    int cc = 0, wc = 0, ln = 0;

    // Create FIFOs (ignore if they already exist)
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST)
        perror("mkfifo fifo1");
    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST)
        perror("mkfifo fifo2");

    // --- Read data from user1 ---
    d1 = open(fifo1, O_RDONLY);
    if (d1 < 0) { perror("open fifo1"); exit(1); }

    int n = read(d1, buffer, sizeof(buffer) - 1);
    close(d1);
    if (n <= 0) { perror("read"); exit(1); }
    buffer[n] = '\0';

    // --- Count lines, words, characters ---
    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\t')
            wc++;
        else if (buffer[i] == '\n') {
            ln++;
            wc++;
        } else
            cc++;
    }
    if (i > 0) wc++; // count last word

    // --- Write results to a file ---
    const char *filename = "Prat.txt";
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) { perror("fopen"); exit(1); }

    fprintf(fp, "Line count = %d\n", ln);
    fprintf(fp, "Word count = %d\n", wc);
    fprintf(fp, "Character count = %d\n", cc);
    fclose(fp);

    // --- Send filename back to user1 ---
    d2 = open(fifo2, O_WRONLY);
    if (d2 < 0) { perror("open fifo2"); exit(1); }
    write(d2, filename, strlen(filename) + 1);
    close(d2);

    return 0;
}
