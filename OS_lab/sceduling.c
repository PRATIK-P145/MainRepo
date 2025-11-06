#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// -------------------- SSTF Algorithm --------------------
void SSTF(int arr[], int n, int head) {
    int seek = 0;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Sequence: %d", head);

    for (int i = 0; i < n; i++) {
        int min = INT_MAX, index = -1;

        // Find nearest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(arr[j] - head) < min) {
                min = abs(arr[j] - head);
                index = j;
            }
        }

        visited[index] = 1;
        seek += abs(arr[index] - head);
        head = arr[index];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time = %d", seek);
    printf("\nAverage Seek Time = %.2f\n", (float)seek / n);
}

// -------------------- SCAN Algorithm --------------------
void SCAN(int arr[], int n, int head, int disk_size) {
    int seek = 0;
    int left[n], right[n];
    int l = 0, r = 0;

    // Divide requests into left and right of head
    for (int i = 0; i < n; i++) {
        if (arr[i] >= head)
            right[r++] = arr[i];
        else
            left[l++] = arr[i];
    }

    // Sort both sides
    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    printf("\n--- SCAN Disk Scheduling ---\n");
    printf("Sequence: %d", head);

    // Move towards higher end first
    for (int i = 0; i < r; i++) {
        seek += abs(right[i] - head);
        head = right[i];
        printf(" -> %d", head);
    }

    // Move to end if not at the last track
    if (r > 0 && head != disk_size - 1) {
        seek += abs((disk_size - 1) - head);
        head = disk_size - 1;
        printf(" -> %d", head);
    }

    // Reverse towards left
    for (int i = l - 1; i >= 0; i--) {
        seek += abs(left[i] - head);
        head = left[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time = %d", seek);
    printf("\nAverage Seek Time = %.2f\n", (float)seek / n);
}

// -------------------- C-LOOK Algorithm --------------------
void CLOOK(int arr[], int n, int head) {
    int seek = 0;
    int left[n], right[n];
    int l = 0, r = 0;

    // Divide requests into left and right of head
    for (int i = 0; i < n; i++) {
        if (arr[i] >= head)
            right[r++] = arr[i];
        else
            left[l++] = arr[i];
    }

    // Sort both sides
    for (int i = 0; i < r - 1; i++)
        for (int j = i + 1; j < r; j++)
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }

    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (left[i] > left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }

    printf("\n--- C-LOOK Disk Scheduling ---\n");
    printf("Sequence: %d", head);

    // Move towards higher end first
    for (int i = 0; i < r; i++) {
        seek += abs(right[i] - head);
        head = right[i];
        printf(" -> %d", head);
    }

    // Jump to the lowest request (circular movement)
    if (l > 0) {
        seek += abs(head - left[0]);
        head = left[0];
        printf(" -> %d", head);

        for (int i = 1; i < l; i++) {
            seek += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time = %d", seek);
    printf("\nAverage Seek Time = %.2f\n", (float)seek / n);
}

// -------------------- Main Function --------------------
int main() {
    int n, head, disk_size;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter disk requests (space separated): ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("\nInitial Head Position: %d\n", head);

    SSTF(arr, n, head);
    SCAN(arr, n, head, disk_size);
    CLOOK(arr, n, head);

    return 0;
}
