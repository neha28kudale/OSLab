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
/*Start
Input number of processes (n) and resources (m)
Input Allocation matrix (Alloc[n][m])
Input Maximum matrix (Max[n][m])
Input Available resources array (Avail[m])
Compute Need matrix:
Need[i][j] = Max[i][j] − Alloc[i][j]
Initialize:
Finish[i] = false for all processes
Work = Available
Find a process Pi such that:
Finish[i] == false
Need[i] ≤ Work
If found:
Work = Work + Allocation[i]
Mark Finish[i] = true
Add Pi to Safe Sequence
Repeat steps 8–9 until all processes are finished or no process can proceed
If all processes are finished → System is SAFE
Else → System is NOT SAFE
End
 Input
Enter number of processes: 3
Enter number of resources: 3

Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2

Enter Maximum Matrix:
7 5 3
3 2 2
9 0 2

Enter Available Resources:
3 3 2

 Output
Need Matrix:
7 4 3
1 2 2
6 0 0

System is SAFE
Safe Sequence: P1 P0 P2*/