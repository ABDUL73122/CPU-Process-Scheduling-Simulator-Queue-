#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int pid;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
    int ct;  // Completion Time
} Process;

int main() {
    int n, tq;
    Process p[MAX];
    int queue[MAX], front = 0, rear = 0;
    bool visited[MAX] = {false};

    printf("=== CPU Process Scheduling Simulator (Round Robin Queue) ===\n");
    printf("Enter total number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", p[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("  Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);
    if (tq <= 0) {
        printf("Time quantum must be greater than 0.\n");
        return 1;
    }

    // Sort processes by arrival time (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j+1].at) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    int completed = 0;
    int idx;

    // Push the first arriving process into the queue
    queue[rear++] = 0;
    visited[0] = true;
    current_time = p[0].at;

    printf("\n--- Execution Timeline (Gantt Chart) ---\n");

    while (front < rear) {
        idx = queue[front++];

        if (p[idx].rt > tq) {
            current_time += tq;
            p[idx].rt -= tq;
            printf("P%d (t=%d) -> ", p[idx].pid, current_time);
        } else {
            current_time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
            printf("P%d [Finished at t=%d] -> ", p[idx].pid, current_time);
        }

        // Enqueue any newly arrived processes up to current time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }

        // If the current process still needs CPU time, push it back to the queue
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        }

        // If queue becomes empty but processes are left, jump time to next arrival
        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (p[i].rt > 0) {
                    queue[rear++] = i;
                    visited[i] = true;
                    current_time = p[i].at;
                    break;
                }
            }
        }
    }
    printf("END\n");

    // Display summary table
    printf("\n--- Performance Summary ---\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
