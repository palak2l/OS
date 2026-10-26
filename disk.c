#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int requests[] = {82, 170, 43, 140, 24, 16, 190};
int total = sizeof(requests) / sizeof(requests[0]);
int startHead = 50;

// Sorting comparator
int sortCompare(const void *a, const void *b) {
    int p = *(const int *)a;
    int q = *(const int *)b;
    return (p > q) - (p < q);
}

// Find the first element greater than or equal to target
int findPosition(int arr[], int size, int target) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else high = mid;
    }
    return low;
}

// 1. First Come First Serve
int runFCFS() {
    int current = startHead;
    int movement = 0;
    for (int i = 0; i < total; i++) {
        movement += abs(current - requests[i]);
        current = requests[i];
    }
    return movement;
}

// 2. Shortest Seek Time First (Corrected Version)
int runSSTF() {
    bool visited[total];
    for (int i = 0; i < total; i++) {
        visited[i] = false;
    }

    int current = startHead;
    int movement = 0;

    for (int i = 0; i < total; i++) {
        int minDistance = 1e9;
        int minIndex = -1;

        // Find the unvisited request closest to the current head
        for (int j = 0; j < total; j++) {
            if (!visited[j]) {
                int distance = abs(current - requests[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = j;
                }
            }
        }

        // Move to the closest request
        visited[minIndex] = true;
        movement += minDistance;
        current = requests[minIndex];
    }
    return movement;
}

// 3. SCAN
int runSCAN() {
    int temp[total + 1];
    for (int i = 0; i < total; i++) temp[i] = requests[i];
    temp[total] = 199;
    qsort(temp, total + 1, sizeof(int), sortCompare);

    int position = findPosition(temp, total + 1, startHead);
    int right = position;
    int left = position - 1;
    int current = startHead;
    int movement = 0;

    while (right < total + 1) {
        movement += abs(current - temp[right]);
        current = temp[right];
        right++;
    }
    while (left >= 0) {
        movement += abs(current - temp[left]);
        current = temp[left];
        left--;
    }
    return movement;
}

// 4. Circular SCAN
int runCSCAN() {
    int temp[total + 1];
    for (int i = 0; i < total; i++) temp[i] = requests[i];
    temp[total] = 199;
    qsort(temp, total + 1, sizeof(int), sortCompare);

    int position = findPosition(temp, total + 1, startHead);
    int current = startHead;
    int movement = 0;

    for (int i = position; i < total + 1; i++) {
        movement += abs(current - temp[i]);
        current = temp[i];
    }

    // Move from the maximum cylinder to cylinder 0
    movement += current; 
    current = 0;

    for (int i = 0; i < position; i++) {
        movement += abs(current - temp[i]);
        current = temp[i];
    }
    return movement;
}

// 5. LOOK
int runLOOK() {
    int temp[total];
    for (int i = 0; i < total; i++) temp[i] = requests[i];
    qsort(temp, total, sizeof(int), sortCompare);

    int position = findPosition(temp, total, startHead);
    int current = startHead;
    int movement = 0;

    for (int i = position; i < total; i++) {
        movement += abs(current - temp[i]);
        current = temp[i];
    }
    for (int i = position - 1; i >= 0; i--) {
        movement += abs(current - temp[i]);
        current = temp[i];
    }
    return movement;
}

// 6. Circular LOOK
int runCLOOK() {
    int temp[total];
    for (int i = 0; i < total; i++) temp[i] = requests[i];
    qsort(temp, total, sizeof(int), sortCompare);

    int position = findPosition(temp, total, startHead);
    int current = startHead;
    int movement = 0;

    for (int i = position; i < total; i++) {
        movement += abs(current - temp[i]);
        current = temp[i];
    }
    if (position > 0) {
        movement += abs(current - temp[0]);
        current = temp[0];
        for (int i = 1; i < position; i++) {
            movement += abs(current - temp[i]);
            current = temp[i];
        }
    }
    return movement;
}

// Menu-driven main function
int main() {
    int choice;
    do {
        printf("\n--- Disk Scheduling ---\n");
        printf("1. Display All Results\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("FCFS: %d\n", runFCFS());
                printf("SSTF: %d\n", runSSTF());
                printf("SCAN: %d\n", runSCAN());
                printf("C-SCAN: %d\n", runCSCAN());
                printf("LOOK: %d\n", runLOOK());
                printf("C-LOOK: %d\n", runCLOOK());
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}











