#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n];
    for (int i = 0; i < n; i++) {
        printf("P%d AT & BT: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
        wt[i] = tat[i] = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int t = 0, done = 0;
    int q[100], front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    // Initially add processes that have arrived at time 0
    for (int i = 0; i < n; i++)
        if (at[i] <= t && !inQueue[i]) {
            q[rear++] = i;
            inQueue[i] = 1;
        }

    while (done < n) {
        if (front == rear) { // CPU idle
            t++;
            for (int i = 0; i < n; i++)
                if (at[i] <= t && !inQueue[i]) {
                    q[rear++] = i;
                    inQueue[i] = 1;
                }
            continue;
        }

        int i = q[front++]; // dequeue
        int run = rt[i] < tq ? rt[i] : tq;
        rt[i] -= run;
        t += run;

        // Check if new processes arrived during execution
        for (int j = 0; j < n; j++)
            if (at[j] <= t && !inQueue[j]) {
                q[rear++] = j;
                inQueue[j] = 1;
            }

        if (rt[i] == 0) {
            done++;
            tat[i] = t - at[i];
            wt[i] = tat[i] - bt[i];
        } else {
            q[rear++] = i; // re-queue if not finished
        }
    }

    float avgT = 0, avgW = 0;
    printf("\nP\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], tat[i], wt[i]);
        avgT += tat[i];
        avgW += wt[i];
    }

    printf("\nAvg TAT = %.2f  Avg WT = %.2f\n", avgT / n, avgW / n);
    return 0;
}
