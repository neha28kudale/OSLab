#include <iostream>
#include <climits>
using namespace std;

void printResult(string name, int alloc[], int n) {
    cout << "\n" << name << "\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << " -> ";
        if (alloc[i] != -1)
            cout << "B" << alloc[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

void printRemaining(int block[], int m) {
    cout << "\nRemaining Memory Blocks:\n";
    for (int i = 0; i < m; i++) {
        cout << "B" << i + 1 << " -> " << block[i] << endl;
    }
}

// ---------------- FIRST FIT ----------------
void firstFit(int block[], int m, int process[], int n) {
    int alloc[n];
    int temp[m];

    for (int i = 0; i < m; i++) temp[i] = block[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                alloc[i] = j;
                temp[j] -= process[i];
                break;
            }
        }
    }

    printResult("First Fit", alloc, n);
    printRemaining(temp, m);
}

// ---------------- BEST FIT ----------------
void bestFit(int block[], int m, int process[], int n) {
    int alloc[n];
    int temp[m];

    for (int i = 0; i < m; i++) temp[i] = block[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int best = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                if (best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if (best != -1) {
            alloc[i] = best;
            temp[best] -= process[i];
        }
    }

    printResult("Best Fit", alloc, n);
    printRemaining(temp, m);
}

// ---------------- WORST FIT ----------------
void worstFit(int block[], int m, int process[], int n) {
    int alloc[n];
    int temp[m];

    for (int i = 0; i < m; i++) temp[i] = block[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                if (worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            alloc[i] = worst;
            temp[worst] -= process[i];
        }
    }

    printResult("Worst Fit", alloc, n);
    printRemaining(temp, m);
}

// ---------------- NEXT FIT ----------------
void nextFit(int block[], int m, int process[], int n) {
    int alloc[n];
    int temp[m];

    for (int i = 0; i < m; i++) temp[i] = block[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    int last = 0;

    for (int i = 0; i < n; i++) {
        int j = last;
        int count = 0;

        while (count < m) {
            if (temp[j] >= process[i]) {
                alloc[i] = j;
                temp[j] -= process[i];
                last = j;
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    printResult("Next Fit", alloc, n);
    printRemaining(temp, m);
}

// ---------------- MAIN ----------------
int main() {
    int m, n;

    cout << "Enter number of blocks: ";
    cin >> m;

    int block[m];
    cout << "Enter block sizes:\n";
    for (int i = 0; i < m; i++)
        cin >> block[i];

    cout << "Enter number of processes: ";
    cin >> n;

    int process[n];
    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> process[i];

    firstFit(block, m, process, n);
    bestFit(block, m, process, n);
    worstFit(block, m, process, n);
    nextFit(block, m, process, n);

    return 0;
}
/*Algorithm: 
Start
Input number of memory blocks (m)
Input size of each memory block
Input number of processes (n)
Input size of each process
Apply memory allocation using different strategies:
First Fit
Best Fit
Worst Fit
Next Fit
For each algorithm:
Initialize allocation array with -1
Allocate processes to suitable blocks
Update remaining block size
Display:
Process → Block allocation
Unallocated processes
Remaining memory blocks
Compare results of all algorithms
End
Algorithm (Individual Methods)

First Fit
Start from first block
Assign first block that is large enough
Move to next process

Best Fit
Search all blocks
Choose smallest block that fits process
Allocate process

Worst Fit
Search all blocks
Choose largest available block
Allocate process

Next Fit
Start from last allocated position
Continue circular search
Allocate first suitable block found

Sample Input
Enter number of blocks: 5
Enter block sizes:
100 500 200 300 600

Enter number of processes: 4
Enter process sizes:
212 417 112 426
Output

First Fit
P0 → B1
P1 → B4
P2 → B1
P3 → Not Allocated

Best Fit
P0 → B2
P1 → B4
P2 → B3
P3 → Not Allocated

Worst Fit
P0 → B4
P1 → B1
P2 → B4
P3 → Not Allocated

Next Fit
P0 → B1
P1 → B4
P2 → B4
P3 → Not Allocated*/