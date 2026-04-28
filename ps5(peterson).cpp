#include <iostream>
#include <thread>
using namespace std;

bool flag[2] = {false, false};
int turn;

// Critical Section
void criticalSection(int process) {
    cout << "Process " << process << " ENTERED critical section\n";
    
    // Simulate work
    for(int i = 0; i < 3; i++) {
        cout << "Process " << process << " working...\n";
    }

    cout << "Process " << process << " EXITING critical section\n";
}

// Peterson's Algorithm
void peterson(int process) {
    int other = 1 - process;

    flag[process] = true;     // I want to enter
    turn = other;             // Give turn to other

    // Wait
    while(flag[other] && turn == other);

    // Critical Section
    criticalSection(process);

    // Exit Section
    flag[process] = false;
}

int main() {
    thread t1(peterson, 0); // P0
    thread t2(peterson, 1); // P1

    t1.join();
    t2.join();

    return 0;
}