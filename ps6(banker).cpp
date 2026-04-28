#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[10][10], max[10][10], need[10][10];
    int avail[10];

    // Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> alloc[i][j];

    // Maximum Matrix
    cout << "\nEnter Maximum Matrix:\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> max[i][j];

    // Available Resources
    cout << "\nEnter Available Resources:\n";
    for(int i = 0; i < m; i++)
        cin >> avail[i];

    // Calculate Need = Max - Allocation
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    // Safety Algorithm
    bool finish[10] = {false};
    int safeSeq[10];
    int work[10];

    for(int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;

    while(count < n) {
        bool found = false;

        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                bool possible = true;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if(possible) {
                    for(int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found) break;
    }

    // Result
    if(count == n) {
        cout << "\nSystem is SAFE\nSafe Sequence: ";
        for(int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << " ";
    } else {
        cout << "\nSystem is NOT SAFE";
    }

    return 0;
}