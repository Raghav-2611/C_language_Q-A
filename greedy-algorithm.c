#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_JOBS 100
#define MAX_STR_LEN 10

// Define the Job structure
typedef struct {
    char job_id[MAX_STR_LEN];
    int deadline;
    int profit;
} Job;

// Function to swap two jobs
void swap(Job* a, Job* b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort jobs in descending order of profit
void sort_jobs_by_profit(Job jobs[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                swap(&jobs[j], &jobs[j + 1]);
            }
        }
    }
}

// Function to schedule jobs and return the maximum profit
int schedule_jobs(Job jobs[], int n, char result[][MAX_STR_LEN]) {
    // Step 1: Sort jobs by descending order of profit
    sort_jobs_by_profit(jobs, n);

    // Step 2: Find the maximum deadline to determine the number of time slots
    int max_deadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > max_deadline) {
            max_deadline = jobs[i].deadline;
        }
    }

    // Step 3: Initialize result array and slot_filled array
    bool slot_filled[MAX_JOBS] = {false};
    int total_profit = 0;

    // Step 4: Assign jobs to the latest available time slot before their deadline
    for (int i = 0; i < n; i++) {
        for (int j = (jobs[i].deadline < max_deadline ? jobs[i].deadline : max_deadline) - 1; j >= 0; j--) {
            if (!slot_filled[j]) {
                strcpy(result[j], jobs[i].job_id); // Assign the job to this slot
                slot_filled[j] = true;
                total_profit += jobs[i].profit;
                break;
            }
        }
    }

    // Step 5: Return total profit
    return total_profit;
}

int main() {
    // Input jobs with {job_id, deadline, profit}
    Job jobs[] = {
        {"Job1", 2, 100},
        {"Job2", 1, 19},
        {"Job3", 2, 27},
        {"Job4", 1, 25},
        {"Job5", 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    // Array to store the scheduled jobs
    char scheduled_jobs[MAX_JOBS][MAX_STR_LEN] = {""};

    // Schedule jobs and get the maximum profit
    int max_profit = schedule_jobs(jobs, n, scheduled_jobs);

    // Output the scheduled jobs
    printf("Scheduled Jobs: ");
    for (int i = 0; i < n; i++) {
        if (strlen(scheduled_jobs[i]) > 0) {
            printf("%s ", scheduled_jobs[i]);
        }
    }

    // Output the maximum profit
    printf("\nMaximum Profit: %d\n", max_profit);

    return 0;
}
