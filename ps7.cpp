#include <iostream>
using namespace std;

// Display result
void display(int alloc[], int n) {
    cout << "\nProcess\tBlock\n";
    for(int i = 0; i < n; i++) {
        if(alloc[i] != -1)
            cout << "P" << i << "\tB" << alloc[i] << endl;
        else
            cout << "P" << i << "\tNot Allocated\n";
    }
}

// First Fit
void firstFit(int blocks[], int m, int process[], int n) {
    int alloc[10];
    for(int i = 0; i < n; i++) alloc[i] = -1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i]) {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }

    cout << "\n--- First Fit ---";
    display(alloc, n);
}

// Best Fit
void bestFit(int blocks[], int m, int process[], int n) {
    int alloc[10];
    for(int i = 0; i < n; i++) alloc[i] = -1;

    for(int i = 0; i < n; i++) {
        int best = -1;
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i]) {
                if(best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }
        if(best != -1) {
            alloc[i] = best;
            blocks[best] -= process[i];
        }
    }

    cout << "\n--- Best Fit ---";
    display(alloc, n);
}

// Worst Fit
void worstFit(int blocks[], int m, int process[], int n) {
    int alloc[10];
    for(int i = 0; i < n; i++) alloc[i] = -1;

    for(int i = 0; i < n; i++) {
        int worst = -1;
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= process[i]) {
                if(worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }
        if(worst != -1) {
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    cout << "\n--- Worst Fit ---";
    display(alloc, n);
}

// Next Fit
void nextFit(int blocks[], int m, int process[], int n) {
    int alloc[10];
    for(int i = 0; i < n; i++) alloc[i] = -1;

    int j = 0;
    for(int i = 0; i < n; i++) {
        int count = 0;
        while(count < m) {
            if(blocks[j] >= process[i]) {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    cout << "\n--- Next Fit ---";
    display(alloc, n);
}

int main() {
    int m, n;

    cout << "Enter number of blocks: ";
    cin >> m;

    int blocks[10];
    cout << "Enter block sizes:\n";
    for(int i = 0; i < m; i++) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> n;

    int process[10];
    cout << "Enter process sizes:\n";
    for(int i = 0; i < n; i++) cin >> process[i];

    // Copy arrays for each algorithm
    int b1[10], b2[10], b3[10], b4[10];
    for(int i = 0; i < m; i++) {
        b1[i] = b2[i] = b3[i] = b4[i] = blocks[i];
    }

    firstFit(b1, m, process, n);
    bestFit(b2, m, process, n);
    worstFit(b3, m, process, n);
    nextFit(b4, m, process, n);

    return 0;
}