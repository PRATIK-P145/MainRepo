#include <stdio.h>
#include <stdbool.h>

#define N 5 /* number of processes */
#define M 3 /* number of resource types */

/* Global data structures */
int allocation[N][M]; /* Allocation Matrix */
int max[N][M];        /* Max Matrix */
int need[N][M];       /* Need Matrix = Max - Allocation */
int available[M];     /* Available resources */

/* Print the system state in a readable layout */
void printState(void) {
    printf("\nCurrent System State:\n");
    printf("P\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < N; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < M; j++) printf("%d", allocation[i][j]);
        printf("\t\t");
        for (int j = 0; j < M; j++) printf("%d", max[i][j]);
        printf("\t\t");
        for (int j = 0; j < M; j++) printf("%d", need[i][j]);
        printf("\n");
    }
    printf("Available: ");
    for (int j = 0; j < M; j++) printf("%d ", available[j]);
    printf("\n");
}

/* Safety algorithm:
   Returns true if the system is in a safe state; safeSeq[] is filled with an order. */
bool isSafe(int safeSeq[]) {
    int work[M];
    bool finish[N];
    for (int i = 0; i < M; i++) work[i] = available[i];
    for (int i = 0; i < N; i++) finish[i] = false;

    int count = 0;
    while (count < N) {
        bool found = false;
        for (int p = 0; p < N; p++) {
            if (!finish[p]) {
                bool canFinish = true;
                for (int j = 0; j < M; j++) {
                    if (need[p][j] > work[j]) { canFinish = false; break; }
                }
                if (canFinish) {
                    for (int k = 0; k < M; k++) work[k] += allocation[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; /* no process could proceed -> unsafe */
    }
    return true;
}

/* Request algorithm:
   Return true if request can be granted (and is granted), otherwise false. */
bool requestResources(int p, int request[]) {
    /* Validate process index */
    if (p < 0 || p >= N) {
        printf("Invalid process number %d\n", p);
        return false;
    }

    /* Step 0: Non-negative requests */
    for (int j = 0; j < M; j++) {
        if (request[j] < 0) {
            printf("Error: negative request not allowed.\n");
            return false;
        }
    }

    /* Step 1: Check request <= need */
    for (int j = 0; j < M; j++) {
        if (request[j] > need[p][j]) {
            printf("Error: Process P%d requested more than its maximum need.\n", p);
            return false;
        }
    }

    /* Step 2: Check request <= available */
    for (int j = 0; j < M; j++) {
        if (request[j] > available[j]) {
            printf("Process P%d must wait — resources not available.\n", p);
            return false;
        }
    }

    /* Step 3: Pretend to allocate */
    for (int j = 0; j < M; j++) {
        available[j] -= request[j];
        allocation[p][j] += request[j];
        need[p][j] -= request[j];
    }

    int safeSeq[N];
    if (isSafe(safeSeq)) {
        printf("Request can be granted. System will be in a SAFE state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < N; i++) printf("P%d ", safeSeq[i]);
        printf("\n");
        return true;
    } else {
        /* Rollback */
        for (int j = 0; j < M; j++) {
            available[j] += request[j];
            allocation[p][j] -= request[j];
            need[p][j] += request[j];
        }
        printf("Request CANNOT be granted. System would be UNSAFE.\n");
        return false;
    }
}

int main(void) {
    /* Example data (you can modify) */
    int initial_allocation[N][M] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int initial_max[N][M] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int initial_available[M] = {3, 3, 2}; /* as provided */

    /* Initialize system state */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            allocation[i][j] = initial_allocation[i][j];
            max[i][j] = initial_max[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    for (int j = 0; j < M; j++) available[j] = initial_available[j];

    printState();

    /* Check initial safety */
    int safeSeq[N];
    if (isSafe(safeSeq)) {
        printf("\nInitial state is SAFE.\nSafe sequence: ");
        for (int i = 0; i < N; i++) printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nInitial state is NOT SAFE.\n");
    }

    /* Example request from user */
    int p;
    int request[M];
    printf("\nEnter process number making request (0-%d): ", N-1);
    if (scanf("%d", &p) != 1) {
        printf("Invalid input for process number.\n");
        return 1;
    }

    printf("Enter request vector (space separated %d integers): ", M);
    for (int j = 0; j < M; j++) {
        if (scanf("%d", &request[j]) != 1) {
            printf("Invalid input for request vector.\n");
            return 1;
        }
    }

    requestResources(p, request);
    printState();

    return 0;
}
