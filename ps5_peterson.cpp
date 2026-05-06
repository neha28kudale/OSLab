#include <iostream>
#include <thread>
using namespace std;

bool flag[2] = {false, false};
int turn;

/* Critical Section */
void criticalSection(int process) {
    cout << "Process " << process << " ENTERED critical section\n";

    for(int i = 0; i < 3; i++) {
        cout << "Process " << process << " working...\n";
    }

    cout << "Process " << process << " EXITING critical section\n";
}

/* Peterson's Algorithm */
// Critical Section
void peterson(int process) {
    int other = 1 - process;
    // Entry Section
    flag[process] = true;
    turn = other;

    // Waiting Condition
    while(flag[other] && turn == other);

    criticalSection(process);
    // Exit Section
    flag[process] = false;
}

int main() {
    thread t1(peterson, 0);
    thread t2(peterson, 1);

    t1.join();
    t2.join();

    return 0;
}

/*
Start
Initialize flag[0] = flag[1] = false, turn variable
For Process P0 or P1:
Set flag[i] = true (process wants to enter critical section)
Set turn = other process
Check condition:
While flag[other] == true AND turn == other → wait
Enter Critical Section
Perform required operations
Set flag[i] = false (exit critical section)
Go to remainder section
Repeat steps 4–10
End
I/P: Number of processes = 2
Processes = P0, P1
Initial values:
flag[0] = false
flag[1] = false
turn = undefined
O/P:
Process 0 ENTERED critical section
Process 0 working...
Process 0 working...
Process 0 working...
Process 0 EXITING critical section

Process 1 ENTERED critical section
Process 1 working...
Process 1 working...
Process 1 working...
Process 1 EXITING critical section
*/