#include <stdio.h>

struct process {
    char name;
    int at, bt, ct, wt, tat;
    int complete;
    float ntt;
} p[10];

int m;

void sortByArrival() {
    struct process temp;
    int i, j;
    for (i = 0; i < m - 1; i++) {
        for (j = i + 1; j < m; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void main() {
    int i, j, t, sum_bt = 0;
    char c;
    int arriv[100];
    int burst[100];
    float avgwt = 0, avgtt = 0;
    printf("Enter the total number of processes: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++) {
        printf("Enter the arrival time for P%d: ", i + 1);
        scanf("%d", &arriv[i]);
        printf("Enter the burst time for P%d: ", i + 1);
        scanf("%d", &burst[i]);
    }

    for (i = 0, c = '1'; i < m; i++, c++) {
        p[i].name = c;
        p[i].at = arriv[i];
        p[i].bt = burst[i];
        p[i].complete = 0;
        sum_bt += p[i].bt;
    }

    sortByArrival();
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time");

    int time = p[0].at; // Initialize time with the arrival time of the first process

    while (1) {
        float hrr = -1; // Initialize highest response ratio
        int loc = -1;    // Location of process with highest response ratio

        // Find process with highest response ratio
        for (i = 0; i < m; i++) {
            if (p[i].complete != 1 && p[i].at <= time) {
                float response_ratio = (time - p[i].at + p[i].bt) / (float)p[i].bt;
                if (response_ratio > hrr) {
                    hrr = response_ratio;
                    loc = i;
                }
            }
        }

        // If no process found, break the loop
        if (loc == -1)
            break;

        // Execute the process
        time += p[loc].bt;
        p[loc].ct = time;
        p[loc].tat = p[loc].ct - p[loc].at;
        p[loc].wt = p[loc].tat - p[loc].bt;
        avgwt += p[loc].wt;
        avgtt += p[loc].tat;
        p[loc].complete = 1;

        printf("\nP%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d", p[loc].name, p[loc].at, p[loc].bt, p[loc].ct, p[loc].tat, p[loc].wt);
    }
    printf("\nThe Average waiting time: %f\n", avgwt / m);
    printf("The Average Turn Around time: %f\n", avgtt / m);
}
