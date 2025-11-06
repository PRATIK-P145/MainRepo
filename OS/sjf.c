#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n], at[n], bt[n], rt[n], wt[n], tat[n];
    float avgwt = 0, avgtat = 0;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("\nProcess %d\n", p[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int t = 0, completed = 0, min = -1, prev = -1;
    printf("\nGantt Chart:\n");

    while (completed != n) {
        min = -1;
        int shortest = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= t && rt[i] > 0 && rt[i] < shortest) {
                shortest = rt[i];
                min = i;
            }
        }

        if (min == -1) {
            t++;
            continue;
        }

        if (min != prev) {
            printf("P%d ", p[min]);
            prev = min;
        }

        rt[min]--;
        t++;

        if (rt[min] == 0) {
            completed++;
            int finish_time = t;
            tat[min] = finish_time - at[min];
            wt[min] = tat[min] - bt[min];
            avgwt += wt[min];
            avgtat += tat[min];
        }
    }

    printf("\n\nP\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avgtat / n);
    printf("\nAverage Waiting Time = %.2f\n", avgwt / n);
    return 0;
}
