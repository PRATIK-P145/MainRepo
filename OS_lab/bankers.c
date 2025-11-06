BANKER’S PROBLEM
#include <stdio.h>
#include <stdbool.h>
#define N 5 // Number of processes
#define M 3 // Number of resource types
// Global data structures
int allocation[N][M]; // Allocation Matrix
int max[N][M]; // Max Matrix
int need[N][M]; // Need Matrix = Max - Allocation
int available[M]; // Available resources
// Function to print the system state
void printState() {
printf("\nCurrent System State:\n");
printf("Process Allocation Max Need\n");
for (int i = 0; i < N; i++) {
printf("P%d\t ", i);
for (int j = 0; j < M; j++) printf("%d ", allocation[i][j]);
printf("\t ");
for (int j = 0; j < M; j++) printf("%d ", max[i][j]);
printf("\t ");
for (int j = 0; j < M; j++) printf("%d ", need[i][j]);
printf("\n");
}
printf("Available: ");
for (int j = 0; j < M; j++) printf("%d ", available[j]);
printf("\n");
}
// Safety Algorithm
bool isSafe(int safeSeq[]) {
int work[M];
bool finish[N] = {false};
for (int i = 0; i < M; i++) work[i] = available[i];
int count = 0;
while (count < N) {
bool found = false;
for (int p = 0; p < N; p++) {
if (!finish[p]) {
bool canFinish = true;
for (int j = 0; j < M; j++) {
if (need[p][j] > work[j]) {
canFinish = false;
break;
}
}
BANKER’S PROBLEM
if (canFinish) {
for (int k = 0; k < M; k++) work[k] += allocation[p][k];
safeSeq[count++] = p;
finish[p] = true;
found = true;
}
}
}
if (!found) return false; // no safe sequence
}
return true;
}
// Resource Request Algorithm
bool requestResources(int p, int request[]) {
// Step 1: Check if request <= need
for (int j = 0; j < M; j++) {
if (request[j] > need[p][j]) {
printf("Error: Process %d requested more than its maximum need.\n", p);
return false;
}
}
// Step 2: Check if request <= available
for (int j = 0; j < M; j++) {
if (request[j] > available[j]) {
printf("Process %d must wait, resources not available.\n", p);
return false;
}
}
// Step 3: Pretend to allocate
for (int j = 0; j < M; j++) {
available[j] -= request[j];
allocation[p][j] += request[j];
need[p][j] -= request[j];
}
int safeSeq[N];
if (isSafe(safeSeq)) {
printf("Request can be granted. System is in safe state.\n");
printf("Safe Sequence: ");
for (int i = 0; i < N; i++) printf("P%d ", safeSeq[i]);
printf("\n");
return true;
} else {
// Rollback
for (int j = 0; j < M; j++) {
available[j] += request[j];
allocation[p][j] -= request[j];
need[p][j] += request[j];
}
BANKER’S PROBLEM
printf("Request CANNOT be granted. System would be unsafe.\n");
return false;
}
}
int main() {
// Example data (you can modify)
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
int initial_available[M] = {3, 3, 2};
// Initialize system state
for (int i = 0; i < N; i++)
for (int j = 0; j < M; j++) {
allocation[i][j] = initial_allocation[i][j];
max[i][j] = initial_max[i][j];
need[i][j] = max[i][j] - allocation[i][j];
}
for (int j = 0; j < M; j++) available[j] = initial_available[j];
printState();
// Check initial safety
int safeSeq[N];
if (isSafe(safeSeq)) {
printf("\nInitial state is SAFE.\nSafe Sequence: ");
for (int i = 0; i < N; i++) printf("P%d ", safeSeq[i]);
printf("\n");
} else {
printf("\nInitial state is NOT SAFE.\n");
}
// Example request
int p, request[M];
printf("\nEnter process number making request (0-%d): ", N-1);
scanf("%d", &p);
BANKER’S PROBLEM
printf("Enter request vector (size %d): ", M);
for (int j = 0; j < M; j++) scanf("%d", &request[j]);
requestResources(p, request);
printState();
return 0;
}
OUTPUT:
