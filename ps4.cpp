#include <iostream>
#include <algorithm>
using namespace std;

struct P {
    int pid, bt, at, pr, ct, wt, tat;
};

// Display
void display(P p[], int n) {
    float avg_wt = 0, avg_tat = 0;

    cout << "\nPID\tBT\tAT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].bt << "\t" << p[i].at << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    cout << "Avg WT = " << avg_wt/n;
    cout << "\nAvg TAT = " << avg_tat/n << endl;
}

// FCFS
void fcfs(P p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].at) time = p[i].at;

        p[i].ct = time + p[i].bt;
        time = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// SJF (Non-preemptive)
void sjf(P p[], int n) {
    sort(p, p+n, [](P a, P b){ return a.bt < b.bt; });
    fcfs(p, n);
}

// Priority (Non-preemptive)
void priority(P p[], int n) {
    sort(p, p+n, [](P a, P b){ return a.pr < b.pr; });
    fcfs(p, n);
}

// Round Robin
void roundRobin(P p[], int n, int tq) {
    int rem[10], time = 0, done;

    for(int i = 0; i < n; i++) rem[i] = p[i].bt;

    do {
        done = 1;
        for(int i = 0; i < n; i++) {
            if(rem[i] > 0) {
                done = 0;

                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    p[i].ct = time;

                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    rem[i] = 0;
                }
            }
        }
    } while(!done);
}

int main() {
    P p[10];
    int n, choice, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        cout << "Enter BT and AT for P" << i+1 << ": ";
        cin >> p[i].bt >> p[i].at;
        cout << "Enter Priority: ";
        cin >> p[i].pr;
    }

    cout << "\n1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\nEnter choice: ";
    cin >> choice;

    if(choice == 1) fcfs(p, n);
    else if(choice == 2) sjf(p, n);
    else if(choice == 3) priority(p, n);
    else if(choice == 4) {
        cout << "Enter Time Quantum: ";
        cin >> tq;
        roundRobin(p, n, tq);
    }

    display(p, n);
    return 0;
}