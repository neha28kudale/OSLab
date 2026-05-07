#include <stdio.h>
#include <pthread.h>

int flag[2] = {0, 0};
int turn;

/* Critical Section */
void criticalSection(int process) {
    printf("Process %d ENTERED critical section\n", process);

    for(int i = 0; i < 3; i++) {
        printf("Process %d working...\n", process);
    }

    printf("Process %d EXITING critical section\n", process);
}

/* Peterson Algorithm */
void* peterson(void* arg) {
    int process = *(int*)arg;
    int other = 1 - process;

    // Process wants to enter
    flag[process] = 1;

    // Give chance to other process
    turn = other;

    // Wait if other process also wants to enter
    while(flag[other] && turn == other);

    // Critical Section
    criticalSection(process);

    // Exit section
    flag[process] = 0;

    return NULL;
}

int main() {
    pthread_t t1, t2;

    int p0 = 0;
    int p1 = 1;

    // Create threads
    pthread_create(&t1, NULL, peterson, &p0);
    pthread_create(&t2, NULL, peterson, &p1);

    // Wait for completion
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
